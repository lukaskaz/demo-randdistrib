#pragma once

#include "interfaces/randomgen.hpp"

#include <memory>

class Collector
{
  public:
    template <typename T, typename P>
    static void add(const P& param)
    {
        auto item = std::make_shared<T>(param);
        RandomIf::items.push_back(item);
    }

    static const decltype(RandomIf::items)& get()
    {
        return RandomIf::items;
    }
};

