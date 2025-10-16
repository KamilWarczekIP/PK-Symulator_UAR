#include "Generator.h"
#include <stdexcept>

Generator::Generator()
    : amplitude(1.0), bias(0.0), internal_clock(0), samples_per_cycle(128)
{

}
void Generator::setAmplitude(double amplitude)
{
    if(amplitude <= 0.0)
        throw std::invalid_argument("Amplituda nie może być ujemna");
    this->amplitude = amplitude;
}
void Generator::setSamplesPerCycle(uint16_t samples_per_cycle)
{
    if(samples_per_cycle <= 1)
        throw std::invalid_argument("Nie można ustawić mneij niż 2 próbek na okres");
    this->samples_per_cycle = samples_per_cycle;
}
void Generator::setBias(double bias)
{
    this->bias = bias;
}
double Generator::getAmplitude()
{
    return this->amplitude;
}
uint16_t Generator::getSamplesPerCycle()
{
    return this->samples_per_cycle;
}
double Generator::getBias()
{
    return this->bias;
}
void Generator::resetClock()
{
    internal_clock = 0;
}
