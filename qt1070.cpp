#include "qt1070.h"

#define DEBUG_MODE 1

extern "C" void mbed_reset();

namespace QT1070TouchDevice{

BusIn joy(p12,p13,p15,p16);
DigitalIn center(p14);

QT1070::QT1070()
{


}

char QT1070::readFirmware()
{

    return 0x15;

}

void QT1070::reset()
{

    mbed_reset();

}

char QT1070::readChipId()
{

    return 0x2E;

}

char QT1070::keyCheck()
{
    char keyCode;
    if (center) {
        printf("Center!\r\n");
        keyStatus = 0;
        keyCode = readKey();
    } else {
        switch(joy) {
            case 0x1:
                printf("Down!\r\n");
                keyStatus = 1;
                keyCode = readKey();
                break;
            case 0x2:
                printf("Left!\r\n");
                keyStatus = 2;
                keyCode = readKey();
                break;
            case 0x4:
                printf("Up!\r\n");
                keyStatus = 3;
                keyCode = readKey();
                break;
            case 0x8:
                printf("Right!\r\n");
                keyStatus = 4;
                keyCode = readKey();
                break;
        }
    }
    return keyCode;
}

char QT1070::readKey()
{
    char tmp;
    switch (keyStatus) {
        case 0:
            tmp =  0x20;
            break;
        case 1:
            tmp = 0x08;
            break;
        case 2:
            tmp = 0x01;
            break;
        case 3:
            tmp = 0x04;
            break;
        case 4:
            tmp =  0x02;
            break;
    }
    printf("%d\r\n",tmp);
    return tmp;
}

};
