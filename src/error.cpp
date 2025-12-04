#include "error/error.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sstream>

void error(const std::string& message, std::string filename, std::string& source, int line, int column, int length) {
    std::cout << BOLD << RED;
    std::cout << "error" << RESET << RED << " at (" << line << ':' << column << '-' << column - 1 + length << "):" << RESET;
    std::cout << std::endl << "          " << message << std::endl;
    std::cout << std::endl;

    // Get the maximum size of the string line number for formatting (minimum of linenum + 2 and the total number of lines)
    int total_line_nums = std::count(source.begin(), source.end(), '\n') + 1;
    int line_num_size = std::to_string(std::min(line + 2, total_line_nums)).size();

    winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int term_width = w.ws_col == 0 ? 80 : w.ws_col;
    for (int i = 0; i < line_num_size + 2; i++) std::cout << H;
    std::cout << MD;
    for (int i = 0; i < term_width - line_num_size - 3; i++) std::cout << H;
    std::cout << std::endl;
    std::cout << ' ' << std::string(line_num_size, ' ') << ' ' << V << "    " << BOLD << "File: " << RESET << filename << std::endl;
    for (int i = 0; i < line_num_size + 2; i++) std::cout << H;
    std::cout << MM;
    for (int i = 0; i < term_width - line_num_size - 3; i++) std::cout << H;
    std::cout << std::endl;
    
    // Get only the relevant lines from the source code - from two lines before to two lines after
    int start_line = std::max(1, line - 2);
    int end_line = std::min(total_line_nums, line + 2);
    
    std::vector<std::string> lines;
    std::stringstream ss(source);
    std::string current_line;
    int current_line_num = 1;
    
    while (std::getline(ss, current_line)) {
        if (current_line_num >= start_line && current_line_num <= end_line) {
            lines.push_back(current_line);
        }
        current_line_num++;
    }

    if (start_line > 1) {
        std::cout << std::string(line_num_size + 2, ' ') << V << " ..." << std::endl;
    }

    for (size_t i = 0; i < lines.size(); i++) {
        int display_line_num = start_line + i;
        std::cout << ' ' << std::string(line_num_size - std::to_string(display_line_num).size(), ' ') << display_line_num << ' ' << V << " " << lines[i] << std::endl;
        if (display_line_num == line) {
            std::cout << std::string(line_num_size + 2, ' ') << V << " " 
                      << std::string(column - 1, ' ') 
                      << BOLD << RED << std::string(length, '^') << RESET << std::endl;
        }
    }
    if (end_line < total_line_nums) {
        std::cout << std::string(line_num_size + 2, ' ') << V << " ..." << std::endl;
    }
    for (int i = 0; i < line_num_size + 2; i++) std::cout << H;
    std::cout << MU;
    for (int i = 0; i < term_width - line_num_size - 3; i++) std::cout << H;
    std::cout << std::endl;
}
