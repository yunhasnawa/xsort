#ifndef PARAM_H
#define PARAM_H

#include <string>

class Param
{
    public:
        Param();
        virtual ~Param();
        void set_memory_size(size_t msize);
        void set_output_fname(std::string fname);
        size_t get_memory_size();
        std::string get_output_fname();
        std::string get_input_fname();

    private:
        size_t memory_size;
        std::string output_fname;
        std::string input_fname;

    protected:
    private:
};

#endif // PARAM_H
