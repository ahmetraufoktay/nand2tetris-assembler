#include "asm_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Program program;
static int lineIdx;
static char* currentLine = NULL;

static int cleanLine(char *line) {
    char *comment = strstr(line, "//");
    if (comment)
        *comment = '\0';

    // trim left (MOVE CONTENT)
    char *start = line;
    while (*start == ' ' || *start == '\t')
        start++;

    if (start != line)
        memmove(line, start, strlen(start) + 1);

    // trim right
    char *end = line + strlen(line) - 1;
    while (end >= line && (*end == ' ' || *end == '\t' || *end == '\n'))
        *end-- = '\0';

    return *line != '\0';
}

void Parser_init(const char *fileName) {
    FILE* fp = fopen(fileName, "r");
    char line[256];

    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    program.text = NULL;
    program.line_count = 0;
    lineIdx = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (cleanLine(line)) {
            char **tmp = realloc(
            program.text,
            (program.line_count + 1) * sizeof(char *)
            );

            if (!tmp) {
                perror("realloc");
                exit(1);
            }

            program.text = tmp;
            program.text[program.line_count++] = strdup(line);
        }
    }

    currentLine = program.text[lineIdx];
    fclose(fp);
}

void Parser_free() {
    int i;

    if (!program.text) 
        return;
    
    for (i = 0; i < program.line_count; ++i) {
        free(program.text[i]);
    }

    free(program.text);

    program.text = NULL;
    program.line_count = 0;
}

InstructionType Parser_instructionType() {
    if (currentLine[0] == '@')
        return A_INSTRUCTION;
    if (currentLine[0] == '(') 
        return L_INSTRUCTION;
    return C_INSTRUCTION;
}

char *Parser_symbol() {
    static char buf[64];

    if (currentLine[0] == '@') {
        strcpy(buf, currentLine + 1);
        return buf;
    } 
    
    if (currentLine[0] == '(') {
        int len;
        
        char *end = strchr(currentLine, ')');
        
        if (!end) return NULL;

        len = end - (currentLine + 1);
        strncpy(buf, currentLine + 1, len);
        buf[len] = '\0';
        return buf;
    }

    return NULL;
}

char *Parser_dest() {
    static char buf[4];
    char *eq = strchr(currentLine, '=');
    int len;

    if (!eq)
        return NULL;

    len = eq - currentLine;
    strncpy(buf, currentLine, len);
    buf[len] = '\0';
    return buf;
}

char *Parser_comp() {
    static char buf[10];
    char *start = currentLine;
    char *end;

    int len;

    char *eq = strchr(currentLine, '=');
    char *sc = strchr(currentLine, ';');

    if (eq)
        start = eq + 1;

    if (sc)
        end = sc;
    else 
        end = currentLine + strlen(currentLine);

    len = end - start;
    strncpy(buf, start, len);
    buf[len] = '\0';
    return buf;
}

char *Parser_jump() {
    static char buf[4];
    char *sc = strchr(currentLine, ';');

    if (!sc) 
        return NULL;
    
    strncpy(buf, sc + 1, 3);
    buf[3] = '\0';
    return buf;
}

int Parser_hasMoreLines() {
    return lineIdx < program.line_count;
}

void Parser_advance() {
    lineIdx++;
    if (Parser_hasMoreLines()) {
        currentLine = program.text[lineIdx];
    } else {
        currentLine = NULL;
    }
}
