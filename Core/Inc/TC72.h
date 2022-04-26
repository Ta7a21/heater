#ifndef INC_TC72_H_
#define INC_TC72_H_

#include <utils.h>

void TC72_Init(void);
void TC72_Select(void);

void TC72_Unselect(void);

void TC72_RegisterWrite(uint8_type RegAdd, uint8_type Data);

void TC72_RegisterRead(uint8_type RegAdd, uint8_type *DataPtr);
float64_type TC72_GetTemperature(void);
void TC72_ManageData(void);

#endif /* INC_TC72_H_ */
