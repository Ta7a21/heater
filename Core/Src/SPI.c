#include "SPI.h"
#include "utils.h"
#include "stm32f401xc.h"

void SPI_EnableClock() { RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; }

void SPI_Init(uint8_type MasterSlave, uint8_type ClkPol, uint8_type ClkPhase)
{
	SPI_EnableClock();

	SPI1->CR1 |= (0x3 << SPI_CR1_SSI_Pos);

	SPI1->CR1 &= ~(1 << SPI_CR1_MSTR_Pos);
	SPI1->CR1 |= (MasterSlave << SPI_CR1_MSTR_Pos);

	SPI1->CR1 &= ~(1 << SPI_CR1_CPOL_Pos);
	SPI1->CR1 |= (ClkPol << SPI_CR1_CPOL_Pos);

	SPI1->CR1 &= ~(1 << SPI_CR1_CPHA_Pos);
	SPI1->CR1 |= (ClkPhase << SPI_CR1_CPHA_Pos);

	SPI1->CR1 &= ~(0x7 << SPI_CR1_BR_Pos);
	SPI1->CR1 |= (0x3 << SPI_CR1_BR_Pos);

	SPI1->CR1 |= (1 << SPI_CR1_SPE_Pos);
}

uint8_type SPI_TransmitRecieveByte(uint8_type TxData)
{
	if (SPI1->SR & (1 << SPI_SR_TXE_Pos))
	{
		SPI1->DR = TxData;
		while (SPI1->SR & (1 << SPI_SR_BSY_Pos));
		return SPI1->DR;
	}
	return -1;
}
