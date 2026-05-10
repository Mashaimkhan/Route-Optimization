# 🚀 Route Optimization System (DSA Project)

## 📌 Project Description

This project implements a **Route Optimization System** using different graph algorithms in C++.
It focuses on solving pathfinding problems using both **static and dynamic graph representations**.

---

## 🧠 Algorithms Implemented

* 🔹 Greedy Algorithm (Nearest Neighbor approach)
* 🔹 Brute Force (Optimal solution using permutations)
* 🔹 Dijkstra Algorithm (Shortest path between two cities)

---

## 🏗️ Graph Representations

### 1. Static Representation

* Uses **Adjacency Matrix**
* Faster access
* Higher memory usage

### 2. Dynamic Representation

* Uses **Adjacency List**
* Memory efficient for sparse graphs

---

## ⚙️ Features

* Add cities and routes
* Read graph data from file
* Find optimized routes
* Compare:

  * Time Complexity
  * Memory Usage
* Display complete path with total distance

---

## 📊 Complexity Analysis

| Algorithm   | Time Complexity |
| ----------- | --------------- |
| Greedy      | O(N²)           |
| Brute Force | O(N!)           |
| Dijkstra    | O(V²)           |

---

## 📂 File Structure

```
project-folder/
│── main.cpp
│── graph.h
│── graph.cpp
│── input.txt   (for routes data)
```

---

## 📥 Input Format

File should contain:

```
city1 city2 distance
```

Example:

```
0 1 10
0 2 15
0 3 20
1 2 30
1 3 20
2 3 25
```

---

## ▶️ How to Run

1. Compile:

```
g++ main.cpp -o program
```

2. Run:

```
./program
```

---

## 💾 Memory Comparison

* Static Graph: Uses matrix (O(N²))
* Dynamic Graph: Uses linked list (efficient for sparse graphs)

---

## 👩‍💻 Author

**Dur-e-Shahwar Mazher**

---

## 📌 Notes

* Brute Force gives **optimal solution** but is slow
* Greedy is **fast but not always optimal**
* Dijkstra finds **shortest path between two cities**

---

## ⭐ Future Improvements

* Add GUI visualization
* Use priority queue for optimized Dijkstra
* Handle larger datasets efficiently
# Route-Optimization
