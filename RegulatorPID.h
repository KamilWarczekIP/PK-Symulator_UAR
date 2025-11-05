#ifndef REGULATOR_PID_H
#define REGULATOR_PID_H

enum class IntegType
{
    outside,
    insde,
};

class RegulatorPID
{
    double k;
    double T_i;
    double T_d;
    double sum_of_e_inside_integ;
    double sum_of_e_outside_integ;
    double previous_e;
    IntegType integration_type;
public:
    double tick(double e_i);
    RegulatorPID(double k, double T_i = 0.0, double T_d = 0.0, IntegType integration_type = IntegType::outside);
    void setK(double k);
    void setT_i(double T_i);
    void setT_d(double T_d);
    void setIntegrationType(IntegType integ_type);
    IntegType getIntegrationType();
    double getK();
    double getT_i();
    double getT_d();
    void resetIntegrationPart();
    void resetDerrivativePart();
    void reset();
};

#endif // REGULATOR_PID_H
