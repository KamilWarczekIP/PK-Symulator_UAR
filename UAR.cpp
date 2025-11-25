#include "UAR.h"

UAR::UAR(ARX &&arx, RegulatorPID &&pid)
    : previous_y_i(0.0)
    , arx(arx)
    , pid(pid)
{}
UAR::UAR(ARX &arx, RegulatorPID &pid)
    : previous_y_i(0.0)
    , arx(arx)
    , pid(pid)
{}
double UAR::tick(double input)
{
    previous_y_i = this->arx.tick(this->pid.tick(input - previous_y_i));
    return previous_y_i;
}
TickData UAR::tick_more_info(double input)
{
    TickData tick_data;

    tick_data.wartosc_zadana = input;
    tick_data.uchyb = tick_data.wartosc_zadana - previous_y_i;
    tick_data.sterowanie = this->pid.tick(tick_data.uchyb);
    tick_data.wartosc_regulowana = this->arx.tick(tick_data.sterowanie);
    previous_y_i = tick_data.wartosc_regulowana;
    return tick_data;
}
void UAR::resetAll()
{
    arx.reset();
    pid.reset();
    previous_y_i = 0.0;
}
ARX &UAR::getARX()
{
    return this->arx;
}
RegulatorPID &UAR::getRegulatorPID()
{
    return this->pid;
}
