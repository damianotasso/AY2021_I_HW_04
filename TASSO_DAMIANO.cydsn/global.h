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
    #define FSR 65535
    #define THRESHOLD 0.3*FSR 
    #define BYTE_TO_SEND 4
    #define TRANSMIT_BUFFER_SIZE 1+BYTE_TO_SEND+1
    #define HEADER 0xA0
    #define TAIL 0xC0
    
    int32 value_photo;
    int32 value_pot;
    uint8_t received;
    //volatile uint8_t flag_photo;
    //volatile uint8_t flag_pot;
    volatile uint8_t flag_rx_tx;
    volatile uint8_t flag_start;
    uint8_t Data[TRANSMIT_BUFFER_SIZE];
    
#endif

/* [] END OF FILE */