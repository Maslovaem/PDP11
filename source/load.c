#include <stdio.h>
#include <stdlib.h>

#include "../headers/load.h"
#include "../headers/mem.h"
#include "../headers/logger.h"

void load_data(FILE *stream)
{
    unsigned int a = 0;
    unsigned int n = 0;
    unsigned int temp = 0;
    while (2 == fscanf(stream, "%x%x", &a, &n))
    {
        for (int i = 0; i < n; i++)
        {
            fscanf(stream, "%x", &temp);
            b_write(a + i, (byte)temp);
        }
    }
}

void load_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror(filename);
        exit(1);
    }
    load_data(file);
    fclose(file);
}

void usage(const char *prog)
{
    log_(ERROR, "USAGE: %s file\n file - PDP11 execution fault", prog);
}
