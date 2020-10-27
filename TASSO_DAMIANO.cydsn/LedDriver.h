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
#ifndef __LED_DRIVER_H__
    #define __LED_DRIVER_H__
    
    #include "project.h"
    
    void LED_Start(void);
    void LED_Stop(void);
    
    void LED_DriveIntensity(int32 x);
#endif
/* [] END OF FILE */
