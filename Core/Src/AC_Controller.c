#include "AC_Controller.h"
#include "DIO.h"

static const float64_type Kp = 0.1;
static const float64_type Ki = 0.01;
static const float64_type Kd = 0;
static float64_type last_error = 0;
static float64_type sum_errors = 0;
static float64_type attenuating_signal = 0;
static float64_type max_signal = 1;
static uint8_type heater_counter = 0;
static volatile uint32_type heater_time = 0;
extern const uint32_type auto_reload_value;

void SetHeaterTime(void)
{
	heater_time = attenuating_signal * auto_reload_value;
}

float64_type Control_Temperature(float64_type Current_Temperature,
								 float64_type Requested_Temperature)
{
	float64_type error = Requested_Temperature - Current_Temperature;
	sum_errors += error;
	attenuating_signal =
		Kp * error + Kd * ((error - last_error) / 500) + Ki * sum_errors;
	if (attenuating_signal < 0)
	{
		attenuating_signal = 0;
	}
	max_signal = (max_signal > attenuating_signal) ? max_signal : attenuating_signal;
	/* (output_end - output_start) / (input_end - input_start) */
	float64_type slope = 1.0 * (0.73 - 0) / (max_signal - 0);
	/* output_start + slope * (input - input_start) */
	attenuating_signal = 0 + slope * (attenuating_signal - 0);
	last_error = error;
	SetHeaterTime();
	return attenuating_signal;
}

void StartHeater(void)
{
	if (heater_counter < heater_time)
	{
		DIO_ChannelWrite(5, 1);
	}
	else
	{
		DIO_ChannelWrite(5, 0);
	}
	heater_counter = (heater_counter + (uint32_type)1) % ((uint32_type)100);
}
