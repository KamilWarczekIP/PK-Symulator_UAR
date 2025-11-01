#include "State.h"
State::State(UAR&& uar)
    :uar(uar)
{}

State& State::getInstance()
{
    static State instance(UAR(ARX({1.0}, {1.0}), RegulatorPID(1.0)));
    return instance;
}
UAR& State::getUAR()
{
    return this->uar;
}
GeneratorSinusoida& State::getGeneratorSinusoida()
{
    return this->gen_sin;
}
GeneratorProstokatny& State::getGeneratorProstokatny()
{
    return this->gen_pros;
}
ARX& State::getARX()
{
    return this->uar.getARX();
}
RegulatorPID& State::getPID()
{
    return this->uar.getRegulatorPID();
}
