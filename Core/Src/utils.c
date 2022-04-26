#include "utils.h"
#include <stdio.h>
#include "string.h"
#include "USART.h"

char_type str[5] = "0.";
char data[] = {'-', ' ', ' ', '.', ' ', ' ', '\r', '\n', '\0'};

char_type *convertIntegerToString(uint32_type num);

char_type *convertFloatToString(float32_type num)
{
	uint8_type decimal = (num * 100);
	char_type *decimal_string = convertIntegerToString(decimal);
	str[2] = decimal_string[0];
	str[3] = decimal_string[1];
	str[4] = '\0';

//	floatToStr(num, usart2TempData);

	return str;
}

char_type *convertIntegerToString(uint32_type num)
{
	char_type *str = "";
	sprintf(str, "%d", num);
	return str;
}

char_type *floatToStr(float64_type val) {
  int32_type intVal = val * 100;
  data[4] = (intVal % 10) + '0';
  intVal /= 10;
  data[3] = (intVal % 10) + '0';
  data[2] = '.';
  intVal /= 10;
  data[1] = (intVal % 10) + '0';
  intVal /= 10;
  data[0] = (intVal % 10) + '0';

  data[5] = '\r';
  data[6] = '\n';
  data[7] = '\0';

  return data;
}

