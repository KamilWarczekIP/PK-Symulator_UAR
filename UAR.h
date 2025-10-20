#ifndef UAR_H
#define UAR_H
#include "RegulatorPID.h"
#include "ARX.h"
#include "Generator.h"

class UAR
{
    ARX arx;
    RegulatorPID pid;
    Generator* generator;
    double previous_y_i;
public:
    using UsesGenerator = bool;
    UAR(ARX& arx, RegulatorPID& pid, Generator* generator = nullptr);
    void setGenerator(Generator* generator);
    Generator* getGenerator();
    double tick(UsesGenerator = true);
    double tick(double input);
    void resetAll();
    ARX& getARX();
    RegulatorPID& getRegulatorPID();
};

#endif // UAR_H
