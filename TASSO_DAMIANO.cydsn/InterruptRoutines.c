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
    AMux_Select(PHOTORESISTOR);
    value_digit_photo = ADC_DelSig_Read32();
    if (value_digit_photo < 0) value_digit_photo = 0;
    if (value_digit_photo > 65535) value_digit_photo = 65535;
    sprintf(DataBuffer, "Sample: %ld mV\r\n", value_digit_photo);
    
    flag = 1;
}

CY_ISR(UART_RX_ISR)
{
    received = UART_GetChar();
    
    switch(received)
    {
        case 'B':
        case 'b':
            flag = 1;
            Pin_BluLed_Write(1);
            Timer_Start();
            break;
        case 'S':
        case 's':
            flag = 0;
            Pin_BluLed_Write(0);
            Timer_Stop();
            break;
        default:
            break;       
    }
}
/* [] END OF FILE */
