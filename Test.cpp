#include "Test.h"
#include "listwithextremes.hpp"
#include "State.h"
#include <random>

void Test::wykonajTesty()
{
    std::array testy = {
        TEST_ListWithExtremes_poprawne_dzialanie,
        TEST_State_czy_jest_signletonem,
        TEST_State_zapis_i_odczyt_z_pliku,
        TEST_Generator_Prostokatny_zmiana_okresu,
        TEST_Generator_Prostokatny_zmiana_amplitudy,
        TEST_Generator_Prostokatny_bias,
        TEST_Generator_Prostokatny_100_procent,
        TEST_Generator_Prostokatny_50_procent,
        TEST_Generator_Prostokatny_10_procent,
    };
    std::shuffle(testy.begin(), testy.end(), std::random_device() );


    std::map<const char*, bool> wyniki_testow;
    for(auto& test : testy)
    {
        auto wynik = test();
        wyniki_testow[wynik.second] = wynik.first;
    };

    for (auto& wynik : wyniki_testow)
    {
        if(!wynik.second)
        {
            qDebug() << wynik.first << " [ FAIL ]\n";
        }
    }
    qDebug() << "TESTY POMYŚLNE: [ "
             << std::count_if(wyniki_testow.begin(), wyniki_testow.end(),
                    [](std::pair<const char*, bool> wynik){return wynik.second;})
             << " / " << wyniki_testow.size() << " ]";

}

