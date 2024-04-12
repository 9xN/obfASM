#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 512

const char* random_asm_code[] = {
    "NOP",                         // No operation
    "MOV AX, AX",                  // Moves a value to the same place
    "MOV EAX, EAX",                // Moves a value to the same place
    "XCHG BX, BX",                 // Exchanges the value of a register with itself
    "ADD EAX, 0",                  // Adds zero to a register
    "AND EAX, 0xFFFFFFFF",         // Logical AND operation with all ones
    "OR EAX, 0x0",                 // Logical OR operation with all zeros
    // ... more asm lines as needed
};

void insert_random_code(FILE* output) {
    fputs(random_asm_code[rand() % (sizeof(random_asm_code) / sizeof(char*))], output);
    fputs("\n", output);
}

void process_file(FILE* input, FILE* output) {
    char** lines = NULL;
    size_t line_count = 0;

    // read lines
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), input)) {
        char* new_line = strdup(line);
        if (!new_line) {
            perror("strdup");
            exit(1);
        }

        line_count += 1;
        char** new_lines = realloc(lines, line_count * sizeof *new_lines);
        if (!new_lines) {
            perror("realloc");
            exit(1);
        }

        new_lines[line_count - 1] = new_line;
        lines = new_lines;
    }

    // write with random inserts
    for (size_t i = 0; i < line_count; i++) {
        insert_random_code(output);         // Insert random line before the actual line
        fputs(lines[i], output);            // Write the actual line from the input
        free(lines[i]);                     // Free line memory
        insert_random_code(output);         // Insert random line after the actual line
    }
    free(lines);
}

int main(int argc, char** argv) {
    srand((unsigned int)time(0)); // Initialize the random number generator

    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if (!input || !output) {
        perror("fopen");
        return 1;
    }

    process_file(input, output);

    fclose(input);
    fclose(output);
    return 0;
}
