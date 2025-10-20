#ifndef STATE_H
#define STATE_H
#include "UAR.h"

class State
{
    static UAR uar;

    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State();
public:
    static State& getInstance();

};

#endif // STATE_H
