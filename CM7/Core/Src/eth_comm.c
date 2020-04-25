/*
 * eth_comm.c
 *
 *  Created on: Apr 22, 2020
 *      Author: kpiek
 */


#include "eth_comm.h"

extern char uart3_send[200];


/* function parse received ethernet packet */
uint8_t parse_eth_command(char * eth_data, uint16_t eth_data_length, Eth_Packet * eth_packet){

	uint16_t index = 0;

	sprintf(uart3_send, "Packet: %s\n\r", eth_data);
	HAL_UART_Transmit(&huart3, (uint8_t*) uart3_send, strlen(uart3_send), HAL_MAX_DELAY);

	// find start new packet in ethernet data
	while((index < eth_data_length) && (*(eth_data+index) != 's')) index++;

	sprintf(uart3_send, "Index of s character: %d\n\r", index);
	HAL_UART_Transmit(&huart3, (uint8_t*) uart3_send, strlen(uart3_send), HAL_MAX_DELAY);



	return eth_packet_ok;
}


/* function to construct send data packet sensor standard */
void construct_eth_data_packet_sensor_standard(uint8_t eth_packet_data[], Eth_Packet * eth_packet){

	eth_packet_data[0] = 's';
	eth_packet_data[1] = 'n';
	eth_packet_data[2] = 'p';
	eth_packet_data[3] = eth_packet->pacet_type;
	int i;
//	for(i = 0; ){
//
//	}

}


/* function to construct send data packet motor state (speed od the motors) */
void construct_eth_data_packet_motor_state(uint8_t eth_packet_data[], Eth_Packet * eth_packet){




}


/* calculate checksum of the packet  */
void calculate_check_sum(uint8_t eth_packet_data[], uint8_t eth_packet_data_length){



}







