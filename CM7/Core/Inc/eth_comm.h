/*
 * eth_comm.h
 *
 *  Created on: Apr 22, 2020
 *      Author: kpiek
 */

#ifndef INC_ETH_COMM_H_
#define INC_ETH_COMM_H_

#include "main.h"

/* parse packet function status */
enum{
	eth_packet_ok,
	checksum_error
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
uint8_t parse_eth_data(uint8_t eth_data[], uint8_t eth_data_length, Eth_Packet * eth_packet);


/* function to construct send data packet sensor standard */
void construct_eth_data_packet_sensor_standard(uint8_t eth_packet_data[], Eth_Packet * eth_packet);


/* calculate checksum of the packet  */
void calculate_check_sum(uint8_t eth_packet_data[], uint8_t eth_packet_data_length);


#endif /* INC_ETH_COMM_H_ */
