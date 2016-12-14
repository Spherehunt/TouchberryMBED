#pragma once

#include "mbed.h"

namespace QT1070TouchDevice{

    class QT1070 {

    private:
      char keyStatus;


    public:
    QT1070();
      char readFirmware();
      char readChipId();
      char readKey();
      void reset();
    public:
        char keyCheck();
    };
};