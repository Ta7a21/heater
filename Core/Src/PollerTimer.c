#include "PollerTimer.h"
#include "poller.h"
#include "stm32f4xx.h"

uint32_type poller_auto_reload = 100;

void StartTimer(void)
{
	/*Enable timer 2*/
	RCC->APB1ENR |= (1u << 0);

	TIM2->PSC = 15999;
	TIM2->ARR = poller_auto_reload;

	/*clear timer counter*/
	TIM2->CNT = 0;

	/*Enable  timer*/
	TIM2->CR1 |= (1u << 0);
}

void StopTimer(void) { TIM2->CR1 &= ~(1u << 0); }
void EnableTimerInterrupt(void)
{
	/*Enable timer interrupt*/
	TIM2->DIER |= (1 << 0);
	/*Enable timer interrupt NVIC*/
	NVIC_EnableIRQ(TIM2_IRQn);
}

void DisableTimerInterrupt(void)
{
	/*Enable timer interrupt NVIC*/
	NVIC_DisableIRQ(TIM2_IRQn);
	/*Enable timer interrupt*/
	TIM2->DIER &= ~(1u << 0);
}

void CallPollingFunction(void) { Poll(); }
