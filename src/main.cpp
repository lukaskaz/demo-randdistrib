#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

template <typename T>
concept Numerical = std::is_arithmetic_v<T>;

class RandomIf
{
  public:
    virtual ~RandomIf() = default;
    virtual void simulate(uint32_t, bool) = 0;
    static std::vector<std::shared_ptr<RandomIf>> items;
};

std::vector<std::shared_ptr<RandomIf>> RandomIf::items;

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

template <Numerical T = int32_t, typename U = std::uniform_int_distribution<T>>
class Uniform : public Random<T, U>
{
  public:
    explicit Uniform(const std::pair<T, T>& param) :
        Random<T, U>("uniform", U{param.first, param.second})
    {}
};

template <Numerical T = bool, typename U = std::bernoulli_distribution>
class Bernoulli : public Random<T, U>
{
  public:
    explicit Bernoulli(double param) : Random<T, U>("bernoulli", U{param})
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
    explicit Exponential(double param) : Random<T, U>("exponential", U{param})
    {}
};

template <Numerical T = int32_t, typename U = std::discrete_distribution<T>>
class Discrete : public Random<T, U>
{
  public:
    explicit Discrete(const std::initializer_list<double>& param) :
        Random<T, U>("discrete", U{param})
    {}
};

class Collector
{
  public:
    template <typename T, typename P>
    static void add(const P& param)
    {
        auto item = std::make_shared<T>(param);
        RandomIf::items.push_back(item);
    }
};

int main()
{
    Collector::add<Uniform<uint32_t>>(std::make_pair(0, 9));
    Collector::add<Uniform<double, std::uniform_real_distribution<double>>>(
        std::make_pair(4.0, 5.0));
    Collector::add<Bernoulli<bool>>(0.75);
    Collector::add<Gaussian<double>>(std::make_pair(5.0, 2.0));
    Collector::add<Exponential<double>>(1.25);
    Collector::add<Discrete<int32_t>>(
        std::initializer_list<double>{30, 10, 10, 30, 20});

    for (const auto& gen : RandomIf::items)
    {
        gen->simulate(200, true);
    }

    return 0;
}

