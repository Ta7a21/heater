#include "utils.h"
#include <stdio.h>
#include "string.h"
#include "USART.h"

char_type str[5] = "0.";
char data[] = {'-', ' ', ' ', '.', ' ', ' ', '\r', '\n', '\0'};

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

char_type *convertIntegerToString(uint16_type num)
{
	char_type *str = "";
	sprintf(str, "%d\r", num);
	return str;
}

char_type *floatToStr(float32_type val) {
	char_type *ptr = data;
  if (val < 0) {
	*ptr = '-';
	ptr++;
	val *= -1;
  }
  int32_type intVal = val * 100;
  ptr[4] = (intVal % 10) + '0';
  intVal /= 10;
  ptr[3] = (intVal % 10) + '0';
  ptr[2] = '.';
  intVal /= 10;
  ptr[1] = (intVal % 10) + '0';
  intVal /= 10;
  ptr[0] = (intVal % 10) + '0';

  ptr[5] = '\r';
  ptr[6] = '\n';
  ptr[7] = '\0';

  return ptr;
}

