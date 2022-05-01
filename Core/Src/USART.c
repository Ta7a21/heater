#include "USART.h"
#include "utils.h"
#include "stm32f4xx.h"

void USART_EnableClock() { RCC->APB1ENR |= (0x01 << 17); }

void USART_Init(char_type Mode, char_type Stop,
                char_type WordLength, char_type Oversampling)
{
    USART_EnableClock();
    // Enable USART
    USART2->CR1 |= (1 << 13);
    // Baud rate = 9600
    // From equation, 16MHz / 16 * 9600 = 104.16
    // 104 = 0x68
    // .16 * 16 = 2.6 = 0x003 to keep the value after sampling by 16
    // DIV = 0x683
    USART2->BRR = 0x683;
    USART2->CR1 |= (0x01 << Mode);
    USART2->CR1 |= (WordLength << 12);
    USART2->CR1 |= (Oversampling << 15);
    USART2->CR2 |= (Stop << 12);
}

void USART_Transmit(const char_type *str)
{
    while (*str != '\0')
    {
        while (((USART2->SR >> 6) & 1))
        {
            USART2->DR = *str;
            str++;
        }
    }
}
