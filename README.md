# 🚀 Optimizing Aggregate Queries in Databases using Segment Trees

![Repo Size](https://img.shields.io/github/repo-size/BhargavShekokar3425/Group2-G4?style=for-the-badge)
![Stars](https://img.shields.io/github/stars/BhargavShekokar3425/Group2-G4?style=for-the-badge)
![Forks](https://img.shields.io/github/forks/BhargavShekokar3425/Group2-G4?style=for-the-badge)

---

## 📝 Project Overview

This project demonstrates how **Segment Trees** can be utilized to optimize aggregate queries in a simulated database system. Using **B-Trees** for CRUD operations and Segment Trees for rapid aggregation, this system efficiently handles queries for operations like `SUM`, `MIN`, and `MAX`, while supporting SQL-like `WHERE` clauses to add flexibility in query selection.

---

## 🔍 Problem Statement

Aggregate queries such as `SUM`, `COUNT`, `MIN`, and `MAX` are common in databases but can become slow with large datasets if not optimized. This project uses Segment Trees—common in competitive programming for range queries—to speed up aggregate query processing in a database setting. Key components of the project include:

- **Database Simulation**: CRUD operations implemented using B-Trees for efficient storage and retrieval.
- **Optimized Aggregate Queries**: Standard database queries are optimized with Segment Trees for faster processing.
- **Advanced Querying**: Support for SQL-like `WHERE` clauses to provide flexible selection.

---

## 🧠 Key Features

- **Database Simulation**: Basic CRUD operations simulated with B-Trees for efficient data handling.
- **Optimized Querying**: Segment Trees enable rapid execution of aggregate queries like `SUM`, `MIN`, and `MAX`.
- **WHERE Clause Support**: SQL-like filtering with `WHERE` clauses for flexible query handling.
- **Fast Query Processing**: Combination of Binary Search and Segment Trees ensures fast, efficient data processing.

---

## 🛠️ Technical Details

### Project Structure

This project is organized to simulate a database environment with optimized query execution.

- **CRUD Operations with B-Trees**: Implements basic database operations with B-Trees for effective insertion, deletion, and update functionality.

- **Optimized Aggregate Functions**:
  - **Segment Tree**: Builds and maintains a Segment Tree for performing fast aggregate queries, with operations executed in O(log n) time for each segment.
  - **Binary Search**: Used for quick record retrieval, further enhanced by Segment Trees for range queries.
  - **SQL-like WHERE Clause**: Adds filtering capability, enabling users to specify conditions, making query handling dynamic and versatile.

### Data Structures Used

- **B-Trees**: Efficient for CRUD operations, maintaining the simulated database’s records.
- **Segment Trees**: The core data structure for efficient aggregate queries over specific ranges.

---

## 🚀 How It Works

1. **Creating Data Records**: Users add records to the database using the CRUD module.
2. **Executing Queries**:
   - Users input optimized aggregate queries, like calculating the `SUM` or `MIN` over specified ranges.
   - Queries with a `WHERE` clause are filtered before aggregation, providing an efficient way to handle conditional queries.
3. **Getting Results**: The system provides quick results by leveraging Segment Trees, making the querying experience seamless even with large datasets.

Run Command:  g++ -o main tree0.cpp BTree.cpp segtree.cpp csvAaryan.cpp -I.
---

## 📚 Resources

- **Segment Trees**: [CSES Handbook, Chapter 9 - Range Queries](https://cses.fi/book/book.pdf)
- **Basic SQL Aggregate Functions**: [SQL Tutorial on Aggregate Functions](https://www.sqltutorial.org/sql-aggregate-functions/)

---

## 🔗 Repository

Check out the repository for code and additional documentation: [Group2-G4 on GitHub](https://github.com/BhargavShekokar3425/Group2-G4)
