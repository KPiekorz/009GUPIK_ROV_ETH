/*
 * eth_comm.h
 *
 *  Created on: Apr 22, 2020
 *      Author: kpiek
 */

#ifndef INC_ETH_COMM_H_
#define INC_ETH_COMM_H_

#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

/* parse packet function status */
enum{
	eth_packet_ok = 1,
	checksum_error,
	no_packet_found
};

/* packet type for command packet */
enum{
	sensor_command  = 1,
	motor_command
};

/* packet type for data packet */
enum{
	sensor_data_standart = 1,
	motor_data_standard
};



/* struct to hold packet variables */
typedef struct{

	uint8_t pacet_type;
	uint8_t data_length;
	uint8_t data[30];
	uint16_t checksum;

}Eth_Packet;


/* function parse received ethernet packet */
uint8_t parse_eth_command(char * eth_data, uint16_t eth_data_length, Eth_Packet * eth_packet);


/* function to construct send data packet sensor standard */
void construct_eth_data_packet_sensor_standard(uint8_t eth_packet_data[], Eth_Packet * eth_packet);

/* function to construct send data packet motor state (speed od the motors) */
void construct_eth_data_packet_motor_state(uint8_t eth_packet_data[], Eth_Packet * eth_packet);

/* calculate checksum of the packet  */
void calculate_check_sum(uint8_t eth_packet_data[], uint8_t eth_packet_data_length);


#endif /* INC_ETH_COMM_H_ */
