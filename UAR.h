#ifndef UAR_H
#define UAR_H
#include "RegulatorPID.h"
#include "ARX.h"
#include "Generator.h"

class UAR
{
    ARX* arx;
    RegulatorPID* pid;
    Generator* generator;
    double previous_y_i;
public:
    using UsesGenerator = bool;
    UAR(ARX* arx, RegulatorPID* pid, Generator* generator = nullptr);
    double tick(UsesGenerator = true);
    double tick(double input);
    void resetAll();
};

#endif // UAR_H
