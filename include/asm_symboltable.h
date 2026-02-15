#ifndef ASM_SYMBOLTABLE_H
#define ASM_SYMBOLTABLE_H

typedef struct {
    char *symbol;
    int address;
} Symbol;

typedef struct {
    Symbol *entries;
    int size;
    int capacity;
} SymbolTable;

void SymbolTable_init();

void SymbolTable_addEntry(const char *symbol, int address);

int SymbolTable_contains(const char *symbol);

int SymbolTable_getAddress(const char *symbol);

void SymbolTable_free();

#endif // ASM_SYMBOLTABLE_H
