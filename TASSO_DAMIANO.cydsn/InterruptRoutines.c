/* =====================================================================================================================================================================================
 * Damiano Tasso 944232
 *
 * ***READ ME***
 * 
 * The idea is to sample when the received char is correct. If the sampling can start, the value of the photoresist and of the potentiometer are sampled thanks AMux. Both signals 
 * are adjusted if the values exeed the 0-65535 range. 
 * I have decided to carry out the average of every subsequent 100 samples, for each signals, in order to have more satble signals. Given that the sampling feaquency by the timer
 * overflow is 1ms and considering that, to compute the average are needed 100 samples, I transmits the averaged signals every 100ms. After this averaging the data frame transmitted
 * is composed as follow: Data[HEADER avg_value_photoresist avg_value_photoresist avg_value_potentiometer avg_value_potentiometer TAIL]. 
 * I tried to solve another "problem", which is the swinging of the photoresist signal when it is near the THRESHOLD. If the light "bounces" fast, up and down the threshold, the 
 * LED blinks. The implemented solution is to control the transition from LIGHT to DARK (and viceversa) and verify that the value is below (or above) the THRESHOLD for 1 second
 * consecutively. If yes, I can consider that the the light must be ON because the enviroment is in DARK, otherwise it stays OFF. The same logic from DARK to LIGHT. This solutions
 * follows the "debouncing" logic. The reason why it is choosen 1second to avoid the bouncing is that is very improbable that an artificial/natural light can have a frequency of 1Hz.
 * At the end of the 100 samples and the signals avarage, the flag_rx_tx is set HIGH and it is used in the main.c to send the DATA[]
 *
 =====================================================================================================================================================================================
*/
#include "InterruptRoutines.h"
#include "LedDriver.h"

CY_ISR(TIMER_ISR)
{
    Timer_ReadStatusRegister();
    
    // This switch take into account the bouncing_control flag, if it is in the situation that the eviroment light is 
    // passing from light to dark, the count_control_dark is incremented otherwise, in the opposite situation, is 
    // incremented count_control_light. This two counter values take track of the time used to control the problem of 
    // the swinging of the photoresist signal when it is near the THRESHOLD.
    switch(bouncing_control)
    {
        case FROM_LIGHT_TO_DARK:
            count_control_dark ++;
            break;
        case FROM_DARK_TO_LIGHT:
            count_control_light ++;
            break;
        default:
            break;
    }
    
    //The following condition is verified when the right char is received by the UART
    if(flag_start == HIGH)
    {
        // It counts how many samples are acquired 
        count_timer ++;  
        
        // Photoresistor sampling
        AMux_Select(PHOTORESISTOR);
        value_photoresist = ADC_DelSig_Read32();
        if (value_photoresist < 0) value_photoresist = 0;
        if (value_photoresist > 65535) value_photoresist = 65535;
        
        sum_value_photoresist = sum_value_photoresist + value_photoresist;
        
        // Potentiometer sampling
        AMux_Select(POTENTIOMETER);
        value_potentiometer = ADC_DelSig_Read32();
        if (value_potentiometer < 0) value_potentiometer = 0;
        if (value_potentiometer > 65535) value_potentiometer = 65535;
        
        sum_value_potentiometer = sum_value_potentiometer + value_potentiometer;
        
        // When the 100 samples are acquired the execution of the code enters in this condition
        if(count_timer == 100)
        {
            count_timer = 0;
             
            // Computation of the average signals
            avg_value_photoresist = sum_value_photoresist/100;
            avg_value_potentiometer = sum_value_potentiometer/100;
            
            Data[1] = avg_value_photoresist >> 8;
            Data[2] = avg_value_photoresist & 0xFF;
            Data[3] = avg_value_potentiometer >> 8;
            Data[4] = avg_value_potentiometer & 0xFF;
            
            // Controlling if the avg_value is below the THRESHOLD 
            if(avg_value_photoresist <= THRESHOLD)
            {
                // If the execution arrives at this point means that the the light is passing from light to dark, but it must be verified.
                // So, the bouncing_control flag is initialized as FROM_LIGHT_TO_DARK state, in order to increment a corresponding counter
                // at the switch-case (cfr, raws 24-34)
                bouncing_control = FROM_LIGHT_TO_DARK;
                
                // In the case that the counter_control_dark arrives at 900 (corresponding to 1 second, because are passed 100 + 900 samples), 
                // the program enters in this condition. 
                if(count_control_dark == 900)
                {
                    count_control_dark = 0;
                    count_control_light = 0;
                    
                    // Here the sate is definitively set as DARK, so the led MUST be ON
                    state = DARK;
                }
                
                if(state == DARK)
                {
                    // Switch ON the LED and modulate its intensity with the Potentiometer. 
                    LED_Start();
                    LED_DriveIntensity(avg_value_potentiometer);
                }
            }
            else
            {   
                // In the case that avg_value_photoresist is greather than the THRESHOLD and the LED must be OFF, but there is the case that the light 
                // is passing from dark to light. Also this situation must be verified, using the same logic seen before. 
                // The bouncing_control is set on the state FROM_DARK_TO_LIGHT, which increments the corresponding counter (cfr raws 24-34).
                bouncing_control = FROM_DARK_TO_LIGHT;
                
                // Same control as before, but with the opposite situation 
                if(count_control_light == 900) 
                {
                    count_control_dark = 0;
                    count_control_light = 0;
                    
                    // Here the sate is definitively LIGHT, so the led MUST be OFF
                    state = LIGHT;
                }
                
                if(state == LIGHT)
                {
                    // LED is switched OFF
                    LED_Stop();
                    
                    // bouncing_control is initialized in a value different from FROM_DARK_TO_LIGHT/FROM_LIGHT_TO_DARK because it have to be initialized
                    // with the next interrupt calls.
                    bouncing_control = TO_INIT;
                }
                
            }
            
            avg_value_photoresist = 0;
            sum_value_photoresist = 0;
            avg_value_potentiometer = 0;
            sum_value_potentiometer = 0;
            
            // This flag is used to send Data[] in the main.c
            flag_rx_tx = HIGH;
        }
    }
}

 /*
 * ==================================================================================================================================================================
 * 
 * When the UART interrupt is called the the program verifies what char receives with UART_GetChar(), if it is 'B' or 'b' the blu_Led is switched ON and the Timer 
 * is activated. This state is labeled with the flag_start HIGH which corresponds to the sampling start. Otherwise, if the received char is 'S' or 's', the blu_Led is 
 * switched OFF, the Timer is disactivated and the extern LED is swithed OFF.
 * 
 * ==================================================================================================================================================================
 */

CY_ISR(UART_RX_ISR)
{
    received = UART_GetChar();
    
    switch(received)
    {
        case 'B':
        case 'b':
            flag_start = HIGH;
            Pin_BluLed_Write(1);
            Timer_Start();
            LED_Start();
            state = TO_INIT;
            break;
        case 'S':
        case 's':
            flag_start = LOW;
            Pin_BluLed_Write(0);
            LED_DriveIntensity(0); // Initialization of the CmpValue equalo to zero in order to avoid a 1ms of LED ON when the sampling start again!
            LED_Stop();
            Timer_Stop();
            state = TO_INIT;
            break;
        default:
            break;       
    }
}
/* [] END OF FILE */
