# 🚀 **Optimizing Aggregate Queries in Databases using Segment Trees**
![Repo Size](https://img.shields.io/github/repo-size/BhargavShekokar3425/Group2-G4?style=for-the-badge)
![License](https://img.shields.io/github/license/BhargavShekokar3425/Group2-G4?style=for-the-badge)
![Stars](https://img.shields.io/github/stars/BhargavShekokar3425/Group2-G4?style=for-the-badge)
![Forks](https://img.shields.io/github/forks/BhargavShekokar3425/Group2-G4?style=for-the-badge)

📝**Project Overview**
This project demonstrates how Segment Trees can be utilized to optimize aggregate queries in a simulated database system, providing a unique approach to handling SUM, MIN, MAX, and more, alongside support for WHERE clauses in queries. With efficient data retrieval and processing, this project shows how advanced data structures can enhance database operations, offering a simulation of CRUD operations via B-Trees for efficient data storage and Segment Trees for rapid aggregation.

🔍 **Problem Statement**
Aggregate queries like SUM, MIN, MAX, and similar operations are common in databases but can become slow when working with large datasets if optimized algorithms aren’t used. By implementing Segment Trees, which are common in competitive programming for range queries, this project achieves faster aggregate query processing in a database setting. The project tackles the following:

Database Simulation: CRUD operations (basic Create, Read, Update, Delete) are implemented using B-Trees, ensuring efficient storage and retrieval.
Optimized Aggregate Queries: Standard database aggregate queries are optimized with Segment Trees, enabling faster processing.
Advanced Querying: Adding support for SQL-like WHERE clauses, enhancing flexibility in query selection.

🧠 **Key Features**  
Database Simulation: Basic CRUD operations simulated with B-Trees for efficient data handling.
Optimized Querying: Segment Trees are used to speed up aggregate queries such as SUM, MIN, and MAX.
WHERE Clause Support: Adds flexibility by enabling SQL-like filtering with WHERE clauses.
Fast Query Processing: Binary search and Segment Trees combine to deliver swift query execution and optimal data processing.

🛠️**Technical Details**  
Project Structure
This project is organized to provide a structured flow, simulating a database environment where users can execute optimized queries.

CRUD Operations with B-Trees: Implements basic database operations with B-Trees to enable effective insertion, deletion, and update functionality.

Optimized Aggregate Functions:

Segment Tree: Builds and maintains a Segment Tree for performing fast aggregate queries. Each query (e.g., SUM, MIN, MAX) is executed in O(log n) time for each segment, optimizing processing speed.
Binary Search: Utilized for fast record retrieval, which is further enhanced by Segment Trees for range queries.
SQL-like WHERE Clause: Adds filtering capability, allowing users to specify conditions in their aggregate queries, making the query handling more dynamic and versatile.

**Data Structures Used**
B-Trees: Efficient for CRUD operations and used to maintain the simulated database’s records.
Segment Trees: Core of the project, these data structures enable efficient aggregate queries over specific ranges in O(log n) time.

**🚀 How It Works**

Creating Data Records: Users can add records to the database via the CRUD module.

Executing Queries:
Users can execute optimized aggregate queries, like calculating the sum or minimum over specific ranges, by simply inputting the command in the CLI.
Queries that include a WHERE clause are filtered before being aggregated using the Segment Tree, providing an efficient way to handle conditional queries.
Getting Results:
The system provides quick results by leveraging the efficiency of the Segment Tree data structure, making the querying experience seamless even with large datasets.

**📚 Resources**
Segment Trees: CSES Handbook, Chapter 9 - Range Queries
Basic SQL Aggregate Functions: For those unfamiliar with SQL basics, SQL Tutorial on Aggregate Functions provides foundational understanding.


