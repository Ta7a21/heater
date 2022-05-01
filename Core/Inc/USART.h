#ifndef INC_USART_H_
#define INC_USART_H_

#include "utils.h"

/* Oversampling */
#define OVER16 0
#define OVER8 1

/* Word size */
#define WORD8 0
#define WORD9 1

/* Stop bit */
#define STOP1 ((char_type)0x00)
#define STOP0_5 ((char_type)0x01)
#define STOP2 ((char_type)0x10)

/* Mode */
#define TRANSMIT 3
#define RECEIVE 2

void USART_Init(char_type Mode, char_type Stop,
                char_type WordLength, char_type Oversampling);
void USART_Transmit(const char_type *str);

#endif /* INC_USART_H_ */
