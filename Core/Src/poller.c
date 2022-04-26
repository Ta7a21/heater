#include "poller.h"
#include "AC_Controller.h"
#include "TC72.h"
#include "USART.h"
#include "utils.h"

uint8_type polling_enabled = 1;
uint32_type polling_counter = 1;
uint32_type counter = 0;
extern uint32_type auto_reload_value;

void Poll(void)
{
	if ((polling_enabled == (uint8_type)1) && (counter == (uint32_type)0))
	{
		float64_type current_temperature = TC72_GetTemperature();
		/* Set temperature to 30 */
		float64_type pid_signal =
			Control_Temperature(current_temperature, (float64_type)30);
		USART_Transmit(floatToStr(pid_signal));
	}
	counter = (counter + (uint32_type)1) % ((uint32_type)polling_counter);
}

void StartPolling(void) { polling_enabled = (uint8_type)1; }

void StopPolling(void) { polling_enabled = (uint8_type)0; }

void SetPollingTime(uint32_type polling_time)
{
	polling_counter = polling_time / auto_reload_value;
}
