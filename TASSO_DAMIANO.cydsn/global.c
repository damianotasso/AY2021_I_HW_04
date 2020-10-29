/* ========================================
 * Damiano Tasso 944232
 * 
 * Initialization of the global variables 
 * ========================================
*/
#include "global.h"

int32 value_photoresist = 0;
int32 value_potentiometer = 0;
int32 sum_value_photoresist = 0;
int32 avg_value_photoresist = 0;
int32 sum_value_potentiometer = 0;
int32 avg_value_potentiometer = 0;
uint8_t received = 0;
uint8_t count_timer = 0;
uint8_t state = 0;
uint8_t bouncing_control = TO_INIT;
uint16_t count_control_dark = 0;
uint16_t count_control_light = 0;

/* [] END OF FILE */
