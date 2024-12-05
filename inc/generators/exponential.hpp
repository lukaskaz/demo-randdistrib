#pragma once

#include "interfaces/randomgen.hpp"

template <Numerical T = double, typename U = std::exponential_distribution<T>>
class Exponential : public Random<T, U>
{
  public:
    explicit Exponential(double param) : Random<T, U>("exponential", U{param})
    {}
};

