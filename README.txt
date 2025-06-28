DEUARC Emulator
This is a C-based emulator for a simple, hypothetical architecture called DEUARC (DEU Electronic Universal Automatic Reduced Computer). It was created as part of a term project in the CME2206 Computer Architecture course, with the goal of exploring how instruction sets, registers, and memory interact inside a basic computer system.

⚠️ This project is primarily for learning purposes. While it runs and emulates DEUARC instructions, there may be bugs or undefined behavior due to manual memory management or edge cases not being fully handled.

Architecture Overview
The DEUARC computer consists of:

Instruction Memory: 32 × 11‑bit instructions

Data Memory: 16 × 4‑bit values

Stack Memory: 16 × 5‑bit values

Registers:

Program Counter (PC)

Stack Pointer (SP)

Address Register (AR)

Instruction Register (IR)

Input & Output Registers

3 General Purpose Registers (R0, R1, R2)

Instruction Set: Arithmetic, logic, control flow, memory I/O — encoded in 11‑bit format

Build Instructions
Using GCC
Run:
gcc emulator.c -o deuarc_emulator

(Optional) With CMake
A simple CMakeLists.txt can be provided to streamline builds across platforms.

Usage
You need to provide:

A file with 11‑bit binary instructions (one per line or fixed‑width)

(Optional) A data memory file, also with 11‑bit binary values

Example:
./deuarc_emulator instructions.txt data.txt

If only an instruction file is given:
./deuarc_emulator instructions.txt

Features Implemented
Instruction fetching and decoding

Register and memory allocation

Execution loop with support for selected opcodes:

HLT, DBL, DBT, ADD, NOT, XOR, INC

ST, LD, IO, TSF, JMP, CAL, RET, JMR

Simple stack operations with program‑counter push/pop

Memory‑mapped data loading from files

Limitations & To‑Do
Some opcodes (ADD, XOR, IO, etc.) are partially or not implemented

Stack overflow/underflow and memory bounds are not fully validated

Many strncpy() and pointer operations are prone to undefined behavior

GetRegister uses string comparisons incorrectly

Register assignments should use strcpy, not direct pointer assignment

Learning Goals
This project served as a learning exercise in:

Understanding low‑level memory layout

Simulating CPU micro‑operations

Using C language features like struct, malloc, and file I/O

Files
emulator.c — Main emulator source file

instructions.txt — Example input instructions (user‑provided)

data.txt — (Optional) data memory initialization

Author Notes
This was written as part of CME2206 Computer Architecture Project during my third year of Computer Engineering studies. It helped me understand how real CPUs decode and execute instructions — even if the implementation isn’t perfect yet!
