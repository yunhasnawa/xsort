#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <fstream>

class Input
{
    public:
        Input(std::string fname);
        virtual ~Input();
        std::string read_until_char_found(size_t start, char seek);
        size_t get_last_char_found_size();
        int get_last_char_found_index();

    protected:

    private:
        std::string fname;
        std::ifstream* in_stream;
        size_t last_char_found_size;
        int last_char_found_index;
};

#endif // INPUT_H
