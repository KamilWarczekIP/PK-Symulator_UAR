#include "Test.h"
#include "listwithextremes.hpp"

Test::Test()
    :test_info(QtDebugMsg)
{}

void Test::wykonajTesty()
{
    std::function<bool(void)> testy[] = {
        [this](){return this->TEST_ListWithExtremes_poprawne_dzialanie();},

    };
    for(auto& test : testy)
    {
        try
        {
            if(test())
                test_info << " [ OK ]";
            else
                test_info << "[ FAIL ]";
        }
        catch (...)
        {
            test_info << "[ FAIL ] (Exception)";
        }
    };

}

bool Test::TEST_ListWithExtremes_poprawne_dzialanie()
{
    this->test_info << "TEST_ListWithExtremes_poprawne_dzialanie";
    ListWithExtremes lista;

    lista.appendLastValue(QPointF(1.0, 4.0));
    if(lista.getMaxValue() != 4.0) return false;
    if(lista.getMinValue() != 4.0) return false;

    lista.appendLastValue(QPointF(1.1, 4.0));
    if(lista.getMaxValue() != 4.0) return false;
    if(lista.getMinValue() != 4.0) return false;

    lista.appendLastValue(QPointF(1.8, 7.0));
    if(lista.getMaxValue() != 7.0) return false;
    if(lista.getMinValue() != 4.0) return false;


    lista.appendLastValue(QPointF(1.8, 9.0));
    if(lista.getMaxValue() != 9.0) return false;
    if(lista.getMinValue() != 4.0) return false;

    lista.deleteFirstValue();
    lista.deleteFirstValue();
    if(lista.getMaxValue() != 9.0) return false;
    if(lista.getMinValue() != 7.0) return false;


    lista.appendLastValue(QPointF(1.8, -1.0));
    if(lista.getMaxValue() != 9.0) return false;
    if(lista.getMinValue() != -1.0) return false;
    return true;
}
