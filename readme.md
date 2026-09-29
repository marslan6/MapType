# MapType

A tiny, header-only C++20 concept that restricts templates to standard map containers: `std::map` and `std::unordered_map`.

```cpp
#include "MapType.h"

template <maptype::MapType Map>
void PrintMap(const Map& map);
```

Pass a `std::map` or `std::unordered_map` and it compiles. Pass anything else, such as a `std::vector` or a `std::set`, and the compiler reports a clear constraint error at the call site instead of a long template error from inside the function.

## Features

- **Header-only.** Copy one file into your project; there is nothing to build.
- **No dependencies.** Uses the standard library only.
- **Ignores qualifiers.** `const`, `volatile` and references are stripped, so `const std::map<K, V>&` satisfies the concept.
- **Allows custom parameters.** Maps with custom comparators, hashers or allocators are accepted.
- **Includes a reusable trait.** `maptype::is_specialization_of<T, Template>` tells you whether a type is an instantiation of any class template.

## Requirements

| Component | Standard | Compilers |
|---|---|---|
| `MapType.h` | C++20 | GCC 10+, Clang 10+, MSVC 19.28+ |
| `main.cpp` example | C++23 (uses `<print>`) | GCC 14+, Clang 18+ with libc++ 17+, MSVC 19.37+ |

## Installation

Copy [MapType.h](MapType.h) into your include path:

```cpp
#include "MapType.h"
```

## Usage

### Constraining a function

```cpp
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "MapType.h"

template <maptype::MapType Map>
std::size_t CountEntries(const Map& map)
{
    return map.size();
}

int main()
{
    std::map<int, std::string> ordered{ {1, "one"} };
    std::unordered_map<std::string, int> hashed{ {"one", 1} };

    CountEntries(ordered);              // OK
    CountEntries(hashed);               // OK
    // CountEntries(std::vector<int>{}); // Error: constraints not satisfied
}
```

### Compile-time checks

```cpp
static_assert(maptype::MapType<std::map<int, int>>);
static_assert(maptype::MapType<const std::unordered_map<int, int>&>);
static_assert(!maptype::MapType<std::vector<int>>);
```

### Using the `is_specialization_of` trait

```cpp
#include <vector>

static_assert(maptype::is_specialization_of<std::vector<int>, std::vector>);
static_assert(!maptype::is_specialization_of<std::vector<int>, std::map>);
```

## API reference

### `maptype::MapType<T>`

A concept. It is satisfied when `std::remove_cvref_t<T>` is a specialization of `std::map` or `std::unordered_map`.

### `maptype::is_specialization_of<T, Template>`

An `inline constexpr bool`. It is `true` when `T` has the form `Template<Args...>`, and `false` otherwise.

`is_specialization_of` does not strip qualifiers from `T`. Apply `std::remove_cvref_t` yourself if you need that.

## Limitations

- Only `std::map` and `std::unordered_map` satisfy the concept. `std::multimap`, `std::unordered_multimap`, `std::flat_map` and third-party maps such as `absl::flat_hash_map` do not.
- `is_specialization_of` supports only templates whose parameters are all types. It cannot match templates with non-type parameters, such as `std::array<T, N>`.
- Types derived from `std::map` do not satisfy the concept, because the trait matches the exact template.

## Building the example

```bash
g++ -std=c++23 -Wall -Wextra -Wpedantic main.cpp -o maptype_example
./maptype_example
```

Sample output (the order of the `std::unordered_map` entries may differ):

```
0) 1 : one
1) 2 : two
2) 3 : three
0) 3 : three
1) 2 : two
2) 1 : one
```

## Contributing

Issues and pull requests are welcome. Please keep changes header-only and dependency-free, and add a `static_assert` for any newly supported container.

## License

<!-- TODO: choose a license (for example MIT) and add a LICENSE file. -->
See [LICENSE](LICENSE).
