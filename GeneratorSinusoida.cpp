#include "GeneratorSinusoida.h"
#define _USE_MATH_DEFINES
#include <cmath>

GeneratorSinusoida::GeneratorSinusoida()
    :Generator()
{}
double GeneratorSinusoida::tick()
{
    internal_clock++;
    return amplitude * std::sin( (internal_clock % samples_per_cycle) / samples_per_cycle * 2 * M_PI ) + bias;
}
