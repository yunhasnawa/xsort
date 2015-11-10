#include "Sorter.h"
#include <string>
#include <string.h>
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
    this->mem_block = new std::vector<char*>;
    this->mem_limit = this->param->get_memory_size() * 1024; // In MB
    this->input = new Input(this->param->get_input_fname());
    this->line_read_index = 0;
    this->eof_reached = false;
}

void Sorter::fill_mem_block()
{
    size_t total_read = 0;

    bool go = true;

    while(go)
    {
        std::cout << "---- Start read at: " << this->line_read_index << std::endl;

        std::string line = this->input->read_until_char_found(this->line_read_index, '\n'); // Read a line.

        size_t read_size = this->input->get_last_char_found_size();

        if(read_size < 1)
        {
            this->eof_reached = true;

            break; // No more content to read.
        }
        else
        {
            std::cout << ">>" << line << "<<" << std::endl;

            total_read += read_size;

            std::cout << "---- Total read: " << line.length() << std::endl;

            if(total_read >= this->mem_limit)
            {
                break; // Memory block is full, stop right now!
            }
            else
            {
                int last_index = this->input->get_last_char_found_index();

                std::cout << "---- Newline found at: " << last_index << std::endl;

                this->line_read_index = last_index + 1;
            }
        }
    }
}

void Sorter::begin_sorting()
{
    std::cout << "============== BEGIN SORTING ==============" << std::endl;

    while(!this->eof_reached)
    {
        this->fill_mem_block();

        std::cout << "----------------------" << std::endl;
        std::cout << "----- Block FULL -----" << std::endl;
        std::cout << "----------------------" << std::endl;
    }

    /*
    std::string line0 = this->input->read_until_char_found(0, '\n'); // Read a line.
    std::cout << line0 << std::endl;
    std::string line1 = this->input->read_until_char_found(101, '\n'); // Read a line.
    std::cout << line1 << std::endl;
    std::string line2 = this->input->read_until_char_found(202, '\n'); // Read a line.
    std::cout << line2 << std::endl;
    std::string line3 = this->input->read_until_char_found(303, '\n'); // Read a line.
    std::cout << line3 << std::endl;
    */
}
