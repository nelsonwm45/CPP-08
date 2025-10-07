# 📘 Associative Containers (C++98)

> `std::set`, `std::multiset`, `std::map`, `std::multimap`

## 🧭 What is an Associative Container?

An **associative container** stores elements ordered by a **key** using a balanced tree (typically red‑black in C++98). You don’t control positions; the tree keeps elements **sorted by key**.

Iteration is still linear traversal of the structure, but it goes in sorted key order (in-order traversal of the tree), not “insertion order” and not by numeric index.

### Key View
```
          KEY SPACE
   ...  1   3   5   7   10  12  ...
        |   |   |   |   |   |
      (1) (3) (5) (7) (10) (12)   // set
      (1:A) (3:C) (5:E) ...       // map
```

1) std::set<int> (values are the keys)
```
            ( 7 )
           /     \
        ( 3 )    ( 10 )
        /  \        \
     ( 1 ) ( 5 )    ( 12 )

In-order traversal (sorted): 1 → 3 → 5 → 7 → 10 → 12
Iterator walk: begin() … end() follows that order.
```

2) std::map<int, char> (key → value pairs)
```
             ( 7 : 'g' )
             /         \
       ( 3 : 'c' )   ( 10 : 'j' )
        /      \            \
 ( 1 : 'a' ) ( 5 : 'e' )  ( 12 : 'l' )

In-order by key: (1:'a') → (3:'c') → (5:'e') → (7:'g') → (10:'j') → (12:'l')
Access: m[5] == 'e', m.find(10) → node (10:'j')
```

multiset / multimap = duplicates allowed
3) std::multiset<int> (duplicates group together in key order)
```
           ( 7 )
          /     \
      ( 3 )    ( 10 )
      /  \         \
   ( 1 ) ( 3 )    ( 10 )

In-order: 1 → 3 → 3 → 7 → 10 → 10
equal_range(3) gives the contiguous range of both 3's.
```

4) std::multimap<int, string> (key → many values)
```
             ( 7 : "g1" )
             /           \
   ( 3 : "c1" )        ( 10 : "j1" )
         \                 /     \
      ( 3 : "c2" )   ( 10 : "j2" ) ( 12 : "l1" )

Sorted by key, stable within equal keys (per insertion rules)
equal_range(10) spans: (10:"j1") → (10:"j2")
```

---

## 🧩 Common Member Functions (ordered associative)

**Capacity / size**

* `size()`, `empty()`, `max_size()`

**Iterators** *(BidirectionalIterator)*

* `begin()`, `end()`, `rbegin()`, `rend()`
* Iteration is in **sorted order**

**Lookup**

* `find(key)`, `count(key)`, `lower_bound(key)`, `upper_bound(key)`, `equal_range(key)`

**Modifiers**

* `insert(value)`, `erase(pos/key/range)`, `clear()`, `swap()`

**Observers**

* `key_comp()`, `value_comp()`

---

## 🧱 Container Summaries & Use Cases

### `std::set` 🔑

* **Holds**: unique keys, value == key (`T`)
* **Use cases**: fast membership tests, deduped & sorted collections
* **Ops**: `insert`, `find`, `erase` → **O(log n)**

### `std::multiset` 🔑🔁

* **Holds**: keys **with duplicates allowed**
* **Use cases**: frequency collections, multi‑buckets where order matters
* **Ops**: same as set; duplicates via `insert` / `equal_range`

### `std::map` 🗺️

* **Holds**: unique key → mapped value (`std::pair<const Key, T>`)
* **Use cases**: dictionaries, indexes, symbol tables
* **Ops**: `operator[]` inserts default if key missing; `insert`, `find` → **O(log n)**

### `std::multimap` 🗺️🔁

* **Holds**: key → multiple values (duplicate keys allowed)
* **Use cases**: one‑to‑many indexes (e.g., author → many books)
* **Ops**: no `operator[]`; use `insert`, `equal_range`

