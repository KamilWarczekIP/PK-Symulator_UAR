#include "UAR.h"
#include <stdexcept>


UAR::UAR(ARX* arx, RegulatorPID* pid, Generator* generator)
    :previous_y_i(0.0)
{
    if(arx == nullptr)
        throw std::invalid_argument("arx* musi wskazywać poprawny obiekt ARX");
    if(arx == nullptr)
        throw std::invalid_argument("pid* musi wskazywać poprawny obiekt PID");
    this->arx = arx;
    this->pid = pid;
}
double UAR::tick(UsesGenerator use_generator)
{
    if(generator == nullptr)
        throw std::runtime_error("generator* nie wskazuje na poprawny obiekt generatora");
    return tick(generator->tick());
}
double UAR::tick(double input)
{
    previous_y_i = this->arx->tick(this->pid->tick(input - previous_y_i));
    return previous_y_i;
}
void UAR::resetAll()
{
    if(generator != nullptr)
        generator->resetClock();
    arx->reset();
    pid->reset();
}
void UAR::setGenerator(Generator* generator)
{
    this->generator = generator;
}
Generator* UAR::getGenerator()
{
    return this->generator;
}
