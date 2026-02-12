# CPP Module 08

## 📝 Overview

This module dives into the **Standard Template Library (STL)**. It covers **Templated Containers**, **Iterators**, and **Algorithms**.

## 📝 Overview

This module dives into the **Standard Template Library (STL)**. It covers **Templated Containers**, **Iterators**, and **Algorithms**.

For a deeper dive into the specific container types, check out the notes:
*   [Sequence Containers](docs/sequence-containers.md) (`vector`, `deque`, `list`)
*   [Associative Containers](docs/associative-containers.md) (`map`, `set`, `multimap`, `multiset`)
*   [Container Adaptors](docs/container-adaptor.md) (`stack`, `queue`, `priority_queue`)

## 📂 Project Structure

### ex00: Easy find
Introduction to STL Algorithms.
*   **`easyfind` Function Template**: 
    *   Accepts a container strictly as type `T` and an integer `value`.
    *   Uses `std::find` to locate the first occurrence of the value.
    *   **Returns**: An iterator to the found element.
    *   **Exception**: Throws `ElementNotFoundException` if the value is not found.

### ex01: Span
Introduction to STL Containers and Algorithms.
*   **`Span` Class**: manages a collection of numbers (using `std::vector<int>`).
    *   **Construction**: initialized with a maximum capacity `N`.
    *   **`addNumber(int)`**: Adds a single number. Throws `StorageIsFullException` if full.
    *   **`addRange(it, it)`**: Adds a range of numbers using iterators (efficiently using `std::vector::insert`).
    *   **`shortestSpan()`**: Finds the smallest difference between any two numbers.
        *   Implementation: Sorts the vector and checks adjacent differences.
    *   **`longestSpan()`**: Finds the largest difference between any two numbers.
        *   Implementation: `max_element` - `min_element`.
    *   **Exceptions**: Throws `InsufficientElementException` if there are fewer than 2 numbers.

### ex02: Mutated Abomination
Introduction to Container Adapters and underlying containers.
*   **`MutantStack<T>` Class Template**:
    *   Inherits from `std::stack<T>`.
    *   **Goal**: `std::stack` is a container adapter and does not expose iterators by default. This class exposes the underlying container (member `c`) to allow iteration.
    *   **Iterators**: Provides `begin()`, `end()`, `rbegin()`, `rend()` (and their const versions).
    *   **Usage**: Can be used exactly like a standard stack, but also allows you to iterate through it like a `std::list` or `std::deque`.

## 🛠️ Compilation & Usage

Each exercise has its own `Makefile`.

### ex00
```bash
cd ex00
make
./easyfind
```

### ex01
```bash
cd ex01
make
./Span
```

### ex02
```bash
cd ex02
make
./MutatedStack
```

## 🧹 Housekeeping
To clean up object files and executables in any directory:
```bash
make clean
make fclean
```
