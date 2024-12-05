#pragma once

#include "interfaces/randomgen.hpp"

template <Numerical T = double, typename U = std::normal_distribution<T>>
class Gaussian : public Random<T, U>
{
  public:
    explicit Gaussian(const std::pair<T, T>& param) :
        Random<T, U>("gaussian", U{param.first, param.second})
    {}
};

