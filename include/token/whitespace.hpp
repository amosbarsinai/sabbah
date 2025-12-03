#pragma once

#include "token/operator.hpp"

namespace Token {

class WhitespaceToken : public Token {
    public:
        int size;
        WhitespaceToken(
            int line,
            int column,
            int size
        ):
        Token(TokenType::TOK_WHITESPACE, nullptr, line, column),
        size(size)
        {}
};

} // namespace Token
