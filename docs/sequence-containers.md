# 📘 Sequence Containers (C++98)

> `std::vector`, `std::deque`, `std::list`

## 🧭 What is a Sequence Container?

A **sequence container** stores elements in a **linear order**. You control element positions (begin/end/middle). Order is by **position**, not by key.

**Linear order** means elements are arranged in a single sequence. You accessed them with **position** and not by a key.

```
[ a ] → [ b ] → [ c ] → [ d ]
  ^       ^       ^       ^
pos 0    pos 1   pos 2   pos 3
```

The STL design separates containers (hold data) from algorithms (operate via iterators).

So you use free algorithms like std::find, std::find_if, std::lower_bound, etc., on iterator ranges.

---

## 🧩 Common Member Functions

**Capacity / size**

* `size()`, `empty()`, `max_size()`
* `resize(n[, value])`

**Element access**

* `front()`, `back()`
* `operator[]`, `at()` *(only `vector`, `deque`)*

**Iterators**

* `begin()`, `end()`, `rbegin()`, `rend()`
* Types: `iterator`, `const_iterator`, `reverse_iterator`, `const_reverse_iterator`

**Modifiers**

* `assign(...)`, `insert(pos, ...)`, `erase(pos[, last])`, `push_back()`, `pop_back()`, `clear()`, `swap()`

**Extras per container**

* **vector**: `capacity()`, `reserve(n)`
* **deque**: `push_front()`, `pop_front()` *(no `reserve`)*)
* **list**: `push_front()`, `pop_front()`, `splice`, `remove`, `remove_if`, `unique`, `merge`, `sort`, `reverse`

---

## 🚀 Typical Use Cases

### `std::vector` 🧱

* **Best for**: many reads, random access, push/pop at end.
* **Examples**: dynamic arrays, lookup tables, tight numeric loops.
* **Why**: contiguous memory → cache‑friendly & fastest iteration.

### `std::deque` 🚌

* **Best for**: fast push/pop at **both ends** plus random access.
* **Examples**: sliding windows, BFS queues with front/back ops.
* **Why**: segmented blocks allow O(1) end operations.

### `std::list` 🔗

* **Best for**: frequent insert/erase **in the middle** with stable iterators.
* **Examples**: job queues that reorder, splicing between lists.
* **Why**: doubly‑linked nodes → O(1) insert/erase **given iterator**.

---

## ⚖️ Deque vs List vs Vector — Pros & Cons

| Container  | Random Access |      Insert/Erase End |    Insert/Erase Middle | Memory locality |                                                 Iterator invalidation | Notes                                   |
| ---------- | ------------- | --------------------: | ---------------------: | --------------: | --------------------------------------------------------------------: | --------------------------------------- |
| **vector** | ✅ O(1)        | ✅ end: amortized O(1) |                 ❌ O(n) |  ⭐⭐⭐ contiguous | Reallocations invalidate **all**; middle ops invalidate from point on | Use `reserve()` to reduce reallocations |
| **deque**  | ✅ O(1)        |      ✅ both ends O(1) |                 ❌ O(n) |    ⭐⭐ segmented |      End ops usually keep most iterators valid; middle can invalidate | No `reserve()`                          |
| **list**   | ❌ O(n)        |                ✅ O(1) | ✅ O(1) (with iterator) |    ⭐ node‑based |                                 Iterators valid except at erased node | Has `splice/sort/merge/unique/reverse`  |

---

## 👣 Iterators: Do these containers have their own?

Yes. All three define iterator types.
**Categories**:

* `vector`, `deque`: **RandomAccessIterator**
* `list`: **BidirectionalIterator**

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v; v.push_back(3); v.push_back(1); v.push_back(4);
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << "\n";
    }
}
```

---

## ❓ Why `<algorithm>` then?

You **don’t** need `<algorithm>` just to iterate. `<algorithm>` provides generic algorithms (`std::find`, `std::sort`, `std::for_each`, …) that operate on iterator ranges of **any** container.

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<int> v; v.push_back(10); v.push_back(20);
    std::vector<int>::iterator it = std::find(v.begin(), v.end(), 20);
    if (it != v.end()) { std::cout << "Found: " << *it << "\n"; }
}
```

---

## 🧪 Complexity Cheat‑Sheet (typical)

* **vector**: `[]/at()` O(1); `push_back()` amortized O(1); middle `insert/erase` O(n)
* **deque**: random access O(1); `push_front/back()` O(1); middle `insert/erase` O(n)
* **list**: random access O(n); `insert/erase` with iterator O(1)

---

## 📎 C++98 Tips

* Put template definitions in headers (`.hpp` or included `.tpp`).
* `std::sort` requires **random access** → works for `vector`/`deque`, not `list`. Use `list::sort()`.
* `vector::reserve(n)` avoids frequent reallocation (keeps amortized O(1) `push_back`).
* Prefer explicit iterator types (no C++11 `auto`).
