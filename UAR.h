#ifndef UAR_H
#define UAR_H
#include "RegulatorPID.h"
#include "ARX.h"

struct TickData
{
    double wartosc_zadana;
    double wartosc_regulowana;
    double uchyb;
    double sterowanie;
};

class UAR
{
    ARX arx;
    RegulatorPID pid;
    double previous_y_i;
public:
    UAR(ARX&& arx, RegulatorPID&& pid);
    UAR(ARX& arx, RegulatorPID& pid);
    double tick(double input);
    TickData tick_more_info(double input);
    void resetAll();
    ARX& getARX();
    RegulatorPID& getRegulatorPID();
};

#endif // UAR_H
