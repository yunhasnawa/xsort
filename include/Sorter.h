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
        int saved_mem_block;
        void init();
        void fill_mem_block();
        void sort_mem_block();
        void save_mem_block();
        void init_mem_block();
        std::string current_mem_block_fname();
};

#endif // SORTER_H
