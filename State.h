#ifndef STATE_H
#define STATE_H
#include "UAR.h"
#include "GeneratorProstokatny.h"
#include "GeneratorSinusoida.h"

class State
{
    UAR uar;
    GeneratorSinusoida gen_sin;
    GeneratorProstokatny gen_pros;

    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(UAR&&);
public:
    static State& getInstance();
    UAR& getUAR();
    GeneratorSinusoida& getGeneratorSinusoida();
    GeneratorProstokatny& getGeneratorProstokatny();
    ARX& getARX();
    RegulatorPID& getPID();

};

#endif // STATE_H
