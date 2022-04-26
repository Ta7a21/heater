#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "utils.h"

#define SLAVE 0x00
#define MASTER 0x01

#define IDLE_LOW 0x00
#define IDLE_HIGH 0x01

#define SAMPLE_FIRST_TRANSITION 0x00
#define SAMPLE_SECOND_TRANSITION 0x01

void SPI_Init(uint8_type MasterSlave, uint8_type ClkPol, uint8_type ClkPhase);
uint8_type SPI_TransmitRecieveByte(uint8_type TxData);

#endif /* INC_SPI_H_ */
