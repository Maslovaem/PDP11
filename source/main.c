#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../headers/mem.h"
#include "../headers/logger.h"
#include "../headers/run.h"
#include "../headers/test_mem.h"
#include "../headers/load.h"
#include "../headers/command.h"

int main(int argc, char *argv[])
{
    CURRENT_LEVEL = DEBUG;

    test_mem();

    if (argc - 1 == 0)
    {
        usage(argv[0]);
        exit(0);
    }

    load_file(argv[1]);


    run();

    return 0;
}
