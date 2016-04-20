#ifndef MONOTONICCUBICSPLINEINTERPOLATOR_H
#define MONOTONICCUBICSPLINEINTERPOLATOR_H

#include <vector>
// UNDER CONSTRUCTION
//https://en.wikipedia.org/wiki/Monotone_cubic_interpolation
class MonotonicCubicSplineInterpolator
{
public:
    MonotonicCubicSplineInterpolator( std::vector<double> xsIn, std::vector<double> ysIn );

    double Hermite00(double t);

    double Hermite10(double t);

    double Hermite01(double t);

    double Hermite11(double t);

    void CreateInterpolant( );

    double Interpolate(double x);

private:
    std::vector<double> xs;
    std::vector<double> ys;
    std::vector<double> deltaK, mK, alphaK, betaK;
};

#endif // MONOTONICCUBICSPLINEINTERPOLATOR_H
