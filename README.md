# 🚀 DEUARC Emulator

**DEUARC** (DEU Electronic Universal Automatic Reduced Computer) is a C-based emulator for a custom, minimal CPU architecture. It was developed as part of the CME 2206 Computer Architecture course at Dokuz Eylül University to learn low‑level programming, instruction decoding, and memory management in C.

---

## 🛠 Project Summary

- **Project Title**: DEUARC Emulator  
- **Institution**: Dokuz Eylül University, Faculty of Engineering, Computer Engineering  
- **Course**: CME 2206 – Computer Architecture  
- **Date**: June 2025  

---

## 🚀 Features

- **Instruction Fetch & Decode**  
  - Reads fixed-width 11‑bit instructions from a text file  
  - Parses opcode, registers, immediate fields  

- **Instruction Set Support**  
  - **Control**: HLT, JMP, JMR, CAL, RET  
  - **Arithmetic & Logic**: DBL, DBT, ADD, NOT, XOR, INC  
  - **Memory & I/O**: LD, ST, IO, TSF  

- **Memory Model**  
  - **Instruction Memory**: 32 words of 11 bits  
  - **Data Memory**: 16 words of 11 bits  
  - **Stack Memory**: 16 words of 11 bits  

- **Register File**  
  - Program Counter (PC)  
  - Stack Pointer (SP)  
  - Address Register (AR)  
  - Instruction Register (IR)  
  - Input & Output Registers  
  - 3 General‑Purpose Registers (R0, R1, R2)  

- **Execution Loop**  
  - Fetch → Decode → Execute until `HLT`  
  - Simple PC push/pop on `CAL`/`RET`  

---

## 📦 System Architecture

1. **emulator.c**  
   - Main driver: initializes CPU state, loads memory from files, runs the execution loop.

2. **Memory Structures**  
   - `MEM` struct holds three memories as arrays of `WORD` (dynamically allocated strings).  
   - `CMPT` struct holds CPU registers and a `MEM` instance.

3. **Core Functions**  
   - `InitializeMemory` / `InitializeComputer`  
   - `Fetch` / `Decode` / `Execute`  
   - `FreeMemory`  

---

## 🛠️ Build & Run

### Using GCC

```bash
gcc emulator.c -o deuarc_emulator
