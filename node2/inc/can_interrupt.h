/*
 * can_interrupt.h
 *
 * Author: Gustav O. Often and Eivind H. J�lsgard
 *
 * For use in TTK4155 Embedded and Industrial Computer Systems Design
 * NTNU - Norwegian University of Science and Technology
 *
 */ 

#include "can_controller.h"

#ifndef CAN_INTERRUPT_H_
#define CAN_INTERRUPT_H_
void CAN0_Handler       ( void );

void receive_handler(CAN_MESSAGE* message);




#endif /* CAN_INTERRUPT_H_ */