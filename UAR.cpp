#include "UAR.h"
#include <stdexcept>


UAR::UAR(ARX&& arx, RegulatorPID&& pid, Generator* generator)
    :previous_y_i(0.0), arx(arx), pid(pid)
{
}
UAR::UAR(ARX& arx, RegulatorPID& pid, Generator* generator)
    :previous_y_i(0.0), arx(arx), pid(pid)
{
}
double UAR::tick(UsesGenerator use_generator)
{
    if(generator == nullptr)
        throw std::runtime_error("generator* nie wskazuje na poprawny obiekt generatora");
    return tick(generator->tick());
}
double UAR::tick(double input)
{
    previous_y_i = this->arx.tick(this->pid.tick(input - previous_y_i));
    return previous_y_i;
}
void UAR::resetAll()
{
    if(generator != nullptr)
        generator->resetClock();
    arx.reset();
    pid.reset();
}
void UAR::setGenerator(Generator* generator)
{
    this->generator = generator;
}
Generator* UAR::getGenerator()
{
    return this->generator;
}
ARX& UAR::getARX()
{
    return this->arx;
}
RegulatorPID& UAR::getRegulatorPID()
{
    return this->pid;
}
