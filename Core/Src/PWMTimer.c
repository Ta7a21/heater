#include "PWMTimer.h"
#include "stm32f4xx.h"
#include "utils.h"
#include "USART.h"

static uint32_type pwm_auto_reload = 100;

void StartPWM(void){
	/* Enable clock */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	/* PWM mode */
	TIM3->CCMR1 |= (0x06 << TIM_CCMR1_OC1M_Pos);

	/* Preload enable */
	TIM3->CCMR1 |= (0x01 << TIM_CCMR1_OC1PE_Pos);

	/* Auto reload preload register enable*/
	TIM3->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);

	/* Initialize all registers */
	TIM3->EGR |= (0x01 << TIM_EGR_UG_Pos);

	/* Direction */
	TIM3->CR1 &= ~(0x01 << TIM_CR1_DIR_Pos);

	/* Aligned mode */
	TIM3->CR1 &= ~(0x03 << TIM_CR1_CMS_Pos);

	/* Polarity enable */
	TIM3->CCER |= (0x01 << TIM_CCER_CC1E_Pos);

	/* Polarity */
	TIM3->CCER &= ~(0x01 << TIM_CCER_CC1P_Pos);

	/* Prescaler */
	TIM3->PSC = 15999;

	/* Autoreload value */
	TIM3->ARR = pwm_auto_reload;

	/* Master mode selection */
	TIM3->CR2 |= (0x04 << TIM_CR2_MMS_Pos);

	/*Enable  timer*/
	TIM3->CR1 |= (0x01 << TIM_CR1_CEN_Pos);
}

void SetDutyCycle(float32_type Duty_Cycle){
	USART_Transmit(convertIntegerToString((uint16_type)(Duty_Cycle * pwm_auto_reload)));
	TIM3->CCR1 = (uint16_type)(Duty_Cycle * pwm_auto_reload);
}

