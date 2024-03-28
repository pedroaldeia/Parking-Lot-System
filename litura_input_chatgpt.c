#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitura.h"

#define BUFSIZ 8192

// Function to split the input line into words
// Function to split the input line into words
int splitLine(char *line, char ***words) {
    int count = 0;
    char **wordList = malloc(BUFSIZ * sizeof(char*));

    if (wordList == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Initialize pointers
    char *start = line;
    char *end = line;
    char inQuote = 0;

    // Iterate through the line
    while (*end != '\0') {
        // If encountering a double quote
        if (*end == '"') {
            // Toggle inQuote flag
            inQuote = !inQuote;
        } else if (*end == ' ' && !inQuote) {
            // If encountering a space outside quotes, it marks the end of a word
            int length = end - start;
            if (length > 0) {
                // Allocate memory for the word
                wordList[count] = malloc((length + 1) * sizeof(char));
                if (wordList[count] == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                // Copy the word into the allocated memory
                strncpy(wordList[count], start, length);
                wordList[count][length] = '\0';
                // Remove double quotes from the word if present
                char *quotePtr = strchr(wordList[count], '"');
                if (quotePtr != NULL) {
                    memmove(quotePtr, quotePtr + 1, strlen(quotePtr)); // Shift characters left
                    wordList[count][strlen(wordList[count]) - 1] = '\0'; // Null-terminate the string
                }
                count++;
            }
            // Move start pointer to the next character after the space
            start = end + 1;
        }
        // Move to the next character
        end++;
    }

    // Process the last word (or the only word if there is only one)
    int length = end - start;
    if (length > 0) {
        // Allocate memory for the word
        wordList[count] = malloc((length + 1) * sizeof(char));
        if (wordList[count] == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        // Copy the word into the allocated memory
        strncpy(wordList[count], start, length);
        wordList[count][length] = '\0';
        // Remove double quotes from the word if present
        char *quotePtr = strchr(wordList[count], '"');
        if (quotePtr != NULL) {
            memmove(quotePtr, quotePtr + 1, strlen(quotePtr)); // Shift characters left
            wordList[count][strlen(wordList[count]) - 1] = '\0'; // Null-terminate the string
        }
        count++;
    }

    // Reallocate memory to fit exactly the number of words
    *words = realloc(wordList, count * sizeof(char*));
    if (*words == NULL) {
        printf("Memory reallocation failed.\n");
        exit(1);
    }

    return count;
}

char * lineinput() {
    char  * line = (char *) malloc(sizeof(char)* BUFSIZ);
    int i = 0;
    char c;
    for(c = getchar(); c != '\n'; c = getchar()){
        line[i++] = c;
    }
    line[i] = '\0';
    return line;
}

void free_input(char ** palavras, int n_args) {
    int i;

    for(i = 0; i < n_args; i++) {
        free(palavras[i]);
    }
    free(palavras);
}

// Main function to read input line and return list of words
char ** wordArray(char *line) {
    char **words;

    // Remove trailing newline character, if present
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    // Split the line into words
    splitLine(line, &words);

    free(line);

    return words;
}
