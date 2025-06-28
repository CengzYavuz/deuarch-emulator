/*
 * DEUARC Emulator - Refactored for Safety and Correctness
 * CME2206 Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define INST_MEM_SIZE 32
#define DATA_MEM_SIZE 16
#define STACK_MEM_SIZE 16
#define WORD_BITS      11
#define WORD_STR_SIZE (WORD_BITS + 1)

// Memory word represented as null-terminated string of '0'/'1'
typedef char WordStr[WORD_STR_SIZE];

// Emulator memory
typedef struct {
    WordStr inst_mem[INST_MEM_SIZE];
    WordStr data_mem[DATA_MEM_SIZE];
    WordStr stack_mem[STACK_MEM_SIZE];
} Memory;

// CPU registers and state
typedef struct {
    Memory mem;
    uint8_t PC;    // Program Counter (0-31)
    uint8_t SP;    // Stack Pointer (0-15)
    uint8_t AR;    // Address Register (0-31)
    WordStr IR;    // Instruction Register
    WordStr INPR;  // Input Register
    WordStr OUTR;  // Output Register
    WordStr R[3];  // General-purpose registers R0, R1, R2
    bool halted;
} CPU;

// Function prototypes
bool load_memory(const char *filename, WordStr buffer[], size_t max_words);
void init_cpu(CPU *cpu);
void fetch(CPU *cpu);
void decode(CPU *cpu, char opcode[], char Rd[], char S1[], char S2[], bool *Q);
void execute(CPU *cpu, const char opcode[], const char Rd[], const char S1[], const char S2[], bool Q);
char* get_reg_ptr(CPU *cpu, const char *code);

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <instructions.txt> [data.txt]\n", argv[0]);
        return EXIT_FAILURE;
    }

    CPU cpu;
    init_cpu(&cpu);

    // Load instruction memory
    if (!load_memory(argv[1], cpu.mem.inst_mem, INST_MEM_SIZE)) {
        fprintf(stderr, "Failed to load instruction file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Load data memory if provided
    if (argc == 3) {
        if (!load_memory(argv[2], cpu.mem.data_mem, DATA_MEM_SIZE)) {
            fprintf(stderr, "Failed to load data file: %s\n", argv[2]);
            return EXIT_FAILURE;
        }
    }

    // Execution loop
    while (!cpu.halted) {
        fetch(&cpu);
        char opcode[5] = {0}, Rd[3] = {0}, S1[3] = {0}, S2[3] = {0};
        bool Q = false;
        decode(&cpu, opcode, Rd, S1, S2, &Q);
        execute(&cpu, opcode, Rd, S1, S2, Q);
    }

    return EXIT_SUCCESS;
}

bool load_memory(const char *filename, WordStr buffer[], size_t max_words) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return false;
    char line[WORD_STR_SIZE + 2];  // + newline + null
    size_t count = 0;
    while (count < max_words && fgets(line, sizeof(line), fp)) {
        if (strlen(line) < WORD_BITS) continue;
        // Copy only first WORD_BITS characters
        memcpy(buffer[count], line, WORD_BITS);
        buffer[count][WORD_BITS] = '\0';
        count++;
    }
    fclose(fp);
    return true;
}

void init_cpu(CPU *cpu) {
    memset(cpu, 0, sizeof(CPU));
    cpu->PC = 0;
    cpu->SP = 0;
    cpu->AR = 0;
    cpu->halted = false;
}

void fetch(CPU *cpu) {
    memcpy(cpu->IR, cpu->mem.inst_mem[cpu->PC], WORD_STR_SIZE);
    cpu->PC = (cpu->PC + 1) % INST_MEM_SIZE;
}

void decode(CPU *cpu, char opcode[], char Rd[], char S1[], char S2[], bool *Q) {
    // IR format: Q(1) | OPC(4) | Rd(2) | S1(2) | S2(2)
    *Q = (cpu->IR[0] == '1');
    memcpy(opcode, &cpu->IR[1], 4);
    opcode[4] = '\0';
    memcpy(Rd, &cpu->IR[5], 2); Rd[2] = '\0';
    memcpy(S1, &cpu->IR[7], 2); S1[2] = '\0';
    memcpy(S2, &cpu->IR[9], 2); S2[2] = '\0';
}

void execute(CPU *cpu, const char opcode[], const char Rd[], const char S1[], const char S2[], bool Q) {
    // Halt
    if (strcmp(opcode, "0111") == 0) {
        cpu->halted = true;
        return;
    }
    // Example: DBL (0000)
    if (strcmp(opcode, "0000") == 0) {
        char *src = get_reg_ptr(cpu, S1);
        char *dst = get_reg_ptr(cpu, Rd);
        // TODO: implement binary doubling (left shift)
        strcpy(dst, src);
        return;
    }
    // TODO: implement other opcodes
    // For unimplemented ops, just skip
}

char* get_reg_ptr(CPU *cpu, const char *code) {
    if (strcmp(code, "00") == 0) return cpu->R[0];
    if (strcmp(code, "01") == 0) return cpu->R[1];
    if (strcmp(code, "10") == 0) return cpu->R[2];
    // Default fallback
    return NULL;
}
