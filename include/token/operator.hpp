#pragma once

#include "token/token.hpp"

namespace Token {

enum class OperatorType {
    SUM,
    SUB,
    MUL,
    DIV,
    POW,
    MOD,
    EQ,
    NEQ,
    GT,
    LT,
    GTE,
    LTE
};

class OperatorToken : public Token {
    public:
        OperatorType operator_type;

        OperatorToken(
            OperatorType operator_type,
            const std::string& lexeme,
            int line,
            int column
        ):
        Token(TokenType::OPERATOR, lexeme, line, column),
        operator_type(operator_type)
        {}
};

} // namespace Token
