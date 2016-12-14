#include "i2c_qt1070.h"


namespace QT1070TouchDevice
{

I2cQT1070::I2cQT1070(PinName sda, PinName scl, int address=0x36, int frequency=100000): I2CSlave(sda, scl)
{

    this->address(address);
    this->frequency(frequency);

}

void I2cQT1070::check_for_instruction(void)
{

    int addressed = receive();
    switch (addressed) {
        case I2CSlave::ReadAddressed:
            printf("Read addressed\r\n");
            send_data_to_master();
            break;

        case I2CSlave::WriteAddressed:
            printf("Write addressed\r\n");
            save_register_address();
            break;
    }

}

void I2cQT1070::send_data_to_master(void)
{
    char value = 0;
    switch (registerAddress) {
        case CHIP_ID:
            value = touch.readChipId();
            break;
        case FIRMWARE:
            value = touch.readFirmware();
            break;
        case RESET:
            touch.reset();
            break;
        case KEY_STATUS:
            value = touch.keyCheck();
            break;
        default:
            printf("Unknown registerAddress.\n");
            break;
    }
    char buffer[] = { value };
    if(!write(buffer, sizeof(buffer))) {
        printf("Sending data....\n");
    } else {
        printf("Sending failed.\n");
    }
}


void I2cQT1070::save_register_address(void)
{
    int tmp = read();;
    if (tmp > 87) {
        printf("Address rejected, too big.\n");
    } else {
        registerAddress = tmp;
    }
    stop();
}
};
