#ifndef ASM_PARSER_H
#define ASM_PARSER_H

typedef struct Program {
    char **text;
    int line_count;
} Program;

void Parser_init(const char *fileName);

void Parser_free();

typedef enum { A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION } InstructionType;

InstructionType Parser_instructionType();

char *Parser_symbol();

char *Parser_dest();

char *Parser_comp();

char *Parser_jump();

int Parser_hasMoreLines();

void Parser_advance();

#endif // ASM_PARSER_H
