#ifndef ARX_H
#define ARX_H
#include <cstdint>
#include <vector>
#include <deque>
#include "Test.h"

class ARX
{
    friend class Test;
private:
    std::vector<double> a;
    std::vector<double> b;
    uint16_t k;
    double standard_deviation;
    std::deque<double> y_i;
    std::deque<double> u_i;
    bool limits_active;
    std::pair<double, double> output_limits;
    std::pair<double, double> input_limits;
    inline double applyLimits(std::pair<double, double>& limits, double value);
    inline double getGaussianDistribValue();
public:
    ARX(std::vector<double>&& a, std::vector<double>&& b, uint16_t k = 1, double standard_deviation = 0.0);
    double tick(double u);
    void setK(uint16_t k);
    double getK();
    std::vector<double> getA();
    std::vector<double> getB();
    void setAB(std::vector<double> a, std::vector<double> b);
    void reset();
    void disableLimits();
    void enableLimits();
    void setInputLimits(double low, double high);
    void setOutputLimits(double low, double high);
    std::pair<double, double> getInputLimits();
    std::pair<double, double> getOutputLimits();
    void setStandardDeviation(double standard_deviation);
    double getStandardDeviation();
};

#endif // ARX_H
