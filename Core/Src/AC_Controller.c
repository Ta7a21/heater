#include "AC_Controller.h"
#include "DIO.h"
#include "PWMTimer.h"

static const float32_type Kp = 0.1;
static const float32_type Ki = 0.01;
static const float32_type Kd = 0;
static float32_type last_error = 0;
static float32_type sum_errors = 0;
static float32_type max_signal = 1;
static volatile uint32_type heater_time = 0;
extern const uint32_type poller_auto_reload;

void Control_Temperature(float32_type Current_Temperature,
		float32_type Requested_Temperature)
{
	float32_type error = Requested_Temperature - Current_Temperature;
	sum_errors += error;
	float32_type attenuating_signal =
		Kp * (float32_type)error + Kd * ((float32_type)((float32_type)error - (float32_type)last_error) / (float32_type)500.0) + Ki * (float32_type)sum_errors;
	if (attenuating_signal < 0)
	{
		attenuating_signal = 0;
	}
	max_signal = (max_signal > attenuating_signal) ? max_signal : attenuating_signal;
	/* (output_end - output_start) / (input_end - input_start) */
	float32_type slope = 1.0 * (0.73 - 0) / (max_signal - 0);
	/* output_start + slope * (input - input_start) */
	attenuating_signal = 0 + slope * (attenuating_signal - 0);
	last_error = error;
	SetDutyCycle(attenuating_signal);
}