std::pair<bool, const char*> Test::TEST_ListWithExtremes_poprawne_dzialanie()
{
    try
    {
        ListWithExtremes lista;
        bool test_passed = true;

        lista.appendLastValue(QPointF(1.0, 4.0));
        if(lista.getMaxValue() != 4.0) test_passed = false;
        if(lista.getMinValue() != 4.0) test_passed = false;

        lista.appendLastValue(QPointF(1.1, 4.0));
        if(lista.getMaxValue() != 4.0) test_passed = false;
        if(lista.getMinValue() != 4.0) test_passed = false;

        lista.appendLastValue(QPointF(1.8, 7.0));
        if(lista.getMaxValue() != 7.0) test_passed = false;
        if(lista.getMinValue() != 4.0) test_passed = false;


        lista.appendLastValue(QPointF(1.8, 9.0));
        if(lista.getMaxValue() != 9.0) test_passed = false;
        if(lista.getMinValue() != 4.0) test_passed = false;

        lista.deleteFirstValue();
        lista.deleteFirstValue();
        if(lista.getMaxValue() != 9.0) test_passed = false;
        if(lista.getMinValue() != 7.0) test_passed = false;


        lista.appendLastValue(QPointF(1.8, -1.0));
        if(lista.getMaxValue() != 9.0)  test_passed = false;
        if(lista.getMinValue() != -1.0) test_passed = false;
        return std::make_pair(test_passed, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> Test::TEST_State_czy_jest_signletonem()
{
    try
    {

        State* adres_State1 = &State::getInstance();
        State* adres_State2 = &State::getInstance();

        return std::make_pair(adres_State1 == adres_State2, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> Test::TEST_State_zapis_i_odczyt_z_pliku()
{
    try
    {
        bool test_passed = true;
        State::getInstance().setGeneneratorAmplitude(1.0);
        State::getInstance().setGeneneratorPeriodMS(100);
        State::getInstance().setGeneneratorDutyCycle(1.0);
        State::getInstance().setGenerator(State::TypGeneratora::Prostokatny);
        State::getInstance().setARXCoefficients({1.0, 2.0, 3.0, 4.0}, {1.0, 2.0, 3.0, 4.0});
        State::getInstance().setARXTransportDelay(1);
        State::getInstance().setARXNoiseStandardDeviation(1.0);
        //TODO RESZTA PARAMATROW DO ZAPISU

        State::getInstance().saveToFile();
        State::getInstance().setGeneneratorAmplitude(5.0);
        State::getInstance().setGeneneratorPeriodMS(500);
        State::getInstance().setGeneneratorDutyCycle(5.0);
        State::getInstance().setGenerator(State::TypGeneratora::Sinusoidalny);
        State::getInstance().setARXCoefficients({5.0, 6.0, 7.0, 8.0}, {5.0, 6.0, 7.0, 8.0});
        State::getInstance().setARXTransportDelay(2);
        State::getInstance().setARXNoiseStandardDeviation(5.0);

        State::getInstance().readFromFile();
        if(State::getInstance().getARXCoefficientsA() != std::vector({1.0, 2.0, 3.0, 4.0}))
            test_passed = false;


        return std::make_pair(test_passed, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> Test::TEST_Generator_Prostokatny_zmiana_amplitudy()
{

    try
    {
        bool test_passed = true;
        GeneratorProstokatny gen;
        gen.setBias(0.0);
        gen.setSamplesPerCycle(2);
        gen.setDutyCycle(1.0);

        gen.setAmplitude(10.0);
        if(gen.tick() != 10.0) test_passed = false;

        gen.setAmplitude(5.4);
        if(gen.tick() != 5.4) test_passed = false;

        gen.setAmplitude(0.0);
        if(gen.tick() != 0.0) test_passed = false;

        gen.setAmplitude(515.0);
        if(gen.tick() != 515.0) test_passed = false;
        return std::make_pair(test_passed, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> Test::TEST_Generator_Prostokatny_zmiana_okresu()
{

    try
    {
        bool test_passed = true;
        GeneratorProstokatny gen;
        gen.setBias(0.0);
        gen.setSamplesPerCycle(2);
        gen.setDutyCycle(1.0);
        gen.setAmplitude(1.0);

        gen.setSamplesPerCycle(2);
        if(gen.tick() != 1.0) test_passed = false;

        gen.setSamplesPerCycle(100);
        if(gen.tick() != 1.0) test_passed = false;

        gen.setSamplesPerCycle(7);
        if(gen.tick() != 1.0) test_passed = false;

        gen.setSamplesPerCycle(100);
        if(gen.tick() != 1.0) test_passed = false;
        return std::make_pair(test_passed, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> Test::TEST_Generator_Prostokatny_bias()
{

    try
    {
        bool test_passed = true;
        GeneratorProstokatny gen;
        gen.setBias(0.0);
        gen.setSamplesPerCycle(2);
        gen.setDutyCycle(1.0);
        gen.setAmplitude(1.0);

        gen.setBias(0.0);
        if(gen.tick() != 1.0) test_passed = false;

        gen.setBias(1.0);
        if(gen.tick() != 2.0) test_passed = false;

        gen.setBias(-1.0);
        if(gen.tick() != 0.0) test_passed = false;

        return std::make_pair(test_passed, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> Test::TEST_Generator_Prostokatny_100_procent()
{

    try
    {
        bool test_passed = true;
        GeneratorProstokatny gen;
        gen.setBias(0.0);
        gen.setSamplesPerCycle(2);
        gen.setDutyCycle(1.0);
        gen.setAmplitude(1.0);

        if(gen.tick() != 1.0) test_passed = false;
        if(gen.tick() != 1.0) test_passed = false;
        if(gen.tick() != 1.0) test_passed = false;
        if(gen.tick() != 1.0) test_passed = false;
        if(gen.tick() != 1.0) test_passed = false;

        return std::make_pair(test_passed, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> Test::TEST_Generator_Prostokatny_50_procent()
{

    try
    {
        bool test_passed = true;
        GeneratorProstokatny gen;
        gen.setBias(0.0);
        gen.setSamplesPerCycle(6);
        gen.setDutyCycle(0.5);
        gen.setAmplitude(1.0);

        gen.resetClock();
        if(gen.tick() != 1.0) test_passed = false;
        if(gen.tick() != 1.0) test_passed = false;
        if(gen.tick() != 1.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 1.0) test_passed = false;

        return std::make_pair(test_passed, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> Test::TEST_Generator_Prostokatny_10_procent()
{

    try
    {
        bool test_passed = true;
        GeneratorProstokatny gen;
        gen.setBias(0.0);
        gen.setSamplesPerCycle(10);
        gen.setDutyCycle(0.1);
        gen.setAmplitude(1.0);

        gen.resetClock();
        if(gen.tick() != 1.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 0.0) test_passed = false;
        if(gen.tick() != 1.0) test_passed = false;

        return std::make_pair(test_passed, __FUNCTION__);
    }
    catch(...)
    {
        return std::make_pair(false, __FUNCTION__);
    }
}
std::pair<bool, const char*> TEST_Generator_Sinusoidalny();
std::pair<bool, const char*> TEST_Generator_Sinusoidalny_bias();
std::pair<bool, const char*> TEST_Generator_Sinusoidalny_zmiana_amplitudy();
std::pair<bool, const char*> TEST_Generator_Sinusoidalny_zmiana_okresu();
