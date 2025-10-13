#ifndef ARX_H
#define ARX_H
#include <cstdint>
#include <vector>

class ARX
{
    std::vector<double> a;
    std::vector<double> b;
    uint16_t k;
    double z;
    std::vector<double> y_i;
    std::vector<double> u_i;
public:
    ARX(std::vector<double>&& a, std::vector<double>&& b, uint16_t k = 1, double z = 0.0);
    double tick(double u);
    void setK(uint16_t k);
    double getK();
    std::vector<double> getA();
    std::vector<double> getB();
    void setAB(std::vector<double> a, std::vector<double> b);
    void reset();
};

#endif // ARX_H
