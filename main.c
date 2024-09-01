#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define INSTRUCTION_SIZE 11
#define MEMORY_SIZE 32

typedef struct WORD{

    char* value;

}WORD;

typedef struct MEMORY{

    WORD instructionMemory[32];
    WORD dataMemory[16];
    WORD stackMemory[16];


}MEM;

typedef struct COMPUTER{

    MEM memory;

    int programCounter;
    int stackPointer;
    int addressRegister;

    char* inputRegister;
    char* outputRegister;
    char* instructionRegister;
    char* registers[3];
    bool halt;

    

}CMPT;

bool InitializeMemory(MEM* memory) {
    for (size_t i = 0; i < MEMORY_SIZE; i++) {
        memory->instructionMemory[i].value = malloc(12 * sizeof(char));
        if (memory->instructionMemory[i].value == NULL) {
            return false;
        }
    }
    for (size_t i = 0; i < MEMORY_SIZE / 2; i++) {
        memory->dataMemory[i].value = malloc(12 * sizeof(char));
        if (memory->dataMemory[i].value == NULL) {
            return false;
        }
        memory->stackMemory[i].value = malloc(12 * sizeof(char));
        if (memory->stackMemory[i].value == NULL) {
            return false;
        }
    }
    return true;
}

void FreeMemory(CMPT* cmpt) {
    free(cmpt->inputRegister);
    free(cmpt->outputRegister);
    free(cmpt->instructionRegister);
    free(cmpt->registers[2]);
    free(cmpt->registers[1]);
    free(cmpt->registers[0]);

}

char* GetRegister(CMPT* cmpt, char* value){

    if(value == "00"){
        return cmpt->registers[0];

    } else if (value == "01")
    {
        return cmpt->registers[1];

    }else if (value == "10")
    {
        return cmpt->registers[2];

    }else
    {
        return NULL;

    }
}

bool InitializeComputer(CMPT* cmpt){

    if(InitializeMemory(&cmpt->memory)){
        printf("Memory Initialized\n");
    }

    cmpt->addressRegister = 0;
    cmpt->stackPointer = 0;
    cmpt->programCounter = 0;

    cmpt->inputRegister = calloc(4,sizeof(char));
    cmpt->registers[0] = calloc(4,sizeof(char));
    cmpt->registers[1] = calloc(4,sizeof(char));
    cmpt->registers[2] = calloc(4,sizeof(char));
    cmpt->outputRegister = calloc(4,sizeof(char));
    cmpt->instructionRegister = calloc(11,sizeof(char));
    cmpt->halt = false;
    
    printf("Computer Has Started\n");

}


