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
 * - DARK: it is a global variable that fixes the current state in a DARK condition
 * - LIGHT: it is a global variable that fixes the current state in a LIGHT condition
 * - FROM_DARK_TO_LIGHT: it is a global variable which is used to control the transition from dark to light
 * - FROM_LIGHT_TO_DARK: it is a global variable which is used to control the transition from light to dark
 * - BYTE_TO_SEND: Number of bytes to send by the UART
 * - TRANSMIT_BUFFER_SIZE: correspond to the size of the string trasmitted which is equal to the BYTE_TO_SEND + 2 (HEADER & TAIL)
 * - HEADER & TAIL: byte wich compose the complete frame to trasmit
 * 
 * - value_photoresist: sample of the photoresistor
 * - sum_value_photoresist: used to compute the average value of xxx samples (the same fot potentiometer)
 * - avg_value_photoresist: the average value of the xxx samples (the same fot the potentiometer)
 * - value_potentiometer: value sampled by the potentiometer
 * - received: char received by the UART
 * - count_timer:           |
 * - state:                 |
 * - bouncing_control:      | ---> variables used as counter or flag to control the right transition
 * - count_control_dark:    |
 * - count_control_light:   |
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
    #define THRESHOLD 0.4*FSR // The threshold is set as the 40% of the FSR
    #define LIGHT 0
    #define DARK 1
    #define TO_INIT 0
    #define FROM_LIGHT_TO_DARK 1
    #define FROM_DARK_TO_LIGHT 2
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
    uint8_t state;
    uint8_t bouncing_control;
    uint16_t count_control_dark;
    uint16_t count_control_light;
    volatile uint8_t flag_rx_tx;
    volatile uint8_t flag_start;

    uint8_t Data[TRANSMIT_BUFFER_SIZE];
    
#endif

/* [] END OF FILE */