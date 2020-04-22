/*
 * eth_comm.c
 *
 *  Created on: Apr 22, 2020
 *      Author: kpiek
 */


#include "eth_comm.h"


/* function parse received ethernet packet */
uint8_t parse_eth_data(uint8_t eth_data[], uint8_t eth_data_length, Eth_Packet * eth_packet){



}


/* function to construct send packet */
void construct_eth_packet(uint8_t eth_packet_data[], Eth_Packet * eth_packet){

	eth_packet_data[0] = 's';
	eth_packet_data[1] = 'n';
	eth_packet_data[2] = 'p';
	eth_packet_data[3] = eth_packet->pacet_type;
	int i;
	for(i = 0)

}






