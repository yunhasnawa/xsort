#include <stdlib.h>
#include <iostream>
#include <getopt.h>
#include "Param.h"
#include "Sorter.h"

using namespace std;

int main(int argc, char* argv[])
{
    Param* p = new Param;

    char c;

    while((c = getopt(argc, argv, "m:o:")) != -1)
    {
        switch(c)
        {
        case 'm':
            {
                size_t msize = atoi(optarg);
                p->set_memory_size(msize);
            }
        case 'o':
            {
                std::string fname(optarg);
                p->set_output_fname(fname);
            }
        default:
            {
                // Nothing here yet..
            }
        }
    }

    Sorter* sorter = new Sorter(p);
    sorter->begin_sorting();

    delete sorter;

    return 0;
}