void Fetch(CMPT* cmpt){

    cmpt->instructionRegister = cmpt->memory.instructionMemory[cmpt->programCounter].value;
    cmpt->programCounter++;
   
}
void Decode(CMPT* cmpt){

    char* adrr;
    strncpy(adrr,cmpt->instructionRegister+7,4);
    cmpt->addressRegister = strtol(adrr,NULL,2);    
}
char* GetRegister(char* dest,CMPT* cmpt){

    if(dest == "00"){
        return cmpt->registers[0];
    }else if(dest == "01"){
        return cmpt->registers[1];
    }else if(dest == "10"){
        return cmpt->registers[2];
    }else if(dest == "11"){
        return cmpt->registers[3];
    }else{
        return NULL;
    }
    

}
void Execute(CMPT* cmpt){
    char opcode[5];
    char Rd[3];
    char S1[3];
    char S2[3];
    char Q = &cmpt->instructionRegister;
    strncpy(opcode,cmpt->instructionRegister+1,4);
    strncpy(Rd,cmpt->instructionRegister+5,2);
    strncpy(S1,cmpt->instructionRegister+7,2);
    strncpy(S2,cmpt->instructionRegister+9,2);
    
    opcode[4] = '\0';
    Rd[3] = '\0';
    S2[3] = '\0';
    S1[3] = '\0';

    if (strcmp(opcode, "0111") == 0) {
        // HLT - Halt the computer
        printf("Executing HLT (Halt the computer)\n");

        cmpt->halt = true;
    } else if (strcmp(opcode, "0000") == 0) {
        // DBL - Double content of S1 and store result in Rd
        printf("Executing DBL (Double content of S1 and store result in Rd)\n");

        char* selecReg = GetRegister(cmpt,S1);
        &GetRegister(cmpt,Rd) = BinaryShift(selecReg,0);

    } else if (strcmp(opcode, "0001") == 0) {
        // DBT - Divide content of S1 by 2 and store result to Rd
        printf("Executing DBT (Divide content of S1 by 2 and store result to Rd)\n");

        char* selecReg = GetRegister(cmpt,S1);
        GetRegister(cmpt,Rd) = BinaryShift(selecReg,1);

    } else if (strcmp(opcode, "0010") == 0) {
        // ADD - Add content of S1 and S2 and store result in Rd
        printf("Executing ADD (Add content of S1 and S2 and store result in Rd)\n");
        
        // Implement ADD functionality here
    } else if (strcmp(opcode, "0011") == 0) {
        // NOT - Complement S1 content and load the result into D
        printf("Executing NOT (Complement S1 content and load the result into D)\n");
        // Implement NOT functionality here
    } else if (strcmp(opcode, "0100") == 0) {
        // XOR - XOR contents of S1 and S2 and store result in Rd
        printf("Executing XOR (XOR contents of S1 and S2 and store result in Rd)\n");
        // Implement XOR functionality here
    } else if (strcmp(opcode, "0101") == 0) {
        // ADD - Add content of S1 and S2 and store result in Rd
        printf("Executing ADD (Add content of S1 and S2 and store result in Rd)\n");
        // Implement ADD functionality here
    } else if (strcmp(opcode, "0110") == 0) {
        // INC - Increase content of S1 and store result in Rd
        printf("Executing INC (Increase content of S1 and store result in Rd)\n");
        // Implement INC functionality here
    } else if (strcmp(opcode, "1000") == 0) {
        // ST - Store content
        printf("Executing ST (Store content)\n");
        // Implement ST functionality here
    } else if (strcmp(opcode, "1001") == 0) {
        // LD - Load content
        printf("Executing LD (Load content)\n");
        // Implement LD functionality here
    } else if (strcmp(opcode, "1010") == 0) {
        // IO - Input/Output operation
        printf("Executing IO (Input/Output operation)\n");
        // Implement IO functionality here
    } else if (strcmp(opcode, "1011") == 0) {
        // TSF - Transfer data
        printf("Executing TSF (Transfer data)\n");

        
    } else if (strcmp(opcode, "1100") == 0) {
        // JMP - Jump to address
        printf("Executing JMP (Jump to address)\n");

        char* adrr;
        strncpy(adrr,cmpt->instructionRegister+6,5);
        cmpt->programCounter = strtol(adrr,NULL,2);

    } else if (strcmp(opcode, "1101") == 0) {
        // CAL - Call subroutine
        printf("Executing CAL (Call subroutine)\n");

        if(cmpt->stackPointer < 16){
            snprintf( )
            cmpt->memory.stackMemory[cmpt->stackPointer].value = cmpt->programCounter;
            cmpt->stackPointer++;
        }
    } else if (strcmp(opcode, "1110") == 0) {
        // RET - Return from subroutine
        printf("Executing RET (Return from subroutine)\n");

        if(cmpt->stackPointer>-1){
            cmpt->stackPointer--;            
            cmpt->programCounter = strtol(cmpt->memory.stackMemory[cmpt->stackPointer].value,NULL,10);
;
        }
    } else if (strcmp(opcode, "1111") == 0) {
        // JMR - Jump relative
        printf("Executing JMR (Jump relative)\n");

        if(cmpt->addressRegister>=8){
            cmpt->addressRegister = cmpt->addressRegister-16;
        }
        cmpt->programCounter +=cmpt->addressRegister;

    } else {
        printf("Unknown opcode: %s\n", opcode);
    }
}




int main(int argc , char* argv[]){

    if(argc == 2 || argc == 3)
    {
        FILE *instructionFile;

        instructionFile = fopen(argv[1],"r");

        if(instructionFile != NULL){

            CMPT cmpt;

            InitializeComputer(&cmpt);

            char buffer[12];

            int count = 0;
            
            while(fread(buffer,1,11,instructionFile) == 11)
            {
                buffer[11] = '\0';
                strncpy(cmpt.memory.instructionMemory[count].value,buffer,12); 
                count++;
                
                if(count == 32)
                {
                    printf("Instruction memory capacity reached");
                    break;
                }

            }
            fclose(instructionFile);


            FILE *dataFile;

            dataFile = fopen(argv[2],"r");

            if(dataFile != NULL){

                count = 0;

                while(fread(buffer,1,11,dataFile) == 11)
                {
                    buffer[11] = '\0';

                    strncpy(cmpt.memory.dataMemory[count].value,buffer,12); 

                    count++;

                    if(count == 32)
                    {
                        printf("Data memory capacity reached");

                        break;
                    }
                }
                fclose(dataFile);

            }
            
            

            while(!cmpt.halt){
                Fetch(&cmpt);

                Decode(&cmpt);

                Execute(&cmpt);

            }
            

            

                
            
            FreeMemory(&cmpt);

        }else
        {
            perror("Instruction File cannot found");
        }
    }else {

        perror("Please provide Instruction file");

    }
    return 0;
}