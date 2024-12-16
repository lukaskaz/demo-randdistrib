#include "random/generators/bernoulli.hpp"
#include "random/generators/discrete.hpp"
#include "random/generators/exponential.hpp"
#include "random/generators/gaussian.hpp"
#include "random/generators/uniform.hpp"

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

    for (const auto& randomgen : Collector::get())
    {
        randomgen->simulate(200, true);
    }

    return 0;
}
