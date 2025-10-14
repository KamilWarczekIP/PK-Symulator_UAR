#ifndef PID_H
#define PID_H

enum class IntegType
{
    outside,
    insde,
};

class PID
{
    double k;
    double T_i;
    double T_d;
    double sum_of_e;
    double previous_e;
    IntegType integration_type;
public:
    double tick(double e_i)
     PID(double T_d, double T_i, double k);
    void setK(double k);
    void setT_i(double T_i);
    void setT_d(double T_d);
    double getK();
    double getT_i();
    double getT_d();
    void reset();
};

#endif // PID_H
