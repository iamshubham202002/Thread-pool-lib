# Thread-pool-lib

A modern C++ thread pool library built from scratch on Ubuntu using CMake.  
This project demonstrates core **systems programming** and **concurrency** concepts.

---

## Project Objective

The goal of this project is to design and implement a reusable thread pool that:

- Manages a **fixed number of worker threads**
- Accepts tasks **dynamically at runtime**
- Executes tasks **concurrently**
- Uses **proper synchronization** (mutexes, condition variables)
- Supports **graceful shutdown**
- **Avoids busy waiting**

---

## Key Concepts Demonstrated

- Multithreading using `std::thread`
- Task scheduling with a shared queue
- Synchronization using:
  - `std::mutex`
  - `std::condition_variable`
- RAII-based thread lifecycle management
- Clean separation of interface and implementation
- Modern CMake build system
- Linux/Ubuntu development workflow

---
### Build Instructions (Ubuntu)

### Prerequisites
- Ubuntu Linux
- C++17 compatible compiler (GCC / Clang)
- CMake ≥ 3.16

### Build & Run

```bash
git clone https://github.com/iamshubham202002/Thread-pool-lib.git
cd Thread-pool-lib

mkdir build
cd build

cmake ..
make -j$(nproc)
./example

----
## Screenshots Output
![Output](screenshots/output.png)


## Author

**Shubham Pandey**  
C++ Systems Programming
