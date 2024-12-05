#pragma once

#include "interfaces/randomgen.hpp"

template <Numerical T = bool, typename U = std::bernoulli_distribution>
class Bernoulli : public Random<T, U>
{
  public:
    explicit Bernoulli(double param) : Random<T, U>("bernoulli", U{param})
    {}
};

