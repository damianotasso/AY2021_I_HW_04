/* ================================================================================================================================================
 * Damiano Tasso 944232
 * 
 * In the main() there is only the activation of the ADC, UART, TIMER_ISR and UART_RX_ISR. 
 * There is also the definition of the HEADER and TAIL in the Data[] frame. 
 * In the infinite loop, instead, there is the sanding of the dataframe, with UART_PutArray(), only if the flag_rx_tx is HIGH, set by the sampling.
 * ================================================================================================================================================
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
    
    Data[0] = HEADER;
    Data[TRANSMIT_BUFFER_SIZE - 1] = TAIL;
    
    for(;;)
    {
        if(flag_rx_tx == HIGH)
        {
            UART_PutArray(Data, TRANSMIT_BUFFER_SIZE);
            flag_rx_tx = LOW;
        }
    }
}

/* [] END OF FILE */
