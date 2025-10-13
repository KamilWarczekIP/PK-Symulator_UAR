#include "ARX.h"
#include <stdexcept>


ARX::ARX(std::vector<double>&& a, std::vector<double>&& b, uint16_t k, double z)
{
    if(a.size() != b.size())
        throw std::invalid_argument("Rozmiary wektorów wspołaczynników a i b są różne");
    if(k < 1)
        throw std::invalid_argument("K nie moze byc mniejsze od 1");
    this->a = a;
    this->b = b;
    this->k = k;
    this->z = z;
    u_i = std::vector<double>(a.size() + k, 0);
    y_i = std::vector<double>(a.size(), 0);
}
double ARX::tick(double u)
{

    double y = 0.0;
    for(int i = 0; i < a.size(); i++)
    {
        y += b[i] * u_i[i + k - 1];
        y -= a[i] * y_i[i];
    }

    y += (rand() / RAND_MAX + 0.5) * z;

    u_i.insert(u_i.begin(), u);
    y_i.insert(y_i.begin(), y);

    if(u_i.size() > a.size() + k)
    {
        u_i.pop_back();
    }
    if(y_i.size() > a.size())
    {
        y_i.pop_back();
    }

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
