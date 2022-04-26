#ifndef INC_USART_H_
#define INC_USART_H_

/* Oversampling */
#define OVER16 0
#define OVER8 1

/* Word size */
#define WORD8 0
#define WORD9 1

/* Stop bit */
#define STOP1 ((unsigned char)0x00)
#define STOP0_5 ((unsigned char)0x01)
#define STOP2 ((unsigned char)0x10)

/* Mode */
#define TRANSMIT 3
#define RECEIVE 2

void USART_Init(unsigned char Mode, unsigned char Stop,
                unsigned char WordLength, unsigned char Oversampling);
void USART_Transmit(const char *str);

#endif /* INC_USART_H_ */
