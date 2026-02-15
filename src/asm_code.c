#include "asm_code.h"
#include <string.h>

char *CODE_dest(const char *ins) {
    static char buf[] = "000";

    buf[0] = buf[1] = buf[2] = '0';

    if (strchr(ins, 'A'))
        buf[0] = '1';
    if (strchr(ins, 'D'))
        buf[1] = '1';
    if (strchr(ins, 'M'))
        buf[2] = '1';

    return buf;
}

char *CODE_comp(const char *ins) {
    if (strcmp(ins, "0") == 0) 
        return "0101010";
    else if (strcmp(ins, "1") == 0)
        return "0111111";
    else if (strcmp(ins, "-1") == 0)
        return "0111010";
    else if (strcmp(ins, "D") == 0)
        return "0001100";
    else if (strcmp(ins, "A") == 0)
        return "0110000";
    else if (strcmp(ins, "M") == 0)
        return "1110000";
    else if (strcmp(ins, "!D") == 0)
        return "0001101";
    else if (strcmp(ins, "!A") == 0)
        return "0110001";
    else if (strcmp(ins, "!M") == 0)
        return "1110001";
    else if (strcmp(ins, "-D") == 0)
        return "0001111";
    else if (strcmp(ins, "-A") == 0)
        return "0110011";
    else if (strcmp(ins, "-M") == 0)
        return "1110011";
    else if (strcmp(ins, "D+1") == 0)
        return "0011111";
    else if (strcmp(ins, "A+1") == 0)
        return "0110111";
    else if (strcmp(ins, "M+1") == 0)
        return "1110111";
    else if (strcmp(ins, "D-1") == 0)
        return "0001110";
    else if (strcmp(ins, "A-1") == 0)
        return "0110010";
    else if (strcmp(ins, "M-1") == 0)
        return "1110010";
    else if (strcmp(ins, "D+A") == 0)
        return "0000010";
    else if (strcmp(ins, "D+M") == 0)
        return "1000010";
    else if (strcmp(ins, "D-A") == 0)
        return "0010011";
    else if (strcmp(ins, "D-M") == 0)
        return "1010011";
    else if (strcmp(ins, "A-D") == 0)
        return "0000111";
    else if (strcmp(ins, "M-D") == 0)
        return "1000111";
    else if (strcmp(ins, "D&A") == 0)
        return "0000000";
    else if (strcmp(ins, "D&M") == 0)
        return "1000000";
    else if (strcmp(ins, "D|A") == 0)
        return "0010101";
    else if (strcmp(ins, "D|M") == 0)
        return "1010101";
    else
        return NULL;
}

char *CODE_jump(const char *ins) {
    if (strcmp(ins, "JGT") == 0)
        return "001";
    else if (strcmp(ins, "JEQ") == 0)
        return "010";
    else if (strcmp(ins, "JGE") == 0)
        return "011";
    else if (strcmp(ins, "JLT") == 0)
        return "100";
    else if (strcmp(ins, "JNE") == 0)
        return "101";
    else if (strcmp(ins, "JLE") == 0)
        return "110";
    else if (strcmp(ins, "JMP") == 0)
        return "111";
    else
        return "000";
}
