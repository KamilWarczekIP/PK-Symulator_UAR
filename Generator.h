#ifndef GENERATOR_H
#define GENERATOR_H
#include <cstdint>

class Generator
{
protected:
    double amplitude;
    uint16_t samples_per_cycle;
    double bias;
    uint16_t internal_clock;

    double advanceClockAndReturn(double);
public:
    Generator();
    virtual double tick() = 0;
    void setAmplitude(double amplitude);
    void setSamplesPerCycle(uint16_t samples_per_cycle);
    void setBias(double bias);
    double getAmplitude() const;
    uint16_t getSamplesPerCycle() const;
    double getBias() const;
    void resetClock();
};

#endif // GENERATOR_H
