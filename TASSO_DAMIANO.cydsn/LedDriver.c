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
