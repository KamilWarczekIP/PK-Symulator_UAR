#include "State.h"

State::State() {}

State& State::getInstance()
{
    static State instance;
    return instance;
}
