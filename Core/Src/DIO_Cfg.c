#include "DIO_Cfg.h"

const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS] = {
	{/*USART*/
	 0, 2, 2, 0, 0, 7},
	{/*TC72_SCK*/
	 0, 5, 2, 0, 0, 5},
	{/*TC72_CE*/
	 1, 0, 1, 0, 0, 0},
	{/*TC72_SDI*/
	 0, 6, 2, 0, 0, 5},
	{/*TC72_SDO*/
	 0, 7, 2, 0, 0, 5},
	{/*Heater*/
	 1, 4, 2, 0, 0, 2}
};
