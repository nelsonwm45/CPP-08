# 📦 STL Container Adaptors — Visual README (CPP‑08)

A compact, visual guide to `std::stack`, `std::queue`, and `std::priority_queue`—what they are, how they differ from sequence containers, what operations they forward to underneath, and how to choose the right backing container.

---

## 🧭 What is a *container adaptor*?

A **container adaptor** is a thin wrapper that **enforces a policy** (LIFO, FIFO, or priority) on top of another container (the *underlying container*). It **restricts access** to match that policy.

> Adaptors don’t define storage layout; they **forward** operations to an existing container.

* `std::stack<T, Container>` → LIFO
* `std::queue<T, Container>` → FIFO
* `std::priority_queue<T, Container, Compare>` → Heap with priority (max‑heap by default)

---

## 🔀 Adaptors vs Sequence Containers

**Sequence containers** (`vector`, `deque`, `list`):

* Own the elements
* Provide **general traversal** and **iterators**
* Expose many insert/erase positions and random/linear access (depending on the container)

**Adaptors** (`stack`, `queue`, `priority_queue`):

* Own nothing special: they **wrap** an underlying container
* Provide **restricted interface** aligned with a policy
* **No iterators** in the public API (by design)

---

## 🔑 Key Views

### 1) **Access Surface** (where you can legally touch the data)

```
std::stack      [      ...      |  TOP  ]   // back only (LIFO)
std::queue      [ FRONT |      ...      | BACK ]   // dequeue at front, enqueue at back (FIFO)
priority_queue  [   TOP (highest priority)   ]  // only top is observable; internal heap order hidden
```

### 2) **Underlying Calls** (conceptual forwarding)

```
stack           push -> c.push_back(x)    top -> c.back()      pop -> c.pop_back()
queue           push -> c.push_back(x)    front -> c.front()   pop -> c.pop_front()   back -> c.back()
priority_queue  push -> push_heap(c, x)   top -> c.front()     pop -> pop_heap(c) + c.pop_back()
```

*(For `priority_queue`, `c.front()` is the heap’s root after `make_heap`/`push_heap` maintenance.)*

### 3) **Memory Pictures** (conceptual; depends on chosen container)

* **vector**: contiguous

```
[c0][c1][c2][c3][c4]  // single contiguous block in memory
```

* **deque**: segmented blocks behind a small map

```
map -> [ B0 ] [ B1 ] [ B2 ]
        |       |       |
       [..block..][..block..][..block..]  // O(1) push_front & push_back
```

* **list**: nodes linked (excellent iterator stability, poor locality)

```
[ node ] <-> [ node ] <-> [ node ]  // each node separately allocated
```

> Adaptors piggyback on one of these. The **layout** comes from the underlying container you pick.

---

## 📋 Adaptor Cheat Sheet

| Adaptor                                             | Policy              | Default Underlying | Acceptable Underlying      | Required Ops on Underlying                | Iterators? | Typical Complexity                |
| --------------------------------------------------- | ------------------- | ------------------ | -------------------------- | ----------------------------------------- | ---------- | --------------------------------- |
| `std::stack<T, C=deque<T>>`                         | LIFO                | `deque<T>`         | `vector<T>`, `list<T>`     | `back`, `push_back`, `pop_back`           | ❌          | `push/pop/top`: O(1) amortized    |
| `std::queue<T, C=deque<T>>`                         | FIFO                | `deque<T>`         | `list<T>`                  | `front`, `back`, `push_back`, `pop_front` | ❌          | `push/pop/front/back`: O(1)`      |
| `std::priority_queue<T, C=vector<T>, Comp=less<T>>` | Priority (max‑heap) | `vector<T>`        | `deque<T>` (random‑access) | random‑access (`operator[]`, `size`)      | ❌          | `push/pop`: O(log n), `top`: O(1) |

**Why no `vector` for `queue`?** Because `vector` lacks O(1) `pop_front()`.

---

## 🧱 `std::stack` — LIFO

**Interface:** `push`, `pop`, `top`, `empty`, `size`

**Default underlying:** `deque<T>`

**Forwarding (conceptual):**

```
push(x) -> c.push_back(x)
pop()   -> c.pop_back()
top()   -> c.back()
```

**Visuals:**

```
Push order      ┌───── TOP (last pushed)
                │ [ 30 ]
                │ [ 20 ]
Bottom          │ [ 10 ]
```

**Notes:** `vector<T>` also works well (great locality). `list<T>` is valid but usually slower due to allocation churn and cache misses.

---

## 🛤️ `std::queue` — FIFO

**Interface:** `push`, `pop`, `front`, `back`, `empty`, `size`

**Default underlying:** `deque<T>`

**Forwarding (conceptual):**

```
push(x)  -> c.push_back(x)      // enqueue
pop()    -> c.pop_front()       // dequeue
front()  -> c.front()
back()   -> c.back()
```

**Visuals:**

```
Enqueue → [ 1 ][ 2 ][ 3 ][ 4 ] ← Enqueue
           ^ pop/front here
