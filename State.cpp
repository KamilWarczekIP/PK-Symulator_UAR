#include "State.h"
#include <cassert>

State::State(UAR &&uar)
    : uar(uar)
    , simmulation_running(false)
    , choosen_type(TypGeneratora::Sinusoidalny)
{
    simmulation_timer = new QTimer();
    simmulation_timer->setSingleShot(false);
    simmulation_timer->setInterval(200);
    simmulation_timer->connect(simmulation_timer, &QTimer::timeout, this, &State::tick);
}
State::~State()
{
    delete simmulation_timer;
}

State &State::getInstance()
{
    static State instance(UAR(ARX({1.0}, {1.0}), RegulatorPID(0.0)));
    return instance;
}


void State::setSimmulationRunning(bool simmulation_running)
{
    this->simmulation_running = simmulation_running;
    if (simmulation_running)
        simmulation_timer->start();
    else
        simmulation_timer->stop();
}
void State::setSimmulationIntervalMS(uint32_t interwal)
{
    this->simmulation_timer->setInterval(interwal);
}
bool State::getSimmulationRunning()
{
    return simmulation_running;
}
uint32_t State::getSimmulationIntervalMS()
{
    return simmulation_timer->interval();
}
void State::setOutputCallback(const std::function<void(TickData)> callback)
{
    assert(callback != nullptr); // Przeslany callback musi być poprawny
    this->tick_callback = callback;
}
void State::resetSimmulation()
{
    resetGenerator();
    this->uar.resetAll();
}

void State::setGenerator(TypGeneratora type)
{
    choosen_type = type;
}
State::TypGeneratora State::getGenerator()
{
    return this->choosen_type;
}
void State::setGeneneratorAmplitude(const double& amplitude)
{
    this->gen_pros.setAmplitude(amplitude);
    this->gen_sin.setAmplitude(amplitude);
}
void State::setGeneneratorDutyCycle(const double& duty_cycle)
{
    this->gen_pros.setDutyCycle(duty_cycle);
}
void State::setGeneneratorPeriodMS(uint32_t period)
{
    this->gen_pros.setSamplesPerCycle(period / getSimmulationIntervalMS());
    this->gen_sin.setSamplesPerCycle(period / getSimmulationIntervalMS());
}
uint8_t State::getGeneneratorPeriodJumpMS()
{
    return getSimmulationIntervalMS();
}
void State::resetGenerator()
{
    this->gen_pros.resetClock();
    this->gen_sin.resetClock();
}

void State::setPIDProportional(double k)
{
    this->uar.getRegulatorPID().setK(k);
}
void State::setPIDIntegration(double T_i)
{
    this->uar.getRegulatorPID().setT_i(T_i);
}
void State::setPIDDerrivative(double T_d)
{
    this->uar.getRegulatorPID().setT_d(T_d);
}
void State::setPIDIntegrationType(IntegType integration_type)
{
    this->uar.getRegulatorPID().setIntegrationType(integration_type);
}
void State::resetPIDIntegration()
{
    this->uar.getRegulatorPID().resetIntegrationPart();
}
void State::resetPIDDerrivative()
{
    this->uar.getRegulatorPID().resetDerrivativePart();
}


void State::setARXCoefficients(std::vector<double> a, std::vector<double> b)
{
    this->uar.getARX().setAB(a, b);
}
const std::vector<double> State::getARXCoefficientsA()
{
    return this->uar.getARX().getA();
}
const std::vector<double> State::getARXCoefficientsB()
{
    return this->uar.getARX().getB();
}
void State::setARXTransportDelay(uint16_t k)
{
    this->uar.getARX().setK(k);
}
uint16_t State::getARXTransportDelay()
{
    return this->uar.getARX().getK();
}
void State::setARXInputLimits(double low, double high)
{
    this->uar.getARX().setInputLimits(low, high);
}
const std::pair<double, double>& State::getARXInputLimits()
{
    return this->uar.getARX().getInputLimits();
}
void State::setARXOutputLimits(double low, double high)
{
    this->uar.getARX().setOutputLimits(low, high);
}
const std::pair<double, double>& State::getARXOutputLimits()
{
    return this->uar.getARX().getOutputLimits();
}
void State::setARXNoiseStandardDeviation(double standard_deviation)
{
    this->uar.getARX().setStandardDeviation(standard_deviation);
}
double State::getARXNoiseStandardDeviation()
{
    return this->uar.getARX().getStandardDeviation();
}
void State::setARXLimitsEnabled(bool enabled)
{
    if(enabled)
        this->uar.getARX().enableLimits();
    else
        this->uar.getARX().disableLimits();
}
void State::resetARX()
{
    this->uar.getARX().reset();
}

void State::saveToFile()
{
    //TODO
    assert(1==0);
}
void State::readFromFile()
{
    //TODO
    assert(1==0);
}

void State::tick()
{
    Generator* curr_gen;
    switch (this->choosen_type) {
    case TypGeneratora::Prostokatny:
        curr_gen = &this->gen_pros;
        break;
    case TypGeneratora::Sinusoidalny:
    default:
        curr_gen = &this->gen_sin;
        break;
    }
    this->tick_callback(uar.tick_more_info(curr_gen->tick()));
}
