#include "Param.h"

Param::Param()
{
    //ctor
    this->memory_size = 0;
    this->output_fname = "";
    this->input_fname = "input10mb.yxs";
}

Param::~Param()
{
    //dtor
}

void Param::set_memory_size(size_t msize)
{
    this->memory_size = msize;
}

void Param::set_output_fname(std::string fname)
{
    this->output_fname = fname;
}

size_t Param::get_memory_size()
{
    return this->memory_size;
}

std::string Param::get_output_fname()
{
    return this->output_fname;
}

std::string Param::get_input_fname()
{
    return this->input_fname;
}
