# 🧠 Bitmask DP – Quick Reference & Core Patterns

Bitmasking is a powerful technique widely used in **DP, combinatorics, and optimization problems**, especially when the number of elements is small (typically `n ≤ 20`). This guide gives you a **clean, beginner‑friendly, and interview‑ready** overview.

---

## 🔢 What is a Bitmask?

* A **bitmask** is an `int` where each bit represents whether an element is **present (1)** or **absent (0)**.
* Example: For `n = 5`

  * `mask = 10101₂` → elements `{0, 2, 4}` are selected

---

## ⚙️ Common Bitmask Operations

Assume `mask` is an integer and `j` is the bit index (0-based).

### ✅ Check if j-th bit is set

```cpp
if (mask & (1 << j)) {
    // j is in the set
}
```

### ➕ Set j-th bit

```cpp
mask |= (1 << j);
```

### ➖ Unset j-th bit

```cpp
mask &= ~(1 << j);
```

### 🔁 Toggle j-th bit

```cpp
mask ^= (1 << j);
```

### 📏 Size of the set (number of selected elements)

```cpp
int count = __builtin_popcount(mask); // for int
```

---

## 🧩 Two Core Patterns of Bitmask DP

Most **beginner to intermediate Bitmask DP problems** fall into one of these two patterns.

---

### 🟦 1. DP Over Subsets

> Each state represents **a subset only**.

#### 🔹 Definition

```cpp
dp[mask] = best answer for this subset
```

#### 🔹 When to Use

* Order of elements **does not matter**
* You only care **which elements are chosen**

#### 🔹 Typical Transitions

```cpp
for (int mask = 0; mask < (1 << n); mask++) {
    for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) {
            dp[mask] = max(dp[mask], dp[mask ^ (1 << j)] + value[j]);
        }
    }
}
```

#### 🔹 Classic Problems

* Subset DP
* Knapsack-like problems
* Minimum cost to cover a set

---

### 🟩 2. DP Over Subsets + Last Element

> Each state represents **a subset and its last chosen element**.

#### 🔹 Definition

```cpp
dp[mask][last] = best answer for this subset ending at `last`
```

#### 🔹 When to Use

* **Order matters**
* Path / sequence / permutation-based problems

#### 🔹 Typical Transitions

```cpp
for (int mask = 0; mask < (1 << n); mask++) {
    for (int last = 0; last < n; last++) {
        if (!(mask & (1 << last))) continue;
        for (int prev = 0; prev < n; prev++) {
            if (prev != last && (mask & (1 << prev))) {
                dp[mask][last] = max(dp[mask][last],
                    dp[mask ^ (1 << last)][prev] + cost[prev][last]);
            }
        }
    }
}
```

#### 🔹 Classic Problems

* Traveling Salesman Problem (TSP)
* Hamiltonian paths
* Optimal ordering / permutations

---

## 🚀 Pro Tips

* Total states ≈ `2^n` → feasible for `n ≤ 20`
* Use `vector<int> dp(1<<n)` or `dp[1<<n][n]`
* Always think:

  * **Is order important?** → use `dp[mask][last]`
  * **Only subset matters?** → use `dp[mask]`

---

## 📌 Final Note

Bitmask DP is a **must-know skill** for competitive programming, system design interviews, and advanced algorithmic problems.

⭐ If you find this helpful, consider **starring the repo** and contributing more patterns!

Happy Coding 🚀