---

## ⚖️ Map vs Multiset vs Multimap vs Set — Pros & Cons

| Container    | Uniqueness | Duplicates |           Access by key | Value type             | Typical use                   |
| ------------ | ---------- | ---------: | ----------------------: | ---------------------- | ----------------------------- |
| **set**      | ✅          |          ❌ |   `find` (key is value) | `T`                    | sorted unique collection      |
| **multiset** | ❌          |          ✅ | range via `equal_range` | `T`                    | sorted collection with counts |
| **map**      | ✅          |          ❌ |    `operator[]`, `find` | `std::pair<const K,V>` | dictionary / lookup table     |
| **multimap** | ❌          |          ✅ |           `equal_range` | `std::pair<const K,V>` | one‑to‑many mapping           |

**Pros (associative)**

* Ordered traversal, logarithmic lookup/insert/erase (O(log n))
* Insertions usually keep iterators/refs valid; erasing only invalidates erased element

**Cons**

* No random access by index
* More pointer chasing than `vector` → slower iteration, higher memory overhead
* Always pays sorting cost even if not needed

---

## 👣 Do they have their own iterators?

Yes: `iterator`, `const_iterator`, `reverse_iterator`, `const_reverse_iterator` (all **Bidirectional**).
They traverse elements in **sorted key order**.

```cpp
#include <map>
#include <string>
#include <iostream>

int main() {
    std::map<std::string, int> freq;
    ++freq["apple"]; // inserts {"apple",0} then increments
    ++freq["apple"];
    freq.insert(std::make_pair("banana", 3));

    std::map<std::string,int>::iterator it = freq.find("banana");
    if (it != freq.end()) {
        std::cout << it->first << " => " << it->second << "\n";
    }
}
```

```cpp
#include <set>
#include <iostream>

int main() {
    std::set<int> s; s.insert(3); s.insert(1); s.insert(3); // duplicate ignored
    for (std::set<int>::const_iterator it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << "\n"; // prints 1, 3
    }
}
```

```cpp
#include <map>
#include <utility>
#include <iostream>

int main() {
    std::multimap<int, char> mm;
    mm.insert(std::make_pair(10, 'a'));
    mm.insert(std::make_pair(10, 'b'));
    std::pair<std::multimap<int,char>::iterator,
              std::multimap<int,char>::iterator> range = mm.equal_range(10);
    for (std::multimap<int,char>::iterator it = range.first; it != range.second; ++it) {
        std::cout << it->first << " -> " << it->second << "\n";
    }
}
```

---

## 🔁 Complexity (ordered associative)

* `insert`, `erase(key)`, `find`, `lower_bound`, `upper_bound` → **O(log n)**
* Iteration over all elements → **O(n)** (sorted)

---

## ⚔️ Sequence vs Associative — When to choose what?

| Aspect                  | Sequence (`vector/deque/list`)                    | Associative (`set/multiset/map/multimap`) |
| ----------------------- | ------------------------------------------------- | ----------------------------------------- |
| **Ordering**            | By position (you control)                         | By key (sorted automatically)             |
| **Lookup**              | By index O(1) (`vector/deque`); value search O(n) | By key O(log n)                           |
| **Random access**       | `vector/deque`: ✅; `list`: ❌                      | ❌                                         |
| **Insert/erase middle** | `vector/deque`: O(n); `list`: O(1) with iterator  | O(log n)                                  |
| **Memory locality**     | `vector` cache‑friendly                           | Node‑based, more overhead                 |
| **Use when**            | Tight loops, arrays, positional edits             | Always‑sorted sets/maps, key lookups      |

---

## 📎 C++98 Tips

* Prefer `std::pair<...>` + `std::make_pair` for inserts.
* `map::operator[]` may **insert**; use `find` if you only check existence.
* Iterator category is **Bidirectional**; algorithms requiring random access (e.g., `std::sort`) won’t work—rely on tree order or copy to a `vector`.
