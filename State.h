#ifndef STATE_H
#define STATE_H
#include <QObject>
#include <QTimer>
#include "GeneratorProstokatny.h"
#include "GeneratorSinusoida.h"
#include "UAR.h"

class SaveStateInterface;


class State : public QObject
{
    Q_OBJECT
public:
    enum class TypGeneratora { Sinusoidalny, Prostokatny, Reczny };


    static State &getInstance();
    void setSimmulationRunning(bool simmulation_running);
    bool getSimmulationRunning();
    void setSimmulationIntervalMS(uint32_t interval);
    uint32_t getSimmulationIntervalMS();
    void setOutputCallback(const std::function<void(TickData)> callback);
    void resetSimmulation();

    void setGenerator(TypGeneratora type);
    TypGeneratora getGenerator();
    void setGeneneratorAmplitude(const double& amplitude);
    void setGeneneratorDutyCycle(const double& duty_cycle);
    void setGeneneratorPeriodMS(uint32_t period);
    void setGeneratorSkladowaStala(double skladowa_stala);
    uint8_t getGeneneratorPeriodJumpMS();
    void resetGenerator();

    void setPIDProportional(double k);
    void setPIDIntegration(double T_i);
    void setPIDDerrivative(double T_d);
    void setPIDIntegrationType(IntegType integration_type);
    void resetPIDIntegration();
    void resetPIDDerrivative();

    void setARXCoefficients(std::vector<double> a, std::vector<double> b);
    const std::vector<double> getARXCoefficientsA();
    const std::vector<double> getARXCoefficientsB();
    void setARXTransportDelay(uint16_t k);
    uint16_t getARXTransportDelay();
    void setARXInputLimits(double low, double high);
    const std::pair<double, double>& getARXInputLimits();
    void setARXOutputLimits(double low, double high);
    const std::pair<double, double>& getARXOutputLimits();
    void setARXNoiseStandardDeviation(double standard_deviation);
    double getARXNoiseStandardDeviation();
    void setARXLimitsEnabled(bool enabled);
    void resetARX();

    void setSaveStateObject(SaveStateInterface* object);
    void saveToFile(std::string path);
    void readFromFile(std::string path);

    const std::tuple<const ARX*, const RegulatorPID*, const TypGeneratora,  const GeneratorSinusoida*, const GeneratorProstokatny*> getAppState();


public slots:
    void tick();

private:
    UAR uar;
    GeneratorSinusoida gen_sin;
    GeneratorProstokatny gen_pros;
    Generator* choosen_generator;
    bool simmulation_running;
    QTimer *simmulation_timer;
    std::function<void(TickData)> tick_callback;
    SaveStateInterface* save;

    State(const State &) = delete;
    State &operator=(const State &) = delete;
    State();
    ~State();
};

class SaveStateInterface
{
public:
    virtual void saveToFile(std::string& path, UAR* uar, bool simmulation, State::TypGeneratora typ, GeneratorProstokatny* gen_pros, GeneratorSinusoida* gen_sin) = 0;
    virtual void readFromFile(std::string& path, UAR* uar, bool* simmulation, State::TypGeneratora* typ, GeneratorProstokatny* gen_pros, GeneratorSinusoida* gen_sin) = 0;
};


class StateGlobalAccess
{
public:
    State& operator()();
};
extern StateGlobalAccess State;
#endif // STATE_H
