#ifndef INC_HELPER_H_
#define INC_HELPER_H_

typedef char char_type;
typedef signed char int8_type;
typedef signed short int16_type;
typedef signed int int32_type;
typedef signed long int64_type;
typedef unsigned char uint8_type;
typedef unsigned short uint16_type;
typedef unsigned int uint32_type;
typedef unsigned long uint64_type;
typedef float float32_type;
typedef double float64_type;
typedef long double float128_type;

char_type *convertFloatToString(float32_type num);
char_type *convertIntegerToString(uint16_type num);
char_type *floatToStr(float32_type val);

#endif /* INC_HELPER_H_ */
