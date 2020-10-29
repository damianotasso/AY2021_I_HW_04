/* ===============================================================================================================
 * Damiano Tasso 944232
 * 
 * - This .h file is used to define the prototype of three useful function used on the project:
 * - LED_Start(): used to switch  ON the LED
 * - LED_Stop(): used to switched OFF the LED
 * - LED_DriveIntensity(): used to change the compare value of the PWM and so, to modulate the LED light intensity
 *
 * ===============================================================================================================
*/
#ifndef __LED_DRIVER_H__
    #define __LED_DRIVER_H__
    
    #include "project.h"
    
    void LED_Start(void);
    void LED_Stop(void);
    
    void LED_DriveIntensity(int32 x);
#endif
/* [] END OF FILE */
