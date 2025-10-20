#include "ARX.h"
#include <stdexcept>
#include <random>

double ARX::getGaussianDistribValue()
{
    static std::random_device random_device{};
    static std::mt19937 generator{random_device()};
    std::normal_distribution<double> distribution(0.0, standard_deviation);
    return distribution(generator);
}
double ARX::applyLimits(std::pair<double, double>& limits, double value)
{
    if(limits_active)
        return std::max(std::min(value, limits.second), limits.first);
    else
        return value;
}
ARX::ARX(std::vector<double>&& a, std::vector<double>&& b, uint16_t k, double standard_deviation)
    : limits_active(true), input_limits(std::make_pair(-10.0, 10.0)),
    output_limits(std::make_pair(-10.0, 10.0))
{
    if(a.size() != b.size())
        throw std::invalid_argument("Rozmiary wektorów wspołaczynników a i b są różne");
    if(k < 1)
        throw std::invalid_argument("K nie moze byc mniejsze od 1");
    this->a = a;
    this->b = b;
    this->k = k;
    this->standard_deviation = standard_deviation;
    u_i = std::vector<double>(a.size() + k, 0);
    y_i = std::vector<double>(a.size(), 0);
}
double ARX::tick(double u)
{
    u = applyLimits(input_limits, u);
    double y = 0.0;
    for(int i = 0; i < a.size(); i++)
    {
        y += b[i] * u_i[i + k - 1];
        y -= a[i] * y_i[i];
    }

    y += getGaussianDistribValue();

    y = applyLimits(output_limits, y);

    u_i.insert(u_i.begin(), u);
    y_i.insert(y_i.begin(), y);
    u_i.pop_back();
    y_i.pop_back();

    return y;
}
void ARX::setK(uint16_t k)
{
    if(k < 1)
        throw std::invalid_argument("K nie moze byc mniejsze od 1");
    this-> k = k;
}
double ARX::getK()
{
    return k;
}
std::vector<double> ARX::getA()
{
    return a;
}
std::vector<double> ARX::getB()
{
    return b;
}
void ARX::setAB(std::vector<double> a, std::vector<double> b)
{
    if(a.size() != b.size())
        throw std::invalid_argument("Rozmiary wektorów wspołaczynników a i b są różne");
    this->a = a;
    this->b = b;
}
void ARX::reset()
{
    u_i = std::vector<double>(a.size(), 0);
    y_i = std::vector<double>(a.size(), 0);
}
void ARX::disableLimits()
{
    this->limits_active = false;
}
void ARX::enableLimits()
{
    this->limits_active = true;
}

void ARX::setInputLimits(double low, double high)
{
    if(low >= high)
        throw std::invalid_argument("Dolne ograniczenie nie może być wyższe niż górne");
    this->input_limits = std::make_pair(low, high);
}
void ARX::setOutputLimits(double low, double high)
{
    if(low >= high)
        throw std::invalid_argument("Dolne ograniczenie nie może być wyższe niż górne");
    this->output_limits = std::make_pair(low, high);
}
std::pair<double, double> ARX::getInputLimits()
{
    return this->input_limits;
}
std::pair<double, double> ARX::getOutputLimits()
{
    return this->output_limits;
}
void ARX::setStandardDeviation(double standard_deviation)
{
    this->standard_deviation = standard_deviation;
}
double ARX::getStandardDeviation()
{
    return standard_deviation;
}
