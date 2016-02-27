#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "parser.h"

void printHelp() {
    std::cout
        << "Usage: dboc -o <OUTFILE> <INFILE>" << std::endl
        << "Parameter:" << std::endl
        << "  -o <OUTFILE> Specifies the file, where we should output the source code" << std::endl
        << "  <INFILE> Specifies the input file" << std::endl;
    /**
     * accept dboc -d <DIRECTORY> <SOURCE> ...
     * DIRECTORY is target directory
     * SOURCE is the source file, where each source file will be compiled to `basedir SOURCE`/dbo_`filename SOURCE`.cpp
     **/
}

int main (int argc, char **argv)
{
    char *outFile = NULL;
    char *inFile = NULL;
    int index;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "ho:")) != -1)
        switch (c)
        {
            case 'h':
                printHelp();
                abort();
            case 'o':
                outFile = optarg;
                break;
            case '?':
                if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                            "Unknown option character `\\x%x'.\n",
                            optopt);
                return 1;
            default:
                abort ();
        }

    for (index = optind; index < argc; index++) {
        inFile = argv[index];
    }

    if (inFile == NULL)
        std::cerr << "No input file specified" << std::endl;

    if (outFile == NULL)
        std::cerr << "No output file specified" << std::endl;

    try {
        Parser parser(inFile);
        parser.write(outFile);
    } catch(const char * c) {
        std::cerr << c << std::endl;
    }

    return 0;
}
