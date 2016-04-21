#include "MonotonicCubicSplineInterpolator.h"
#include <vector>
#include <cmath>
#include <fstream>

MonotonicCubicSplineInterpolator::MonotonicCubicSplineInterpolator( std::vector< std::pair<double, double> > dataPoints )
{
    mNumberOfPoints = dataPoints.size();

    for (int i = 0; i < mNumberOfPoints; i++)
    {
        struct dataRow myDataRow;
        myDataRow.x = dataPoints[i].first;
        myDataRow.y = dataPoints[i].second;

        mData.push_back( myDataRow );
    }
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
    for (int i = 0; i < mNumberOfPoints-1; i++)
    {
        double tmpValue = (mData[i+1].y - mData[i].y ) / (mData[i+1].x - mData[i].x );
        mData[i].delta = tmpValue;
    }

    for (int i = 1; i < mNumberOfPoints-1; i++)
    {
        double tmpValue = (mData[i].delta + mData[i-1].delta ) / 2.0;
        mData[i].m = tmpValue;
    }
    mData[0].m = mData[1].m;
    mData[mNumberOfPoints-1].m = mData[mNumberOfPoints-2].m;

    for (int i = 0; i < mNumberOfPoints-1; i++)
    {
        if (mData[i].delta == 0.0)
        {
            mData[i].m = 0.0;
            mData[i+1].m = 0.0;
        }
    }

    for (int i = 0; i < mNumberOfPoints-1; i++)
    {
        double tmpValue1 = (mData[i].m / mData[i].delta);
        mData[i].alpha = tmpValue1;
        double tmpValue2 = (mData[i+1].m / mData[i].delta);
        mData[i].beta = tmpValue2;

        if (mData[i].alpha < 0.0 || mData[i].beta < 0.0) {}
    }

    for (int i = 1; i < mNumberOfPoints-1; i++)
    {
        if (mData[i].alpha < 0.0 || mData[i-1].beta < 0.0) {mData[i].m = 0.0; }
    }

    for (int i = 1; i < mNumberOfPoints-1; i++)
    {
        double radius2 = mData[i].alpha * mData[i].alpha + mData[i].beta * mData[i].beta;

        if (radius2 > 9.0)
        {
            double tau = 3.0 / sqrt(radius2);
            mData[i].m   = tau * mData[i].alpha * mData[i].delta;
            mData[i+1].m = tau * mData[i].beta  * mData[i].delta;
        }
    }
    std::ofstream fileOut;
    fileOut.open(const_cast<char*>("InterpolationConstruct.txt"), std::ios::out);
    for (int i = 0; i < mNumberOfPoints-1; i++)
    {
        fileOut << mData[i].x << "\t" << mData[i].y << "\t" << mData[i].delta << "\t" << mData[i].m << "\t" << mData[i].alpha << "\t" << mData[i].beta << std::endl;
    }

    fileOut.close();
}

double MonotonicCubicSplineInterpolator::Interpolate(double x)
{
    double xLower, xUpper;
    double yLower, yUpper;
    double mLower, mUpper;

    for (int i = 1; i < mNumberOfPoints-1; i++)
    {
        if (mData[i].x <= x && mData[i+1].x >= x)
        {
            xLower = mData[i].x;
            xUpper = mData[i+1].x;
            yLower = mData[i].y;
            yUpper = mData[i+1].y;
            mLower = mData[i].m;
            mUpper = mData[i+1].m;
        }
    }

    double h = xUpper - xLower;
    double t = (x - xLower) / h;

    double interpolatedY =       yLower * Hermite00(t)
                           + h * mLower * Hermite10(t)
                           +     yUpper * Hermite01(t)
                           + h * mUpper * Hermite11(t);
    return interpolatedY;
}
