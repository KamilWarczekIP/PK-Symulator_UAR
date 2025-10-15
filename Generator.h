#ifndef GENERATOR_H
#define GENERATOR_H
#include <cstdint>

class Generator
{
    double amplitude();
    uint16_t samplesPerCycle;
    double bias;
public:
    virtual double tick() = 0;
    void setAmplitude(double amplitude);
    void setSamplesPerCycle(uint16_t samplesPerCycle);
    void setBias(double bias);
    double getAmplitude();
    uint16_t getSamplesPerCycle();
    double getBias();
};

#endif // GENERATOR_H
