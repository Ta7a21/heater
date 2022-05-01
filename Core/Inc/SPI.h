#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "utils.h"

#define SLAVE 0x00
#define MASTER 0x01

#define IDLE_LOW 0x00
#define IDLE_HIGH 0x01

#define SAMPLE_FIRST_TRANSITION 0x00
#define SAMPLE_SECOND_TRANSITION 0x01

void SPI_Init(char_type MasterSlave, char_type ClkPol, char_type ClkPhase);
char_type SPI_TransmitRecieveByte(char_type TxData);

#endif /* INC_SPI_H_ */
