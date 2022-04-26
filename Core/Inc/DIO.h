#ifndef INC_DIO_H_
#define INC_DIO_H_

#include "DIO_Cfg.h"
#include "utils.h"

void DIO_Init(void);
void DIO_ChannelWrite(uint8_type ChannelId, const uint8_type Data);
void DIO_ChannelGroupWrite(DIO_ChannelGroupConfigType ChannelGroupId,
                           const uint8_type Data[]);
void DIO_ChannelRead(uint8_type ChannelId, uint8_type *DataPtr);
void DIO_ChannelGroupRead(DIO_ChannelGroupConfigType ChannelGroupId,
                          uint8_type *DataPtrs[]);
void DIO_ChannelToggle(uint8_type ChannelId);
void DIO_ChannelGroupToggle(DIO_ChannelGroupConfigType ChannelGroupId);
void DIO_ChannelAFConfig(uint8_type ChannelId, uint8_type Function);
void DIO_ChannelAFGroupConfig(DIO_ChannelGroupConfigType ChannelGroupId,
                              uint8_type Functions[]);

#endif /* INC_DIO_H_ */
