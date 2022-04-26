#include "AC_Controller.h"
#include "DIO.h"
#include "PollerTimer.h"
#include "SPI.h"
#include "TC72.h"
#include "utils.h"
#include "USART.h"
#include "poller.h"
#include "stm32f4xx.h"

int main(void)
{
	DIO_Init();

	USART_Init(TRANSMIT, STOP1, WORD8, OVER16);

	SPI_Init(MASTER, IDLE_LOW, SAMPLE_SECOND_TRANSITION);

	TC72_Init();

	StartTimer();
	EnableTimerInterrupt();
	SetPollingTime(500);
	StartPolling();

	while (1)
	{
		StartHeater();
	}
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~(1 << 0);
	TC72_ManageData();
	CallPollingFunction();
}
