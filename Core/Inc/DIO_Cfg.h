#ifndef INC_DIO_CFG_H_
#define INC_DIO_CFG_H_

#define DIO_NUM_OF_CHANNELS ((unsigned char)6)
#define DIO_NUM_OF_GROUP_IDS ((unsigned char)3)

typedef struct
{
    unsigned char PortId;
    unsigned char PinNum;
    unsigned char PortDirection; /*0 = input,1 = output*/
    unsigned char PuPd;          /*0 = No pull-up, pull-down,1 up,2 down*/
    unsigned char OutputType;    /*0 = push-pull,1 = open drain*/
    unsigned char AlternateFunction;

} DIO_ChannelConfigType;

typedef struct
{
    unsigned char *ChannelIds;
    unsigned char NumOfIds;

} DIO_ChannelGroupConfigType;

#endif /* INC_DIO_CFG_H_ */
