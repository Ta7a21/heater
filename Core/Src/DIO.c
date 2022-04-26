#include "DIO_Cfg.h"
#include "stm32f4xx.h"
#include "stdint.h"
#include "utils.h"

#define NUM_OF_PORTS ((uint8_type)4)

GPIO_TypeDef *Ports[NUM_OF_PORTS] = {GPIOA, GPIOB, GPIOC, GPIOD};
extern const DIO_ChannelConfigType DIO_ConfigParam[DIO_NUM_OF_CHANNELS];

void DIO_Init(void)
{
	uint8_type Loop;
	for (Loop = (uint8_type)0; Loop < DIO_NUM_OF_CHANNELS; ++Loop)
	{
		uint8_type PortId;
		/*read the port Id from link time configuration*/
		PortId = DIO_ConfigParam[Loop].PortId;

		/*verify Port Id*/
		if (PortId < NUM_OF_PORTS)
		{
			/*Enable clock*/
			RCC->AHB1ENR |= (1 << PortId);
			GPIO_TypeDef *GPIOx = Ports[PortId];
			uint8_type PinNumber = DIO_ConfigParam[Loop].PinNum;
			/*this  bit always = 0 in input or output mode */
//			GPIOx->MODER &= ~(1 << ((PinNumber * 2) + 1));

			/*if output*/
			switch (DIO_ConfigParam[Loop].PortDirection)
			{
			case 0:{
				GPIOx->MODER &= ~(1 << (PinNumber * 2));
				/*pull up */
				if (DIO_ConfigParam[Loop].PuPd == 1u)
				{
					GPIOx->PUPDR |= (1 << (PinNumber * 2));
					GPIOx->PUPDR &= ~(1 << ((PinNumber * 2) + 1));
				}
				/*pull down */
				else if (DIO_ConfigParam[Loop].PuPd == 2u)
				{
					GPIOx->PUPDR |= (1 << ((PinNumber * 2) + 1));
					GPIOx->PUPDR &= ~(1 << (PinNumber * 2));
				}
				/* No pull-up, pull-down */
				else
				{
					GPIOx->PUPDR &= ~(1 << (PinNumber * 2));
					GPIOx->PUPDR &= ~(1 << ((PinNumber * 2) + 1));
				}
				break;
			}
			case 1:
			{
				/*if output type open drain*/
				GPIOx->MODER |= (1 << (PinNumber * 2));
				if (DIO_ConfigParam[Loop].OutputType == 1)
				{
					GPIOx->OTYPER |= (1 << PinNumber);
				}
				/*if output type push-pull*/
				else
				{
					GPIOx->OTYPER &= ~(1 << PinNumber);
				}
				break;
			}
			case 2:
			{
				GPIOx->MODER |= (2 << (PinNumber * 2));
				if (DIO_ConfigParam[Loop].OutputType == 1)
				{
					GPIOx->OTYPER |= (1 << PinNumber);
				}
				else
				{
					GPIOx->OTYPER &= ~(1 << PinNumber);
				}
				/* 0-7 => Shifting by 3 = 0 */
				/* 8-15 => Shifting by 3 = 1 */
				uint8_type AlternateFunctionRegister = PinNumber >> 3;
//				GPIOA->AFR[AlternateFunctionRegister] &= ~(0xf << PinNumber * 4);
				GPIOx->AFR[AlternateFunctionRegister] |=
					(DIO_ConfigParam[Loop].AlternateFunction << PinNumber * 4);
				break;
			}
			}
		}
	}
}

void DIO_ChannelAFConfig(uint8_type ChannelId, uint8_type Function)
{
	if (ChannelId < DIO_NUM_OF_CHANNELS)
	{
		uint8_type PinNumber = DIO_ConfigParam[ChannelId].PinNum;
		uint8_type PortId = DIO_ConfigParam[ChannelId].PortId;
		GPIO_TypeDef *GPIOx = Ports[PortId];
		GPIOx = Ports[PortId];
		if (DIO_ConfigParam[ChannelId].PortDirection == 2)
		{
			uint8_type AlternateFunctionRegister = PinNumber >> 3;
			GPIOx->AFR[AlternateFunctionRegister] |= (Function << PinNumber * 4);
		}
	}
}

