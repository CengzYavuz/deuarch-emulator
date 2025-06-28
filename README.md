# 🚀 DEUARC Emulator

**DEUARC Emulator** is a C-based emulator for a custom, minimal CPU architecture called DEUARC (DEU Electronic Universal Automatic Reduced Computer). It was developed as part of the CME 2206 Computer Architecture course at Dokuz Eylül University to learn low-level programming, instruction decoding, and memory management in C.

---

## 🛠 Project Summary

* **Project Title**: DEUARC Emulator
* **Institution**: Dokuz Eylül University, Faculty of Engineering, Computer Engineering
* **Course**: CME 2206 – Computer Architecture
* **Date**: June 2025

---

## 🚀 Features

* **Instruction Fetch & Decode**

  * Reads fixed-width 11-bit instructions from a text file
  * Parses opcode, registers, and immediate fields

* **Instruction Set Support**

  * **Control**: HLT, JMP, JMR, CAL, RET
  * **Arithmetic & Logic**: DBL, DBT, ADD, NOT, XOR, INC
  * **Memory & I/O**: LD, ST, IO, TSF

* **Memory Model**

  * **Instruction Memory**: 32 words of 11 bits
  * **Data Memory**: 16 words of 11 bits
  * **Stack Memory**: 16 words of 11 bits

* **Register File**

  * Program Counter (PC)
  * Stack Pointer (SP)
  * Address Register (AR)
  * Instruction Register (IR)
  * Input & Output Registers (INPR, OUTR)
  * 3 General-Purpose Registers (R0, R1, R2)

* **Execution Loop**

  * Fetch → Decode → Execute until `HLT`
  * Simple PC push/pop on `CAL`/`RET`

---

## 📦 System Architecture

```text
emulator.c       # Main driver: CPU state init, memory loading, execution loop
Memory          # Instantiates instruction, data, and stack memories as arrays
CPU             # Holds registers (PC, SP, AR, IR, INPR, OUTR, R[]), and state
fetch()         # Copies next instruction into IR, increments PC safely
decode()        # Extracts Q, opcode, Rd, S1, S2 from IR
execute()       # Matches opcode and performs the operation on registers/memory
load_memory()   # Reads binary words from file into memory arrays
init_cpu()      # Zeroes CPU struct and initializes registers
get_reg_ptr()   # Returns pointer to register array element by code
```

---

## 🛠️ Build & Run

### Using GCC

```bash
gcc emulator.c -o deuarc_emulator
```

### Run the Emulator

1. **With both instruction & data files**

   ```bash
   ./deuarc_emulator instructions.txt data.txt
   ```
2. **With only instruction file**

   ```bash
   ./deuarc_emulator instructions.txt
   ```

> Each file should contain fixed-width 11-character binary strings (0/1). Instruction memory max 32 words; data memory max 16 words.

---

## ⚙️ Algorithm Complexity

* **Time**: O(T × N) per run, where T is number of cycles until `HLT` and N is number of opcodes.
* **Space**: O(1) additional beyond fixed memory sizes.

---

## 🔮 Future Improvements

* **Complete Opcode Logic**: Implement all arithmetic and memory operations fully (ADD, XOR, IO, ST/LD variations).
* **Error Handling**: Bounds checks for PC/SP overflow, file format validation, and invalid opcode detection.
* **CMake Support**: Add `CMakeLists.txt` for cross-platform builds.
* **Unit Tests**: Create automated tests for each opcode and memory operation.

---

## 📂 File Overview

```text
emulator.c          # Refactored source code (fetch, decode, execute, etc.)
instructions.txt    # Example instruction memory input
data.txt            # Example data memory input (optional)
```

---

## 📧 Contact

Email: [2022510158@ogr.deu.edu.tr](mailto:2022510158@ogr.deu.edu.tr
