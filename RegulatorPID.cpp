#include "RegulatorPID.h"

/**
 * @brief PID::tick metoda symulacji pojedynczego kroku regulatora
 * @param e_i - dane wejściowe w danym momencie czasu
 * @return wartość przekazywana do obiektu ARX
 */
double RegulatorPID::tick(double e_i)
{
    double u_i_P = k * e_i;
    double u_i_I;


    if(T_i == 0.0)
        u_i_I = 0;
    else
    {
        sum_of_e_outside_integ += e_i;
        sum_of_e_inside_integ += e_i / T_i;
        if(integration_type == IntegType::outside)
        {
            u_i_I = sum_of_e_outside_integ / T_i;
        }
        else // IntegType::inside
        {
            u_i_I = sum_of_e_inside_integ;
        }
    }


    double u_i_D = T_d * (e_i - previous_e);
    previous_e = e_i;

    return u_i_P + u_i_I + u_i_D;
}

RegulatorPID::RegulatorPID(double k, double T_i, double T_d, IntegType integration_type)
    :T_d(T_d), T_i(T_i), k(k), integration_type(integration_type)
{
    resetIntegrationPart();
}
void RegulatorPID::setK(double k)
{
    this->k = k;
}
void RegulatorPID::setT_i(double T_i)
{
    this->T_i = T_i;
}
void RegulatorPID::setT_d(double T_d)
{
    this->T_d = T_d;
}
void RegulatorPID::setIntegrationType(IntegType integ_type)
{
    if(this->integration_type != integ_type)
    {
        this->integration_type = integ_type;
        if(integ_type == IntegType::outside)
            sum_of_e_outside_integ = sum_of_e_inside_integ * T_i;
        else
            sum_of_e_inside_integ = sum_of_e_outside_integ / T_i;
    }
}
IntegType RegulatorPID::getIntegrationType()
{
    return integration_type;
}
double RegulatorPID::getK()
{
    return k;
}
double RegulatorPID::getT_i()
{
    return T_i;
}
double RegulatorPID::getT_d()
{
    return T_d;
}
void RegulatorPID::resetIntegrationPart()
{
    sum_of_e_inside_integ = 0.0;
    sum_of_e_outside_integ = 0.0;
}
void RegulatorPID::resetDerrivativePart()
{
    previous_e = 0.0;
}
void RegulatorPID::reset()
{
    resetDerrivativePart();
    resetIntegrationPart();
}

