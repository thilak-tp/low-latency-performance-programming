# Low-Latency & Performance-Oriented Programming

This repository explores **low-latency and performance-oriented programming** concepts in C++, with a strong focus on **extracting maximum performance from modern hardware** through careful software design.

The primary goal is to **understand how CPUs actually behave** — including branch prediction, pipeline stalls, cache effects, and instruction-level execution — and to validate these behaviors using **practical benchmarks**, not assumptions.
- examples/cpu_branch_prediction.cpp


---

### 🧪 Experiment Description

- A large dataset is processed
- Two sums are computed:
  - One using conditional branching (`if`)
  - One using branch-free arithmetic logic
- Execution time is measured using high-resolution timers
- Both approaches are validated for correctness

---


# Phase 1 — Hardware & OS Fundamentals  
## 1A. CPU Architecture (Performance-Oriented View)

Modern CPUs achieve high performance by aggressively overlapping and parallelizing instruction execution. Understanding these mechanisms is essential for low-latency and high-throughput systems.

---

## 1. Instruction Lifecycle (CPU Execution Model)

Every machine instruction follows a well-defined lifecycle:


### 1.1 Instruction Fetch (IF)
- The CPU fetches the next instruction from the **L1 Instruction Cache**, falling back to **L2/L3 → RAM** on cache misses.
- The **Program Counter (PC)** holds the address of the next instruction.
- The instruction is loaded into the **Instruction Register (IR)**.

### 1.2 Decode (ID)
- The **Control Unit** decodes the instruction in the IR.
- Determines:
  - Instruction type (ALU, Load/Store, Branch, FP, SIMD)
  - Required operands and execution units
- Instruction dependencies are identified.

### 1.3 Execute (EX)
- The instruction is executed using the appropriate unit:
  - ALU (integer operations)
  - FPU (floating-point operations)
  - Load/Store units (memory access)
  - Branch units
- Memory operations may trigger cache accesses.

### 1.4 Retire (Write-Back / Commit)
- Results are written back to:
  - Register file
  - Memory (if applicable)
- Instructions are retired **in program order** to preserve correctness.

---

## 2. Superscalar Execution

Superscalar CPUs can execute **multiple instructions per clock cycle**.

### Key Concepts

- **Multiple Execution Units**
  - Integer, Floating-Point, SIMD, Branch, and Load/Store units operate in parallel.

- **Parallel Fetch & Decode**
  - Multiple instructions are fetched and decoded every cycle.

- **Dynamic Scheduling**
  - Hardware scheduler selects independent instructions for execution.

- **Out-of-Order Execution (OoO)**
  - Instructions execute as soon as operands are ready, not strictly in program order.

- **Register Renaming**
  - Eliminates false dependencies (WAR / WAW hazards).

- **Speculative Execution**
  - Executes predicted instruction paths before branch resolution.

### Benefits

- Higher **Instructions Per Cycle (IPC)**
- Improved execution unit utilization
- Increased overall throughput

---

## 3. Pipeline Stalls & Hazards

A pipeline stall occurs when an instruction cannot safely proceed.

### Causes

- **Data Hazards**
  - Instruction depends on results from previous instructions.
- **Control Hazards**
  - Introduced by branches and jumps.
- **Structural Hazards**
  - Resource conflicts between instructions.

### Handling Stalls

- The CPU inserts **pipeline bubbles (NOPs)**.
- Execution pauses until the hazard is resolved.

### Impact

- Wasted clock cycles
- Reduced throughput
- Lower IPC

---

## 4. Branch Prediction & Misprediction Penalty

### Branch Prediction
- The CPU predicts the outcome of conditional branches to keep the pipeline full.
- Uses historical execution patterns and heuristics.

### Branch Misprediction Penalty
- Incorrect predictions cause:
  - Pipeline flush
  - Discarded speculative instructions
  - Re-fetch and execution of the correct path

### Performance Impact

- Mispredictions can cost **tens to hundreds of cycles**.
- Deep pipelines significantly increase penalty cost.

> CPUs are fast only when execution is predictable.

---

## 5. Cache Hierarchy & Memory Access

Cache is small, ultra-fast memory located close to the CPU.

### Memory Access Order


### Purpose

- Reduce average memory access latency
- Exploit locality of reference:
  - Temporal locality
  - Spatial locality

---

## 6. Cache Levels

### L1 Cache
- Per-core
- Fastest cache level
- Size: ~2 KB – 64 KB
- Separate Instruction and Data caches

### L2 Cache
- Per-core or shared
- Size: ~256 KB – 512 KB
- Slower than L1, faster than L3

### L3 Cache
- Shared across all CPU cores
- Size: ~1 MB – 8+ MB
- Acts as a buffer before main memory

---

## 7. Cache Hits & Misses

- **Cache Hit**
  - Data found in cache
  - Low latency
  - High performance

- **Cache Miss**
  - Data fetched from a lower memory level
  - Higher latency
  - Performance degradation

### Cache Performance Metric


Higher hit ratios directly translate to lower latency and better throughput.

---

## Why This Matters for Low-Latency Systems

- Enables cache-friendly data structures
- Encourages branch-free, predictable code
- Improves multithreading and scheduling decisions
- Forms the foundation for real-world performance optimization

