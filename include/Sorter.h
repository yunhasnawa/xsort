#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <string>
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
        std::vector<std::string>* mem_block;
        size_t mem_limit;
        Input* input;
        int line_read_index;
        bool eof_reached;
        void init();
        void fill_mem_block();
        void sort_mem_block();
        //static void quick_sort(std::vector<string>* lines, size_t line_count);
};

#endif // SORTER_H
