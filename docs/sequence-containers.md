# 📘 Sequence Containers (C++98)

> `std::vector`, `std::deque`, `std::list`

## 🧭 What is a Sequence Container?

A **sequence container** stores elements in a **linear order**. You control element positions (begin/end/middle). Order is by **position**, not by key.

**Linear order** means elements are arranged in a single sequence. You accessed them with **position** and not by a key.

### Index View

```
[ a ] → [ b ] → [ c ] → [ d ]
  ^       ^       ^       ^
pos 0    pos 1   pos 2   pos 3
```

* The STL design separates containers (hold data) from algorithms (operate via iterators).

* Use free algorithms like std::find, std::find_if, std::lower_bound, etc., on iterator ranges.

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

Contiguous dynamic array (elements live back-to-back in one block)

```
begin →  ┌───┬───┬────┬───┬───┬────┬───────────────┐
         │ 7 │ 3 │ 10 │ 1 │ 5 │ 12│ (unused cap…) │
         └───┴───┴────┴───┴───┴────┴───────────────┘  ← capacity
                   ^size=6
```

* Storage: one contiguous heap buffer. When capacity runs out, it allocates bigger block and move all elements
* Iterators: random-access (pointer-like).
* Reallocations can move everything to a new block when growing.

### `std::deque` 🚌

* **Best for**: fast push/pop at **both ends** plus random access.
* **Examples**: sliding windows, BFS queues with front/back ops.
* **Why**: segmented blocks allow O(1) end operations.

Segmented Array Visualiation

```
[ pointer map ]  -->  [block0] [block1] [block2] ...   // array of pointers
                        |         |         |
                        v         v         v
                     elem...   elem...   elem...        // fixed-size chunks
```

* The Pointer Map will store the address of each block.
* Each block will holds a fixed amount of value. (Fixed-size block)
* Once block reached maximum, the pointer map will create another block to store the value.

Segmented array: a “map” (small array) of pointers to fixed-size blocks; blocks are contiguous internally, but not as a whole.

```
map:   ┌──────┬──────┬──────┐
       │ blk0 │ blk1 │ blk2 │
       └───┬──┴───┬──┴───┬──┘
           │      │      │
blk0:  ┌───┬───┬───┬───┐
       │ 7 │ 3 │   │   │ ...
       └───┴───┴───┴───┘

blk1:  ┌────┬───┬───┬───┐
       │ 10 │ 1 │   │   │ ...
       └────┴───┴───┴───┘

blk2:  ┌───┬────┬───┬───┐
       │ 5 │ 12 │   │   │ ...
       └───┴────┴───┴───┘
```

* Storage: multiple small contiguous blocks managed by an index array.
* Iterators: random-access, but elements aren’t in one big contiguous chunk.
* Efficient push at both ends

### `std::list` 🔗

* **Best for**: frequent insert/erase **in the middle** with stable iterators.
* **Examples**: job queues that reorder, splicing between lists.
* **Why**: doubly‑linked nodes → O(1) insert/erase **given iterator**.

Doubly-linked nodes; each element is its own allocation with prev/next links.

```
NULL ← [7] ⇄ [3] ⇄ [10] ⇄ [1] ⇄ [5] ⇄ [12] → NULL
```

* Storage: scattered nodes on the heap; each node holds value + two pointers.
* Iterators: bidirectional (no random access).
* Insert/erase is O(1) given an iterator; finding a spot is O(n).

---

## ⚖️ Deque vs List vs Vector — Pros & Cons

This table is your cheat-sheet for choosing the right container.

| Feature | `std::vector` 🧱 | `std::deque` 🚌 | `std::list` 🔗 |
| :--- | :--- | :--- | :--- |
| **Best For** | **General purpose**. Fast random access & end insertions. The default choice. | Queues, or when insertions/deletions at **both ends** are frequent. | Frequent insertions/deletions in the **middle** of the sequence. |
| **Random Access** | ✅ **`O(1)`** - Fastest | ✅ **`O(1)`** - Fast, but with a slight overhead vs. vector. | ❌ **`O(n)`** - Must traverse the list. |
| **Insertion/Deletion (End)** | **Amortized `O(1)`** at the back. `O(n)` at the front. | ✅ **`O(1)`** at **both** front and back. | ✅ **`O(1)`** at **both** front and back. |
| **Insertion/Deletion (Middle)**| ❌ **`O(n)`** - Elements must be shifted. | ❌ **`O(n)`** - Elements must be shifted. | ✅ **`O(1)`** - *If you already have an iterator to the position.* |
| **Memory Locality** | ⭐⭐⭐ **Excellent** (Contiguous) | ⭐⭐ **Good** (Contiguous in blocks) | ⭐ **Poor** (Scattered nodes) |
| **Iterator Invalidation** | High. Insertion can invalidate **all** iterators. | Medium. End insertions may invalidate. Middle insertions invalidate all. | ✅ **Minimal**. Only iterators to the erased element are invalidated. |
### Explanation of the table

