# 🗂️ C++ Containers — Index (C++98)

## 📚 Contents

* 📘 **Sequence Containers** — `std::vector`, `std::deque`, `std::list`

  * What they are, common members, use‑cases
  * Deque vs List vs Vector (pros/cons, complexity, iterator categories)
  * Why/when to use `<algorithm>` with iterators

  👉 Read: **[Sequence Containers](docs/sequence-containers.md)**

* 📘 **Associative Containers** — `std::set`, `std::multiset`, `std::map`, `std::multimap`

  * What they are, common members, use‑cases
  * Map vs Multiset vs Multimap vs Set (pros/cons, complexity)
  * Iterator categories & traversal in sorted order

  👉 Read: **[Associative Containers](docs/associative-containers.md)**

---

## ⚔️ Quick Cheat‑Sheet

* **Sequence** (position‑based): choose when you control order by **position** and need fast **random access** (`vector`/`deque`) or **stable middle insert/erase** (`list`).
* **Associative** (key‑ordered): choose when you need data **sorted by key** and **O(log n)** key lookup (`set/map`).

---

## 📎 Notes / C++98

* Keep template definitions in headers (or included `.tpp`).
* `std::sort` requires random access (works with `vector`/`deque`, not `list`).
* `map::operator[]` may **insert**; use `find` to probe without insertion.
* Iterator categories: `vector/deque` → RandomAccess, `list`/associative → Bidirectional.
