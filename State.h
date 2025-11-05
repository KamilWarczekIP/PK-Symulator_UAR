#ifndef STATE_H
#define STATE_H
#include "UAR.h"
#include "GeneratorProstokatny.h"
#include "GeneratorSinusoida.h"
#include <QTimer>
#include <QObject>

class State : public QObject
{
    Q_OBJECT

    UAR uar;
    GeneratorSinusoida gen_sin;
    GeneratorProstokatny gen_pros;
    bool symulacja_dziala;
    Generator* wybrany_generator;
    QTimer* symulacja_timer;
    //bool natychmiastowa_edycja;

    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(UAR&&);
    ~State();
public:
    static State& getInstance();
    UAR& getUAR();
    GeneratorSinusoida& getGeneratorSinusoida();
    GeneratorProstokatny& getGeneratorProstokatny();
    ARX& getARX();
    RegulatorPID& getPID();
    void setSymulacjaDziala(bool symulacja_dziala);
    void setInterwalSymulacjiMS(uint32_t interwal);
    bool getSymulacjaDziala();
    uint32_t getInterwalSymulacjiMS();
    void setGenerator(Generator* generator);
public slots:
    void tick();
signals:
    void sendTickDataToMainWindow(TickData tick_data);
};

#endif // STATE_H
