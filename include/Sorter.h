#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include "Param.h"
#include "Input.h"

class Sorter
{
    public:
        Sorter(Param* param);
        virtual ~Sorter();
        void begin_sorting();

    protected:


    private:
        Param* param;
        std::vector<char*>* mem_block;
        size_t mem_limit;
        Input* input;
        int line_read_index;
        bool eof_reached;
        void init();
        void fill_mem_block();
};

#endif // SORTER_H
