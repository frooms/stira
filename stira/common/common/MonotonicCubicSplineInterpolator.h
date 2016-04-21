#ifndef MONOTONICCUBICSPLINEINTERPOLATOR_H
#define MONOTONICCUBICSPLINEINTERPOLATOR_H

#include <vector>
// UNDER CONSTRUCTION
//https://en.wikipedia.org/wiki/Monotone_cubic_interpolation
//http://math.stackexchange.com/questions/45218/implementation-of-monotone-cubic-interpolation

struct dataRow
{
    double x     = -1.0;
    double y     = -1.0;
    double delta = -1.0;
    double m     = -1.0;
    double alpha = -1.0;
    double beta  = -1.0;
};

class MonotonicCubicSplineInterpolator
{
public:
    MonotonicCubicSplineInterpolator( std::vector< std::pair<double, double> > dataPoints );

    double Hermite00(double t);

    double Hermite10(double t);

    double Hermite01(double t);

    double Hermite11(double t);

    void CreateInterpolant( );

    double Interpolate(double x);

private:
    std::vector<dataRow> mData;
    int mNumberOfPoints;
};

#endif // MONOTONICCUBICSPLINEINTERPOLATOR_H
