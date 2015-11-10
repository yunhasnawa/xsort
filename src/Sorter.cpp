#include "Sorter.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

Sorter::Sorter(Param* param)
{
    this->param = param;

    this->init();
}

Sorter::~Sorter()
{
    delete this->mem_block;
    delete this->input;
}

void Sorter::init()
{
    this->init_mem_block();
    this->mem_limit = this->param->get_memory_size() * 1024; // In MB
    this->input = new Input(this->param->get_input_fname());
    this->line_read_index = 0;
    this->eof_reached = false;
    this->saved_mem_block = 0;
}

std::string Sorter::current_mem_block_fname()
{
    std::string name = "result/mem_block_";

    std::ostringstream s;

    s << this->saved_mem_block;

    std::string num = s.str();

    name += (num + ".parts");

    return name;
}

void Sorter::fill_mem_block()
{
    std::cout << "-- Reading from files.." << std::endl;

    size_t total_read = 0;

    bool go = true;

    while(go)
    {
        // Read a line.
        std::string line = this->input->read_until_char_found(this->line_read_index, '\n');

        size_t read_size = this->input->get_last_char_found_size();

        if(read_size < 1)
        {
            this->eof_reached = true;

            break; // No more content to read.
        }
        else
        {
            this->mem_block->push_back(line);

            total_read += read_size;

            if(total_read >= this->mem_limit)
            {
                break; // Memory block is full, stop right now!
            }
            else
            {
                int last_index = this->input->get_last_char_found_index();

                this->line_read_index = last_index + 1;
            }
        }
    }
}

void Sorter::sort_mem_block()
{
    std::cout << "-- Sorting memory blocks.." << std::endl;

    sort(this->mem_block->begin(), this->mem_block->end());
}

void Sorter::save_mem_block()
{
    std::cout << "-- Saving memory blocks to parts." << std::endl;

    std::string concat = "";

    std::vector<std::string>::iterator it;

    for(it = this->mem_block->begin(); it < this->mem_block->end(); it++)
    {
        std::string s = *it;
        concat += (s + "\n");
    }

    std::string fname = this->current_mem_block_fname();

    std::ofstream out(fname.c_str());

    out << concat;

    out.close();

    this->saved_mem_block++;
}

void Sorter::init_mem_block()
{
    this->mem_block = new std::vector<std::string>;
}

void Sorter::begin_sorting()
{
    std::cout << "============== BEGIN SORTING ==============" << std::endl;

    int limit = 0;

    while(!this->eof_reached)
    {
        this->fill_mem_block();
        this->sort_mem_block();
        this->save_mem_block();
        this->init_mem_block();

        std::cout << "**********************" << std::endl;
        std::cout << "--------- " << this->saved_mem_block << " ---------" << std::endl;
        std::cout << "**********************" << std::endl;

        limit++;
        if(limit > 99)
            break;
    }
}
