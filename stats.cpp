// File Name: stats.cpp
// implemented from stats.h

#include <cassert>
#include "stats.h"
using namespace std;
using namespace CISP430_A1;

namespace CISP430_A1
{
    // CONSTRUCTOR
    statistician::statistician()
    {
        reset();
    }

    // MODIFICATION MEMBER FUNCTIONS
    void statistician::next(double r)
    {
        total += r;
        count++;

        if (count == 1 || r < tiniest)
        {
            tiniest = r;
        }
        if (count == 1 || r > largest)
        {
            largest = r;
        }
    }
    void statistician::reset()
    {
        count = 0;
        total = 0;
        tiniest = 0;
        largest = 0;
    }

    // CONSTANT MEMBER FUNCTIONS
    double statistician::mean() const // finds the mean in the sequence of numbers
    {
        assert(count > 0);
        return (total / count);
    }
    double statistician::minimum() const // finds the minimum in the sequence of numbers
    {
        assert(count > 0);
        return tiniest;
    }
    double statistician::maximum() const // finds the maximum in the sequence of numbers
    {
        assert(count > 0);
        return largest;
    }

    // FRIEND FUNCTIONS
    statistician operator+(const statistician &s1, const statistician &s2)
    {
        statistician output;
        output.count = s1.count + s2.count;
        output.total = s1.total + s2.total;
        
        if (s1.count == 0)
        {
            output = s2;
        }
        else if (s2.count == 0)
        {
            output = s1;
        }
        else
        {
            output.tiniest = (s1.tiniest <= s2.tiniest) ? s1.tiniest : s2.tiniest;
            output.largest = (s1.largest >= s2.largest) ? s1.largest : s2.largest;
        }
        return output;
    }
    statistician operator*(double scale, const statistician &s)
    {
        statistician output;

        output.total = s.total * scale;
        output.count = s.count;

        if (scale >= 0)
        {
            output.largest = s.largest * scale;
            output.tiniest = s.tiniest * scale;
        }
        else // else if scale is negative switch it
        {
            output.largest = s.tiniest * scale;
            output.tiniest = s.largest * scale;
        }

        return output;
    }
    bool operator==(const statistician &s1, const statistician &s2)
    {
        if ((s1.length() == 0) && (s2.length() == 0))
        {
            return true;
        }
        // Checks all the conditions
        if (!(s1.length() == s2.length()))
            return false;
        else if (!(s1.sum() == s2.sum()))
            return false;
        else if (!(s1.minimum() == s2.minimum()))
            return false;
        else if (!(s1.maximum() == s2.maximum()))
            return false;
        else if (!(s1.mean() == s2.mean()))
            return false;
        
        return true;
    }
}