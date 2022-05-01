#include "TC72.h"
#include "DIO.h"
#include "SPI.h"
#include "utils.h"

static float32_type temperature;

float32_type TC72_GetTemperature(void) { return temperature; }

void TC72_ManageData(void)
{
    char_type data = 0;
    temperature = 0.0;
    TC72_Select();
    TC72_RegisterRead(0x01, &data);
    TC72_Unselect();

    if (data & (1 << 7))
    {
        temperature += 0.5;
    }
    if (data & (1 << 6))
    {
        temperature += 0.25;
    }

    TC72_Select();
    TC72_RegisterRead(0x02, &data);
    TC72_Unselect();

    temperature += (signed char)data;
}

void TC72_Init(void)
{
    TC72_Select();
    TC72_RegisterWrite(0x80, 0x00);
    TC72_Unselect();
}

void TC72_Select(void) { DIO_ChannelWrite(2, 1); }

void TC72_Unselect(void) { DIO_ChannelWrite(2, 0); }

void TC72_RegisterWrite(char_type RegAdd, char_type Data)
{
    SPI_TransmitRecieveByte(RegAdd | (1 << 7));
    SPI_TransmitRecieveByte(Data);
}

void TC72_RegisterRead(char_type RegAdd, char_type *DataPtr)
{
    SPI_TransmitRecieveByte(RegAdd & (~(1 << 7)));
    *DataPtr = SPI_TransmitRecieveByte(0x00);
}