1. Random Access : Can you jump to the nth element instantly?

   * `Vector`/`Deque`: yes ([], it + n).
   * `List`: no (must walk node by node).

2. Insert/Erase End : How fast to push/pop at the back (and front for deque/list)?

   * `Vector`: back is fast, front is slow.
   * `Deque`: both ends fast.
   * `List`: both ends fast.

3. Insert/Erase Middle

   * `Vector`/`Deque`: slow (shift many elements).
   * `List`: fast if you already have the iterator (unlink/link nodes).

4. Memory locality

   * `Vector`: ⭐⭐⭐ contiguous (best for CPU cache).
   * `Deque`: ⭐⭐ segmented blocks.
   * `List`: ⭐ scattered nodes (pointer chasing).

5. Iterator invalidation (what breaks your it?)

   * `Vector`: reallocation or middle edits can invalidate many iterators.
   * `Deque`: end edits often invalidate iterators—don’t keep them across pushes/pops.
   * `List`: only the erased node’s iterator is invalid.

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

---

## 🧠 Locality (Cache Locality)

> **What is it?** Locality describes how *near* your next memory access is to the current one. Modern CPUs fetch memory in **cache lines** (often **64 bytes**). Accessing nearby bytes hits cache (fast); jumping far away misses cache (slow).

---

### 🧩 Types of Locality

* **📍 Spatial locality** — Access addresses that are **close together** (e.g., iterating a contiguous array).
  **Why it helps:** One cache-line fetch can serve **multiple adjacent elements**.

* **⏱️ Temporal locality** — **Revisit the same data** soon (e.g., a small working set used repeatedly).
  **Why it helps:** Recently used data likely **remains in cache**.

---

### 📦 Locality by Container (Summary)

#### 🧱 `vector<T>` — *contiguous block* (**best spatial locality**)

* **Layout:** One contiguous array of `T`:

  ```
  [ T T T T T ... ]
  ```
* **Iteration:** `for (i = 0..n-1)` walks bytes in order → **excellent spatial locality**.
* **Growth:** When capacity is full, allocates a **bigger contiguous block** and **moves** all elements → can **invalidate** pointers/iterators.

---

#### 🚌 `deque<T>` — *segmented contiguous blocks* (**good locality within blocks**)

* **Layout:** Fixed-size **chunks** plus a small pointer **map**:

  ```
  map ---> [ * ][ * ][ * ][ * ] ...
              |    |    |    |
  block0   [ T T T T ... ]   (contiguous within block)
  block1   [ T T T T ... ]
  block2   [ T T T T ... ]
  ```
* **Iteration:** Within each block, elements are contiguous → **good spatial locality**. Crossing a block boundary is a small jump; still **much better** than a linked list.
* **Growth:** Cheap at **both ends** by adding a block and updating the map (no whole-buffer move like `vector`).

---

#### 🔗 `list<T>` — *per-node allocation* (**poor spatial locality**)

* **Layout:** One **heap allocation per element** (a *node* ≈ `{ prev*, T, next* }`). Nodes are placed **individually**, wherever the allocator has space:

  ```
  node0(addr A) --> node1(addr Q) --> node2(addr K) --> ...
  ```
* **Iteration:** Pointer-chasing (`node = node->next`) jumps around memory → **poor spatial locality**, many **cache misses**.
  *Upside:* O(1) insert/erase **given an iterator**; iterators remain valid except the erased one.

---

### ⚡ Locality Quick-Compare

| Container | Spatial Locality                     | Temporal Locality Potential                   | Notes                                                  |
| --------- | ------------------------------------ | --------------------------------------------- | ------------------------------------------------------ |
| `vector`  | ⭐⭐⭐ **Excellent** (fully contiguous) | ⭐⭐ (great for tight loops)                    | Fastest iteration; growth may relocate the whole array |
| `deque`   | ⭐⭐ **Good** (contiguous *by blocks*) | ⭐⭐ (good if working set fits in a few blocks) | Small jumps at block boundaries; cheap ends            |
| `list`    | ⭐ **Poor** (scattered nodes)         | ⭐ (depends on reuse of specific nodes)        | Stable iterators; pointer-chasing hurts cache          |
