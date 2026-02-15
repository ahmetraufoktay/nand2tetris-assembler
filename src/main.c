#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include <sys/types.h>
#include <unistd.h>
#include "asm_code.h"
#include "asm_parser.h"
#include "asm_symboltable.h"

void toBinary(int n, char *buf) {
    for (int i = 14; i >= 0; i--) {
        buf[14 - i] = (n & (1 << i)) ? '1' : '0';
    }
    buf[15] = '\0';
}

int main(int argc, char** argv) {
    FILE* out;
    int romAddr = 0;
    int nextVarAddr = 16;
    
    char* sym;
    char bin[16];
    int addr;
    
    char *pd, *pc, *pj;
    char *d, *c, *j;

    if (argc < 2) {
        printf("Assembler Kullanim: %s <dosya.asm>\n", argv[0]);
        return 1;
    }
    
    SymbolTable_init();
    Parser_init(argv[1]);
    
    // --- FIRST PASS --- //
    while (Parser_hasMoreLines()) {
        InstructionType type = Parser_instructionType();
        if (type == L_INSTRUCTION) {
            SymbolTable_addEntry(Parser_symbol(), romAddr);
        } else {
            romAddr++;
        }
        Parser_advance();
    }
    Parser_free();

    // --- SECOND PASS --- //
    Parser_init(argv[1]);
    out = fopen("Prog.hack", "w");

    while (Parser_hasMoreLines()) {
        InstructionType type = Parser_instructionType();

        if (type == A_INSTRUCTION) {
            sym = Parser_symbol();
            if (isdigit(sym[0])) {
                addr = atoi(sym);
            } else {
                if (!SymbolTable_contains(sym)) {
                    SymbolTable_addEntry(sym, nextVarAddr++);
                }
                addr = SymbolTable_getAddress(sym);
            }
            toBinary(addr, bin);
            fprintf(out, "0%s\n", bin);
        } else if (type == C_INSTRUCTION) {
            pd = Parser_dest();
            pc = Parser_comp();
            pj = Parser_jump();

            d = CODE_dest(pd ? pd : "");
            c = CODE_comp(pc);
            j = CODE_jump(pj ? pj : "");

            fprintf(out, "111%s%s%s\n", c, d, j);
        }
        Parser_advance();
    }

    // -- REMOVE LAST LINE \n -- //
    fflush(out);
    fseek(out, -1, SEEK_END);
    #ifdef _WIN32
        _chsize(_fileno(out), ftell(out));
    #else
        ftruncate(fileno(out), ftell(out));
    #endif

    fclose(out);
    Parser_free();
    SymbolTable_free();
    return 0;
}
