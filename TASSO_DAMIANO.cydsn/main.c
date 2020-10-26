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
#include "project.h"
#include "global.h"
#include "InterruptRoutines.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    ADC_DelSig_Start();
    UART_Start();
    
    isr_ADC_StartEx(TIMER_ISR);
    isr_UART_StartEx(UART_RX_ISR);

    for(;;)
    {
        if(flag == 1)
        {
            UART_PutString(DataBuffer);
            flag = 0;
        }
    }
}

/* [] END OF FILE */
