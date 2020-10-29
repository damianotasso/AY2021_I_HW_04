/* ===================================================================
 * Damiano Tasso 944232
 * 
 * Implementation of the function defined in the corresponding .h file
 * ===================================================================
*/
#include "LedDriver.h"

void LED_Start(void)
{
    PWM_Led_Start();
}

void LED_Stop(void)
{
    PWM_Led_Stop();
}

void LED_DriveIntensity(int32 x)
{
    PWM_Led_WriteCompare(x);
}
/* [] END OF FILE */
