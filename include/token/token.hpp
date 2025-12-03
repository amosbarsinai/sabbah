#pragma once

#include <string>
#include <vector>

namespace Token {

enum class TokenType {
    UNKNOWN,

    TOK_EOF,
    TOK_WHITESPACE,

    // Keywords
    KW_DEF,
    KW_RETURN,

    // Identifiers and literals
    IDENTIFIER,
    NUMBER,

    // Operators
    OPERATOR,

    // Punctuation
    COLON,
    PAREN_OPEN,
    PAREN_CLOSE,
    COMMA

};

class Token {
    public:
        TokenType type;
        std::string lexeme;
        int line;
        int column;

        Token(
            TokenType type,
            const std::string& lexeme,
            int line,
            int column
        ):
        type(type),
        lexeme(lexeme),
        line(line),
        column(column)
        {}
    public:
        // For debug purposes
        std::string&  name();
};

class Tokenizer {
    public:
        Tokenizer(std::string& source): src(source) {}
        std::vector<Token> tokenize();
    private:
        char            peek();
        char         consume();
        int   skipwhitespace();
        size_t       index = 0;
        int           line = 1;
        int         column = 1;
        std::string&       src;
};

} // namespace Token
