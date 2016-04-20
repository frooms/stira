#include "MonotonicCubicSplineInterpolator.h"
#include <vector>
#include <algorithm>



MonotonicCubicSplineInterpolator::MonotonicCubicSplineInterpolator(std::vector<double> xsIn, std::vector<double> ysIn )
{
    xs = xsIn;
    ys = ysIn;
}

double MonotonicCubicSplineInterpolator::Hermite00(double t)
{
    return (2.0 * t*t*t -3.0*t*t + 1.0);
}

double MonotonicCubicSplineInterpolator::Hermite10(double t)
{
    return ( t*t*t -2.0*t*t + t );
}

double MonotonicCubicSplineInterpolator::Hermite01(double t)
{
    return (-2.0 * t*t*t + 3.0*t*t );
}

double MonotonicCubicSplineInterpolator::Hermite11(double t)
{
    return ( t*t*t - t*t );
}

void MonotonicCubicSplineInterpolator::CreateInterpolant()
{
    for (int i = 0; i < xs.size()-1; i++)
    {
        deltaK.push_back(  (ys[i+1] - ys[i]) / (xs[i+1] / xs[i]) );
    }

}

double MonotonicCubicSplineInterpolator::Interpolate(double x)
{
    double xLower, xHigher;

    for (int i = 0; i < xs.size()-1; i++)
    {
        if (xs[i] >= x && xs[i+1] <= x)
        {
            xLower = xs[i];
            xHigher = xs[i+1];
        }
    }
    return 0.0;
}