```

**Notes:** `list<T>` is acceptable (O(1) front ops) but loses locality; `vector<T>` is not appropriate since `pop_front()` is O(n).

---

## ⛰️ `std::priority_queue` — Heap (Max by Default)

**Interface:** `push`, `pop`, `top`, `empty`, `size`

**Default underlying:** `vector<T>` with heap algorithms (`make_heap`, `push_heap`, `pop_heap`).

**Comparator:** `Compare` is `std::less<T>` by default → **max‑heap**. Use `std::greater<T>` for a min‑heap.

**Visuals:**

Heap as a tree (conceptual):

```
            (Top)
             [42]
            /    \
         [29]    [18]
         /  \     / \
       [14][7]  [9] [3]
```

Array layout in the underlying vector (1‑based index shown):

```
idx:    1   2   3   4   5   6   7
vec:   [42][29][18][14][ 7][ 9][ 3]
parent i -> i/2, children -> 2i, 2i+1
```

**Forwarding (conceptual):**

```
push(x):  c.push_back(x);  std::push_heap(c.begin(), c.end(), Comp)
pop():    std::pop_heap(c.begin(), c.end(), Comp); c.pop_back()
top():    return c.front();   // heap root
```

**Notes:** Requires **random access**. `vector<T>` is ideal.

---

## 🧩 “MutantStack” Note (Educational Trick)

`std::stack` doesn’t expose iterators, but in most lib implementations it stores the underlying container in a **protected** member (often named `c`). For learning/tests, you can derive and expose `begin()/end()` via `this->c.begin()`/`this->c.end()`. This is implementation‑detail‑dependent and **non‑standard**—great for 42 exercises, not for production.

---

## 🪄 Mini Re‑Implementations (Pseudo‑C++98)

### `stack`

```cpp
template <class T, class C = std::deque<T> >
class stack {
    C c;
public:
    void push(const T& x) { c.push_back(x); }
    void pop()            { c.pop_back(); }
    T& top()              { return c.back(); }
    const T& top() const  { return c.back(); }
    bool empty() const    { return c.empty(); }
    size_t size() const   { return c.size(); }
};
```

### `queue`

```cpp
template <class T, class C = std::deque<T> >
class queue {
    C c;
public:
    void push(const T& x) { c.push_back(x); }
    void pop()            { c.pop_front(); }
    T& front()            { return c.front(); }
    const T& front() const{ return c.front(); }
    T& back()             { return c.back(); }
    const T& back() const { return c.back(); }
    bool empty() const    { return c.empty(); }
    size_t size() const   { return c.size(); }
};
```

### `priority_queue` (sketch)

```cpp
template <class T, class C = std::vector<T>, class Comp = std::less<T> >
class priority_queue {
    C c; Comp comp;
public:
    void push(const T& x) { c.push_back(x); std::push_heap(c.begin(), c.end(), comp); }
    void pop()            { std::pop_heap(c.begin(), c.end(), comp); c.pop_back(); }
    const T& top() const  { return c.front(); }
    bool empty() const    { return c.empty(); }
    size_t size() const   { return c.size(); }
};
```

---

## 🧠 Choosing the Underlying Container

* **`stack`** → `vector<T>` or `deque<T>` (both fast); avoid `list<T>` unless you need iterator stability and don’t care about locality.
* **`queue`** → `deque<T>` by default (O(1) `pop_front`), `list<T>` if you need guaranteed iterator stability.
* **`priority_queue`** → `vector<T>` almost always the best choice.

---

## ⚠️ Common Pitfalls

* Expecting **iterators** from adaptors → not provided.
* Using `vector` under `queue` → `pop_front()` becomes O(n).
* Confusing `priority_queue` order with sorted container: **only the top** is guaranteed; the rest is heap‑ordered, **not sorted**.
* Forgetting to flip comparator for a min‑heap: use `std::greater<T>`.

---

## 🧾 Quick API Reminders

```
std::stack<T> s; s.push(x); s.top(); s.pop(); s.size(); s.empty();
std::queue<T> q; q.push(x); q.front(); q.back(); q.pop(); q.size(); q.empty();
std::priority_queue<T> pq; pq.push(x); pq.top(); pq.pop(); pq.size(); pq.empty();
```

---

## 🧭 Bonus: Conceptual Axis (like your set/map diagram)

Here’s a **policy‑axis** view showing what part of the sequence is *visible* to each adaptor.

```
Sequence (conceptual order): [ a0, a1, a2, a3, a4, ... ]

stack           visible → [ ... | aN ]                   // top at end only
queue           visible → [ a0 | ... | aN ]              // front (dequeue) and back (enqueue)
priority_queue  visible → [ a* ]                         // only the highest‑priority element
```

---

## ✅ TL;DR

* Adaptors = **policy + restricted API** over an existing container.
* **No iterators**; you interact via `top/front/back` and `push/pop` (or heap `top`).
* Choose underlying containers that match the required operations (e.g., `deque` for `queue`, `vector` for `priority_queue`).
