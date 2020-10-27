/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "InterruptRoutines.h"

CY_ISR(TIMER_ISR)
{
    Timer_ReadStatusRegister();
    if(flag_start == 1)
    {
        AMux_Select(PHOTORESISTOR);
        value_photo = ADC_DelSig_Read32();
        if (value_photo < 0) value_photo = 0;
        if (value_photo > 65535) value_photo = 65535;
        Data[1] = value_photo >> 8;
        Data[2] = value_photo & 0xFF;
        
        if(value_photo <= THRESHOLD)
        {
            pin_LED_Write(1);
            PWM_Led_Start();
            AMux_Select(POTENTIOMETER);
            value_pot = ADC_DelSig_Read32();
            if (value_pot < 0) value_pot = 0;
            if (value_pot > 65535) value_pot = 65535;
            PWM_Led_WriteCompare(value_pot);
            Data[3] = value_pot >> 8;
            Data[4] = value_pot & 0xFF;
        }
        else
        {
            pin_LED_Write(0);
            PWM_Led_Stop();
        }
        flag_rx_tx = 1;
    }
}

CY_ISR(UART_RX_ISR)
{
    received = UART_GetChar();
    
    switch(received)
    {
        case 'B':
        case 'b':
            flag_start = 1;
            Pin_BluLed_Write(1);
            Timer_Start();
            break;
        case 'S':
        case 's':
            flag_start = 0;
            Pin_BluLed_Write(0);
            Timer_Stop();
            break;
        default:
            break;       
    }
}
/* [] END OF FILE */
