/**
 * @file MapType.h
 * @brief A C++20 concept that constrains templates to standard associative map containers.
 *
 * Provides:
 *   - maptype::is_specialization_of : compile-time check whether a type is an
 *                                     instantiation of a given class template.
 *   - maptype::MapType              : concept satisfied by std::map and
 *                                     std::unordered_map (any cv/ref qualification).
 *
 * Example:
 * @code
 *   template <maptype::MapType T>
 *   void PrintMap(const T& map);
 * @endcode
 *
 * Requires C++20 or later.
 */

#pragma once

#include <map>
#include <type_traits>
#include <unordered_map>

namespace maptype
{
    /**
     * @brief True if @p T is a specialization of the class template @p Template.
     *
     * Primary template: any type that does not match the partial
     * specialization below is not a specialization of @p Template.
     *
     * @tparam T        The type to inspect.
     * @tparam Template The class template to compare against (e.g. std::map).
     *
     * @note Works only for templates whose parameters are all types. Templates
     *       with non-type parameters (e.g. std::array<T, N>) are not supported.
     */
    template <typename T, template <typename...> class Template>
    inline constexpr bool is_specialization_of = false;

    /**
     * @brief Partial specialization chosen when @p T has the form Template<Args...>.
     */
    template <template <typename...> class Template, typename... Args>
    inline constexpr bool is_specialization_of<Template<Args...>, Template> = true;

    /**
     * @brief Satisfied when @p T is a std::map or std::unordered_map.
     *
     * const, volatile and reference qualifiers are stripped before the check,
     * so `const std::map<K, V>&` also satisfies the concept. Custom comparators,
     * hashers and allocators are accepted.
     *
     * @tparam T The type to constrain.
     */
    template <typename T>
    concept MapType = is_specialization_of<std::remove_cvref_t<T>, std::map>
                   || is_specialization_of<std::remove_cvref_t<T>, std::unordered_map>;
}
