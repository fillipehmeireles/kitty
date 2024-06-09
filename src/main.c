#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SIZE 1024

void usage(){
    printf("kitty <filename> -c x:y");
}

int main(int argc, char**argv){
    if(argc < 2)
    {
        usage();
        return EXIT_FAILURE;
    }
    char options [] = { "-c" };
    if (strcmp(argv[2], &options[0]) != 0) {
        usage();
        return EXIT_FAILURE;
    }
    char *filename = argv[1];
    char *chunk_lines = strtok(argv[3], ":");
    if(chunk_lines == NULL)
    {
        usage();
        return EXIT_FAILURE;
    }

    int lines[2];
    int i = 0;
    while (chunk_lines != NULL)
    {
        int l = atoi(chunk_lines);
        lines[i] = l;
        i++;
        chunk_lines = strtok(NULL, ":");
    }
    bool to_file_end;
    if(lines[1] == -1)
        to_file_end = true;

    FILE *fptr;
    fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
        perror("error on opening file: ");
        return EXIT_FAILURE;
    }

    unsigned int dyn_len = BUFF_SIZE * sizeof(char);
    char *file_content = malloc( dyn_len);

    int current_line = 1;
    while(fgets(file_content, dyn_len, fptr)) {
        if(current_line >= lines[0])
            printf("\e[1;34m %d \e[0;37m \t %s", current_line,file_content);
        if(!to_file_end)
            if(current_line >= lines[1])
                break;
        current_line++;
    }
    if(!to_file_end)
        if(lines[1] > current_line)
            printf("\e[1;33m [!] Warning: File has %d lines, but input was %d.", current_line, lines[1]);
    fclose(fptr);
    free(file_content);
    return EXIT_SUCCESS;
}
