#include "Generator.h"
#include <cassert>

Generator::Generator()
    : amplitude(1.0)
    , bias(0.0)
    , internal_clock(0)
    , samples_per_cycle(2)
{}
void Generator::setAmplitude(double amplitude)
{
    assert(amplitude >= 0.0);
    this->amplitude = amplitude;
}
void Generator::setSamplesPerCycle(uint16_t samples_per_cycle)
{
    assert(samples_per_cycle >= 1);
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
