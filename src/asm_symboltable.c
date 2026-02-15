#include "asm_symboltable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static SymbolTable st;

void SymbolTable_init() {
    st.size = 0;
    st.capacity = 64;
    st.entries = malloc(st.capacity * sizeof(Symbol));
    if (!st.entries) {
        perror("malloc");
        exit(1);
    }
    
    char r_sym[4];
    for (int i = 0; i < 16; i++) {
        sprintf(r_sym, "R%d", i);
        SymbolTable_addEntry(r_sym, i);
    }

    SymbolTable_addEntry("SP",     0);
    SymbolTable_addEntry("LCL",    1);
    SymbolTable_addEntry("ARG",    2);
    SymbolTable_addEntry("THIS",   3);
    SymbolTable_addEntry("THAT",   4);

    SymbolTable_addEntry("SCREEN", 16384);
    SymbolTable_addEntry("KBD",    24576);
}

void SymbolTable_addEntry(const char *symbol, int address) {
    if (SymbolTable_contains(symbol))
        return;

    if (st.size == st.capacity) {
        st.capacity *= 2;
        st.entries = realloc(st.entries, st.capacity * sizeof(Symbol));
        if (!st.entries) {
            perror("realloc");
            exit(1);
        }
    }

    st.entries[st.size].symbol = strdup(symbol);
    st.entries[st.size].address = address;
    st.size++;
}

int SymbolTable_contains(const char *symbol) {
    for (int i = 0; i < st.size; i++) {
        if (strcmp(st.entries[i].symbol, symbol) == 0)
            return 1;
    }
    return 0;
}

int SymbolTable_getAddress(const char *symbol) {
    for (int i = 0; i < st.size; i++) {
        if (strcmp(st.entries[i].symbol, symbol) == 0)
            return st.entries[i].address;
    }
    return -1;
}

void SymbolTable_free() {
    for (int i = 0; i < st.size; i++) {
        free(st.entries[i].symbol);
    }
    free(st.entries);
}
