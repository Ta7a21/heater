#include "AC_Controller.h"
#include "DIO.h"
#include "PollerTimer.h"
#include "PWMTimer.h"
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
	StartPWM();
	EnableTimerInterrupt();
	SetPollingTime(500);
	StartPolling();

	while (1)
	{
	}
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~(1 << 0);
	TC72_ManageData();
	CallPollingFunction();
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~(1 << TIM_SR_CC1IF_Pos);
}
