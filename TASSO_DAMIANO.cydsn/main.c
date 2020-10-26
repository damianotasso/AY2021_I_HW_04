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
    
    Data_photo[0] = HEADER;
    Data_photo[TRANSMIT_BUFFER_SIZE - 1] = TAIL;
    Data_pot[0] = HEADER;
    Data_pot[TRANSMIT_BUFFER_SIZE - 1] = TAIL;
    
    for(;;)
    {
        if(flag_photo == 1)
        {
            UART_PutArray(Data_photo, TRANSMIT_BUFFER_SIZE);
            if(flag_pot == 1)
            {
                UART_PutArray(Data_pot, TRANSMIT_BUFFER_SIZE);
                flag_pot = 0;
            }
            
            flag_photo = 0;
        }
    }
}

/* [] END OF FILE */
