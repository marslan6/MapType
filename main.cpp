/**
 * @file main.cpp
 * @brief Example usage of the maptype::MapType concept.
 *
 * Demonstrates a single function template, constrained by maptype::MapType,
 * that accepts both std::map and std::unordered_map.
 *
 * Requires C++23 (for <print>).
 */

#include <cstddef>
#include <map>
#include <print>
#include <string>
#include <unordered_map>

#include "MapType.h"

namespace
{
    /**
     * @brief Prints every key/value pair of a map, prefixed with its position.
     *
     * Only std::map and std::unordered_map are accepted; passing any other
     * type (e.g. std::vector) fails to compile with a concept error.
     *
     * @tparam Map A type satisfying maptype::MapType.
     * @param  map The map whose entries are printed.
     */
    template <maptype::MapType Map>
    void PrintMap(const Map& map)
    {
        // C++20 range-for with an init-statement keeps the counter scoped to the loop.
        for (std::size_t index = 0; const auto& [key, value] : map)
        {
            std::println("{}) {} : {}", index++, key, value);
        }
    }
}

int main()
{
    // Ordered map: entries are printed in ascending key order.
    const std::map<int, std::string> orderedMap{
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    // Hash map: iteration order is unspecified.
    const std::unordered_map<int, std::string> unorderedMap{
        {1, "one"},
        {2, "two"},
        {3, "three"}
    };

    PrintMap(orderedMap);
    PrintMap(unorderedMap);

    // PrintMap(std::vector<int>{});  // Does not compile: std::vector is not a MapType.
}