void DIO_ChannelAFGroupConfig(DIO_ChannelGroupConfigType ChannelGroupId,
							  uint8_type Functions[])
{
	uint8_type Loop;
	for (Loop = (uint8_type)0; Loop < ChannelGroupId.NumOfIds; ++Loop)
	{
		DIO_ChannelAFConfig(ChannelGroupId.ChannelIds[Loop], Functions[Loop]);
	}
}

void DIO_ChannelWrite(uint8_type ChannelId, const uint8_type Data)
{
	if (ChannelId < DIO_NUM_OF_CHANNELS)
	{
		uint8_type PortId;
		PortId = DIO_ConfigParam[ChannelId].PortId;
		GPIO_TypeDef *GPIOx = Ports[PortId];
		GPIOx = Ports[PortId];
		if (DIO_ConfigParam[ChannelId].PortDirection == 1)
		{
			if (Data)
			{
				GPIOx->ODR |= (1 << (DIO_ConfigParam[ChannelId].PinNum));
			}
			else
			{
				GPIOx->ODR &= ~(1 << (DIO_ConfigParam[ChannelId].PinNum));
			}
		}
	}
}

void DIO_ChannelGroupWrite(DIO_ChannelGroupConfigType ChannelGroupId,
						   const uint8_type Data[])
{
	uint8_type Loop;
	for (Loop = (uint8_type)0; Loop < ChannelGroupId.NumOfIds; ++Loop)
	{
		DIO_ChannelWrite(ChannelGroupId.ChannelIds[Loop], Data[Loop]);
	}
}

void DIO_ChannelRead(uint8_type ChannelId, uint8_type *DataPtr)
{
	if (ChannelId < DIO_NUM_OF_CHANNELS)
	{
		uint8_type PortId;
		PortId = DIO_ConfigParam[ChannelId].PortId;
		if (DIO_ConfigParam[ChannelId].PortDirection == 0)
		{
			GPIO_TypeDef *GPIOx = Ports[PortId];
			*DataPtr =
				((1 << (DIO_ConfigParam[ChannelId].PinNum)) & GPIOx->IDR) ? 1 : 0;
		}
	}
}

void DIO_ChannelGroupRead(DIO_ChannelGroupConfigType ChannelGroupId,
						  uint8_type *DataPtrs[])
{
	uint8_type Loop;
	for (Loop = (uint8_type)0; Loop < ChannelGroupId.NumOfIds; ++Loop)
	{
		DIO_ChannelRead(ChannelGroupId.ChannelIds[Loop], DataPtrs[Loop]);
	}
}

void DIO_ChannelToggle(uint8_type ChannelId)
{
	if (ChannelId < DIO_NUM_OF_CHANNELS)
	{
		uint8_type PortId;
		PortId = DIO_ConfigParam[ChannelId].PortId;
		GPIO_TypeDef *GPIOx = Ports[PortId];
		if (ChannelId < DIO_NUM_OF_CHANNELS)
		{
			PortId = DIO_ConfigParam[ChannelId].PortId;
			GPIOx = Ports[PortId];
			if (DIO_ConfigParam[ChannelId].PortDirection == 1)
			{
				GPIOx->ODR ^= (1 << (DIO_ConfigParam[ChannelId].PinNum));
			}
		}
	}
}

void DIO_ChannelGroupToggle(DIO_ChannelGroupConfigType ChannelGroupId)
{
	uint8_type Loop;
	for (Loop = (uint8_type)0; Loop < ChannelGroupId.NumOfIds; ++Loop)
	{
		DIO_ChannelToggle(ChannelGroupId.ChannelIds[Loop]);
	}
}
