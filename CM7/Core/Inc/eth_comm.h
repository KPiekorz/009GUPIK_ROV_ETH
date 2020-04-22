/*
 * eth_comm.h
 *
 *  Created on: Apr 22, 2020
 *      Author: kpiek
 */

#ifndef INC_ETH_COMM_H_
#define INC_ETH_COMM_H_

/* parse packet function status */
enum{
	eth_packet_ok,
	checksum_error
};

/* packet type for command packet */
enum{

};

/* packet type for data packet */
enum{

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


/* function to construct send packet */
void construct_eth_packet(uint8_t eth_packet_data[], Eth_Packet * eth_packet);



#endif /* INC_ETH_COMM_H_ */
