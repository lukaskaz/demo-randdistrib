#pragma once

#include "interfaces/randomgen.hpp"

template <Numerical T = int32_t, typename U = std::discrete_distribution<T>>
class Discrete : public Random<T, U>
{
  public:
    explicit Discrete(const std::initializer_list<double>& param) :
        Random<T, U>("discrete", U{param})
    {}
};

