#ifndef UTILS_INCLUDE_H
#define UTILS_INCLUDE_H

#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>

namespace hs 
{

namespace utils 
{

bool route_match(std::string_view pattern, std::string_view target) 
{
    std::vector<std::string> pattern_segments;
    std::vector<std::string> target_segments;

    auto match = [] (auto c) { return c == '/'; };

    boost::algorithm::split(pattern_segments, 
                            std::string_view(pattern.data() + 1, pattern.size() - 1), 
                            match);

    boost::algorithm::split(target_segments, 
                            std::string_view(target.data() + 1, target.size() - 1), 
                            match);

    if (pattern_segments.size() != target_segments.size()) return false;

    for (size_t i = 0; i < pattern_segments.size() - 1; ++i)
    {
        if (pattern_segments[i] != target_segments[i]) return false;            
    }
    return true;
}

} // namespace utils

} // namespace hs

#endif