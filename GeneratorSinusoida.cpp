#include "GeneratorSinusoida.h"
#define _USE_MATH_DEFINES
#include <cmath>

GeneratorSinusoida::GeneratorSinusoida()
    :Generator()
{}
double GeneratorSinusoida::tick()
{
    internal_clock++;
    if(internal_clock == samples_per_cycle) internal_clock = 0;
    if(amplitude == 0)
        return 0.0;
    return amplitude * std::sin( (double)(internal_clock % samples_per_cycle) / samples_per_cycle * 2.0 * M_PI ) + bias;
}
