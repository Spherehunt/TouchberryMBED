#include "mbed.h"
#include "i2c_qt1070.h"



DigitalOut myled(LED1);

int main()
{

    QT1070TouchDevice::I2cQT1070 i2cQT1070(p9, p10, 0x36, 100000);
    int cycleCounter = 0;
    while(1) {
        i2cQT1070.check_for_instruction();

        if(cycleCounter++ >= 250000) {
            myled = !myled;
            cycleCounter = 0;
        }
    }
}