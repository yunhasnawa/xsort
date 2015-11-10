#include "Sorter.h"
#include <algorithm>
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
    this->mem_block = new std::vector<std::string>;
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
        //std::cout << "---- Start read at: " << this->line_read_index << std::endl;

        std::string line = this->input->read_until_char_found(this->line_read_index, '\n'); // Read a line.

        size_t read_size = this->input->get_last_char_found_size();

        if(read_size < 1)
        {
            this->eof_reached = true;

            break; // No more content to read.
        }
        else
        {
            this->mem_block->push_back(line);

            //std::cout << ">>" << line << "<<" << std::endl;

            total_read += read_size;

            //std::cout << "---- Total read: " << line.length() << std::endl;

            if(total_read >= this->mem_limit)
            {
                break; // Memory block is full, stop right now!
            }
            else
            {
                int last_index = this->input->get_last_char_found_index();

                //std::cout << "---- Newline found at: " << last_index << std::endl;

                this->line_read_index = last_index + 1;
            }
        }
    }
}

void Sorter::sort_mem_block()
{
    sort(this->mem_block->begin(), this->mem_block->end());

    std::vector<std::string>::iterator it;

    for(it = this->mem_block->begin(); it < this->mem_block->end(); it++)
    {
        std::cout << *it << std::endl;
    }
}

void Sorter::begin_sorting()
{
    std::cout << "============== BEGIN SORTING ==============" << std::endl;

    int limit = 0;

    while(!this->eof_reached)
    {
        this->fill_mem_block();

        std::cout << "----------------------" << std::endl;
        std::cout << "----- Block FULL -----" << std::endl;
        std::cout << "----------------------" << std::endl;

        this->sort_mem_block();

        limit++;
        if(limit > 2)
            break;
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

/*
void Sorter::quick_sort(std::vector<string>* lines, size_t line_count)
{
    if(line_count < 2)
        return;

    std::string pivot = lines.at(line_count/2);

    std::vector<string>* left = lines;
    std::vector<string>* right = lines + (line_count - 1);

    while (left <= right)
    {
        if(strcmp(*left, pivot) < 0)
        {
            left++;
        }
        else if(strcmp(*right, pivot) > 0)
        {
            right--;
        }
        else
        {
            // Swap
            char* temp = *left;
            *left = *right;
            *right = temp;

            left++;
            right--;
        }
    }
    Engine::quickSort(lines, (right - lines + 1));
    Engine::quickSort(left, (lines + lineCount - left));
}
*/
