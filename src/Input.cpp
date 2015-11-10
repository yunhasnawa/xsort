#include "Input.h"
#include <iostream>
#include <string.h>

Input::Input(std::string fname)
{
    this->fname = fname;
    this->in_stream = new std::ifstream(this->fname.c_str(), std::ifstream::binary);
    this->last_char_found_size = 0;
    this->last_char_found_index = -1;
}

Input::~Input()
{
    this->in_stream->close();
    delete this->in_stream;
}

size_t Input::get_last_char_found_size()
{
    return this->last_char_found_size;
}

int Input::get_last_char_found_index()
{
    return this->last_char_found_index;
}

std::string Input::read_until_char_found(size_t start, char seek)
{
    this->last_char_found_size = 0;
    this->last_char_found_index = -1;

    std::string text = "";

    if(this->in_stream != NULL)
    {
        bool go = true;

        size_t seek_pos = start;

        size_t total_read = 0;

        while(go)
        {
            this->in_stream->seekg(seek_pos);

            char buffer[2];

            this->in_stream->read(buffer, 1);

            if(buffer[0] != seek)
            {
                buffer[1] = '\0';

                std::string found(buffer);

                text += found;

                total_read++;

                seek_pos++;
            }
            else
            {
                go = false;

                this->last_char_found_index = seek_pos;
            }
        }

        this->last_char_found_size = total_read;
    }

    return text;
}
