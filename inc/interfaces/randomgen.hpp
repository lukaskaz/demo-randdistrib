#pragma once

#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

class RandomIf
{
  public:
    virtual ~RandomIf() = default;
    virtual void simulate(uint32_t, bool) = 0;
    static std::vector<std::shared_ptr<RandomIf>> items;
};
std::vector<std::shared_ptr<RandomIf>> RandomIf::items;

template <typename T>
concept Numerical = std::is_arithmetic_v<T>;

template <Numerical T, typename U>
class Random : public RandomIf
{
  public:
    Random(const std::string& type, U dist) : type{type}, gen{rd()}, dist{dist}
    {}

    T operator()()
    {
        return dist(gen);
    }

    void simulate(uint32_t samples, bool round) override
    {
        std::cout << "===== Simulation for distribution " << std::quoted(type)
                  << " started =====\n";
        std::map<T, uint32_t> hist;
        while (samples--)
            if (round)
                ++hist[(int32_t)std::round((*this)())];
            else
                ++hist[(*this)()];

        for (const auto& [x, y] : hist)
            std::cout << std::setw(2) << x << ' ' << std::string(y, '*') << " ("
                      << y << ")" << '\n';
        std::cout << "===== Simulation ended =====\n";
    }

  protected:
    std::string type;
    std::random_device rd;
    std::mt19937 gen;
    U dist;
};

