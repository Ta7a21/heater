#ifndef INC_AC_CONTROLLER_H_
#define INC_AC_CONTROLLER_H_

#include <utils.h>

float64_type Control_Temperature(float64_type Current_Temperature,
								 float64_type Requested_Temperature);
void StartHeater(void);

#endif /* INC_AC_CONTROLLER_H_ */
