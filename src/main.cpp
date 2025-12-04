#include "token/token.hpp"
#include "error/error.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

int main() {
    // Open "test.sbb" and tokenize it
    std::ifstream file("test.sbb");
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
//     // Readlines and stitch
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
//     Token::Tokenizer tokenizer(content);
//     auto tokens = tokenizer.tokenize();
//     for (Token::Token& token : tokens) {
//         std::cout << "Token: " << token.name()
//                   << " Lexeme: '" << token.lexeme << "'"
//                   << " Line: " << token.line
//                   << " Column: " << token.column << std::endl;
//     }
//
    // return 0;
    error("cqnrouuqiwbcriuqiwbcriqwcbruqwcrqwrc", "ubqe.sbb", content, 62, 8, 2);
    return 0;
}