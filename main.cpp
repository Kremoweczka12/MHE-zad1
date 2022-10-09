#include <fstream>
#include <iostream>
#include "json.hpp"
#include <string>


int main(int argc, char **argv) {
    try {
        std::string file_name = argv[1];

        std::ifstream file(file_name);

        nlohmann::json data = nlohmann::json::parse(file);
        std::string text = data["text"];
        int w = data["w"];
        int h = data["h"];
        int text_size = text.length();
        int w_spaces = w - text_size - 2;
        int left_spaces = ceil(w_spaces / 2.0);
        int right_spaces = floor(w_spaces / 2.0);
        int h_text_position = ceil(h / 2.0);

        int in_how_many_lines = ceil(double(text_size) / double(w-2));
        int how_many_chars_per_line = ceil(double(text_size) / double(in_how_many_lines));


        int total_space = (w -2) * (h-2);
        if (total_space < text_size) {
            std::cout << "given size will be never enough to print all that text" << std::endl;
            return 0;
        }
        std::cout << std::string(w, '#') << std::endl;
        if (in_how_many_lines <= 1) {
            for (int i = 0; i < h - 2; i++) {
                if (i == h_text_position - 2) {
                    std::cout << "#" << std::string(left_spaces, ' ') << text <<
                              std::string(right_spaces, ' ') << "#" << std::endl;
                } else {
                    std::cout << "#" << std::string(w - 2, ' ') << "#" << std::endl;
                }
            }
        }
        else {
            int upside_lines = ceil(((h-2)-in_how_many_lines)/ 2.0);
            int bottom_lines = floor(((h-2)-in_how_many_lines)/ 2.0);
            int substring_iteration = 0;
            for (int i = 0; i < h - 2; i++) {
                if (i < upside_lines or i > h - 2 - bottom_lines - 1) {
                    std::cout << "#" << std::string(w - 2, ' ') << "#" << std::endl;
                }
                else {
                    std::string my_str = text.substr(substring_iteration, how_many_chars_per_line);
                    int number_of_spaces = (w-2) - my_str.length();
                    int left_spaces_2 = ceil(double(number_of_spaces) / 2.0);
                    int right_spaces_2 = floor(double(number_of_spaces) / 2.0);
                    std::cout << "#" << std::string(left_spaces_2, ' ') <<
                    my_str << std::string(right_spaces_2, ' ') << "#" << std::endl;
                    substring_iteration += how_many_chars_per_line;
                }
            }

        }
        std::cout << std::string(w, '#') << std::endl;
        return 0;
    }
    catch(...){
        std::cout << "file must take one argument which is json file localization in shape "
                     "{w:SZEROKOSCRAMKI,h:WYSOKOSCRAMKI,text:TEKSTDOWPISANIAWRAMCE}, SZEROKOSC"
                     "  and WYSOKOSC must be an int and TEKST should be string"<< std::endl;
        return 0;
    }


}