#pragma once
#include "mbed.h"
#include "qt1070.h"

namespace QT1070TouchDevice{

    enum QtRegisterAddress {
        CHIP_ID = 0x00,
        FIRMWARE = 0x01,
        KEY_STATUS = 0x03,
        RESET = 0x57};

    class I2cQT1070 : public I2CSlave {

        private:
            QT1070 touch;
            int registerAddress;

        public:
            I2cQT1070(PinName sda, PinName scl, int address, int frequency);
            void check_for_instruction(void);

        private:
            void send_data_to_master(void);
            void save_register_address(void);

    };
};
