#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <tuple>

template <typename T>
concept Numerical = std::is_arithmetic_v<T>;

template <Numerical T, typename U>
class Random
{
  public:
    Random(const std::string& type, U dist) : type{type}, gen{rd()}, dist{dist}
    {}
    virtual ~Random() = default;

    virtual T operator()()
    {
        return dist(gen);
    }

    virtual void simulate(uint32_t samples, bool round = true)
    {
        std::cout << "===== Simulation for distribution " << std::quoted(type)
                  << " started =====\n";
        std::map<T, uint32_t> hist;
        while (samples--)
            if (round)
                ++hist[std::round((*this)())];
            else
                ++hist[(*this)()];

        for (const auto& [x, y] : hist)
            std::cout << std::setw(2) << x << ' ' << std::string(y, '*')
                      << '\n';
        std::cout << "===== Simulation ended =====\n";
    }

  protected:
    std::string type;
    std::random_device rd;
    std::mt19937 gen;
    U dist;
};

template <Numerical T = int32_t, typename U = std::uniform_int_distribution<T>>
class Uniform : public Random<T, U>
{
  public:
    explicit Uniform(const std::pair<T, T>& param) :
        Random<T, U>("uniform", U{param.first, param.second})
    {}
};

template <Numerical T = double, typename U = std::normal_distribution<T>>
class Gaussian : public Random<T, U>
{
  public:
    explicit Gaussian(const std::pair<T, T>& param) :
        Random<T, U>("gaussian", U{param.first, param.second})
    {}
};

template <Numerical T = double, typename U = std::exponential_distribution<T>>
class Exponential : public Random<T, U>
{
  public:
    explicit Exponential(double param) :
        Random<T, U>("exponential", U{param})
    {}
};


int main()
{
    Uniform<uint32_t> uniform({0, 9});
    uniform.simulate(500);
    
    Gaussian<double> gaussian({5.0, 2.0});
    gaussian.simulate(500);

    Exponential<double> exponential(1.0);
    exponential.simulate(300);

    return 0;
}

