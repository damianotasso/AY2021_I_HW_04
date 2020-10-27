/* ==============================================================================================================================
 * Damiano Tasso 944232
 *
 * Declaration of global variables used:
 * - HIGH: high state 
 * - LOW: low state
 * - POTENTIOMETER: correspond to the Mux channel value that selects the Potentiometer as active signal to sample
 * - PHOTORESISTOR: correspond to the Mux channel value that selects the Photoresistor as active signal to sample
 * - FSR: (Full Scale Range) maximum value of the dynamic range sampled.
 * - THRESHOLD: value choosen to distinguish light/dark in the room.
 * - BYTE_TO_SEND: Number of bytes to send by the UART
 * - TRANSMIT_BUFFER_SIZE: correspond to the size of the string trasmitted which is equal to the BYTE_TO_SEND + 2 (HEADER & TAIL)
 * - HEADER & TAIL: byte wich compose the complete frame to trasmit
 * 
 * - value_photoresist: value smapled by the photoresistor
 * - value_potentiometer: value sampled by the potentiometer
 * - received: char received by the UART
 * - flag_rx_tx: this flag is HIGH when the received_photoresist and received_potentiometer are saved and are ready to be sent 
 * - flag_start: this flag is HIGH when the right char are received and the sampling start
 * - Data[]: is a vector of TRANSMIT_BUFFER_SIZE size used to save the bytes to send  
 * 
 * ==============================================================================================================================
*/
#ifndef __GLOBAL_H__
    #define __GLOBAL_H__
    
    #include "project.h"
    
    #define HIGH 1
    #define LOW 0
    #define POTENTIOMETER 0
    #define PHOTORESISTOR 1
    #define FSR 65535
    #define THRESHOLD 0.6*FSR 
    #define DEBOUNCE_TH_HIGH THRESHOLD + THRESHOLD*0.1 
    #define DEBOUNCE_TH_LOW THRESHOLD + THRESHOLD*0.1
    #define BYTE_TO_SEND 4
    #define TRANSMIT_BUFFER_SIZE 1+BYTE_TO_SEND+1
    #define HEADER 0xA0
    #define TAIL 0xC0
    
    int32 value_photoresist;
    int32 sum_value_photoresist;
    int32 avg_value_photoresist;
    int32 value_potentiometer;
    int32 sum_value_potentiometer;
    int32 avg_value_potentiometer;
    uint8_t received;
    uint8_t count_timer;
    uint16_t count_deb_d;
    uint16_t count_deb_l;
    volatile uint8_t flag_rx_tx;
    volatile uint8_t flag_start;
    volatile uint8_t flag_dark;
    volatile uint8_t flag_light;
    volatile uint8_t flag;
    volatile uint8_t flag1;
    uint8_t Data[TRANSMIT_BUFFER_SIZE];
    
#endif

/* [] END OF FILE */