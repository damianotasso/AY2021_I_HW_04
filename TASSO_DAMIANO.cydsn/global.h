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
#ifndef __GLOBAL_H__
    #define __GLOBAL_H__
    
    #include "project.h"
    
    #define POTENTIOMETER 0
    #define PHOTORESISTOR 1
    #define TRANSMIT_BUFFER_SIZE 16
    #define HEADER 0xA0
    #define TAIL 0xC0
    /*#define START 'B' || 'b'
    #define FINISH 'S' || 's'*/
    
    int32 value_digit_photo;
    int32 value_mv_photo;
    int32 value_digit_pot;
    int32 value_mv_pot;
    uint8_t received;
    volatile uint8_t flag;
    char DataBuffer[TRANSMIT_BUFFER_SIZE];
    
#endif

/* [] END OF FILE */