/* ===========================================================================================================================================================================
 * Damiano Tasso 944232
 *
 * When the Timer interrupt is called, the flag_start == HIGH condition is verify, if yes we are in the situation that the sampling could start, because the char received is
 * correct. So, the sensors signals are read alernatively by the AMux_Select() function, which selects the right channel to sample the right signal. With ADC_DelSig_Read32()
 * the value are saved after the adjustment when values exceed the 65535 or 0 values of the byte. 
 * The values sampled are saved in the right position of the Data frame: Data[1], Data[2] for photoresist samples and Data[3], Data[4] for potentiometer samples. This is done 
 * because the first and the last byte positions are occupied by the HEADER and TAIL. 
 * After that, the flag_rx_tx are set to HIGH state, and it is used in the main.c to send the Data[] frame. 
 * In the TIMER_ISR the value_photoresist is controlled, because if it is lower that the THRESHOLD, the external LED must be ON and driven in intensity by the potentiometer,
 * thanks the LED_DriveIntensity() function, which change the PWM Cmp value. Otherwise, if the photoresist_value is higher that the THRESHOLD, the exsternal LED is OFF.
 * 
 =============================================================================================================================================================================
*/
#include "InterruptRoutines.h"
#include "LedDriver.h"

CY_ISR(TIMER_ISR)
{
    Timer_ReadStatusRegister();
    
    if(flag_dark == HIGH)
    { 
        count_deb_d ++;
    }
    if(flag_light == HIGH)
    {
        count_deb_l ++;
    }
    
    if(flag_start == HIGH)
    {
        count_timer ++; 
        
        AMux_Select(PHOTORESISTOR);
        value_photoresist = ADC_DelSig_Read32();
        if (value_photoresist < 0) value_photoresist = 0;
        if (value_photoresist > 65535) value_photoresist = 65535;
        sum_value_photoresist = sum_value_photoresist + value_photoresist;
        
        AMux_Select(POTENTIOMETER);
        value_potentiometer = ADC_DelSig_Read32();
        if (value_potentiometer < 0) value_potentiometer = 0;
        if (value_potentiometer > 65535) value_potentiometer = 65535;
        sum_value_potentiometer = sum_value_potentiometer + value_potentiometer;
        
        if(count_timer == 100)
        {
            count_timer = 0;
            avg_value_photoresist = sum_value_photoresist/100;
            avg_value_potentiometer = sum_value_potentiometer/100;
            
            Data[3] = avg_value_potentiometer >> 8;
            Data[4] = avg_value_potentiometer & 0xFF;
             
            
            if(avg_value_photoresist <= THRESHOLD)
            {
                flag_dark = HIGH;
                flag_light = LOW;
                
                if(count_deb_d == 1000)
                {
                    count_deb_d = 0;
                    flag = HIGH;
                }
                
                if(flag == HIGH)
                {
                    Data[1] = avg_value_photoresist >> 8;
                    Data[2] = avg_value_photoresist & 0xFF;
                    
                    LED_Start();
                    LED_DriveIntensity(avg_value_potentiometer);
                    avg_value_photoresist = 0;
                    sum_value_photoresist = 0;
                }
            }
            else
            {
                flag_light = HIGH;
                flag_dark = LOW;
                
                if(count_deb_l == 1000)
                {
                    count_deb_l = 0;
                    flag1 = HIGH;
                }
                
                if(flag1 == HIGH)
                {
                    LED_Stop();
                
                    Data[1] = avg_value_photoresist >> 8;
                    Data[2] = avg_value_photoresist & 0xFF;
                       
                    avg_value_photoresist = 0;
                    sum_value_photoresist = 0;
                    
                    flag = LOW;
                    flag_dark = LOW;
                }
            }
            
            avg_value_potentiometer = 0;
            sum_value_potentiometer = 0;
            flag_rx_tx = HIGH;
        }
    }
}

 /*
 * ==================================================================================================================================================================
 * 
 * When the UART interrupt is called the the program verify what char receives with UART_GetChar(), if it is 'B'or 'b' the blu_Led is switched ON and the Timer 
 * is activated this state is labeled with the flag_start HIGH which corresponds to the sampling start. Otherwise, if the received char is 'S' or 's', the blu_Led is 
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
            break;
        case 'S':
        case 's':
            flag_start = LOW;
            Pin_BluLed_Write(0);
            LED_Stop();
            Timer_Stop();
            break;
        default:
            break;       
    }
}
/* [] END OF FILE */
