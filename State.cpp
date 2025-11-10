#include "State.h"
#include <QDebug>
#include "mainwindow.h"
#include <cassert>

State::State(UAR &&uar)
    : uar(uar)
    , symulacja_dziala(false)
    , wybrany_generator(&this->gen_sin)
{
    symulacja_timer = new QTimer();
    symulacja_timer->setSingleShot(false);
    symulacja_timer->setInterval(200);
    symulacja_timer->connect(symulacja_timer, &QTimer::timeout, this, &State::tick);

    //TODO: usunac to tu
    gen_sin.setAmplitude(1.0);
    gen_sin.setSamplesPerCycle(100);
}
State::~State()
{
    delete symulacja_timer;
}

State &State::getInstance()
{
    static State instance(UAR(ARX({1.0}, {1.0}), RegulatorPID(0.0)));
    return instance;
}
UAR &State::getUAR()
{
    return this->uar;
}
GeneratorSinusoida &State::getGeneratorSinusoida()
{
    return this->gen_sin;
}
GeneratorProstokatny &State::getGeneratorProstokatny()
{
    return this->gen_pros;
}
ARX &State::getARX()
{
    return this->uar.getARX();
}
RegulatorPID &State::getPID()
{
    return this->uar.getRegulatorPID();
}

void State::setSymulacjaDziala(bool symulacja_dziala)
{
    this->symulacja_dziala = symulacja_dziala;
    if (symulacja_dziala)
        symulacja_timer->start();
    else
        symulacja_timer->stop();
}
void State::setInterwalSymulacjiMS(uint32_t interwal)
{
    this->symulacja_timer->setInterval(interwal);
}
bool State::getSymulacjaDziala()
{
    return symulacja_dziala;
}
uint32_t State::getInterwalSymulacjiMS()
{
    return symulacja_timer->interval();
}
void State::setGenerator(Generator *generator)
{
    assert(generator == &this->gen_sin || generator == &this->gen_pros);
    this->wybrany_generator = generator;
}
void State::tick()
{
    emit sendTickDataToMainWindow(uar.tick_more_info(wybrany_generator->tick()));
}
