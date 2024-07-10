#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Word
{
    char value[2];
}Word;

typedef struct Memory{

    Word* data[32];
    
}Memory;
 
typedef struct CPU { 

    Memory* instructionMemory;
    Memory* dataMemory;

    char* addressRegister;
    char* programCounter;
    char* stackPointer;
    char* inputRegister;
    char* outputRegister;
    char* instructionRegister;


}CPU;
void initializeCPU(CPU *cpu) {
    // Initialize instruction memory
    cpu->instructionMemory = calloc(32,sizeof(Word));
    cpu->dataMemory = calloc(32,sizeof(Word));
    // Initialize registers
    cpu->addressRegister = 0x00;
    cpu->programCounter = 0x00;
    cpu->stackPointer = 0x00;
    cpu->inputRegister = 0x00;
    cpu->outputRegister = 0x00;
    cpu->instructionRegister = 0x00;
}

void WriteToMemory(Memory* memory, int address, Word dataToWrt){

    memory->data[address] = &dataToWrt; 
};
Word* ReadFromMemory(Memory* memory, int address){

    return memory->data[address];
};
void WriteToRegister(char* registerToWrt, char dataToWrt){
    registerToWrt = &dataToWrt;
};

char* ReadFromRegister(char *registerToRd){

    return registerToRd;
}
void Fetch(){

};
void Decode(){

};
void Execute(){

};

int main(int argc, char** kwargs){

    if(argc == 2){

        FILE *fp;
        CPU cpu;
        initializeCPU(&cpu);

        //FILE *fopen(const char *filename, const char *mode);
        fp = fopen(kwargs[1],"r"); //open a stream with r, w, a modes
        if(fp == NULL)
        {
        puts("error opening file!");
        exit (1);
        }
        char myString[12];
        int address= 0;
        while(fgets(myString, 12, fp)){
            memcpy(cpu.instructionMemory->data[address]->value,myString);
            address++;
        }
        

    }else{
        printf("Please give only file name\n");
    }

    return 0;
}