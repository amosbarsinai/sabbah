#include "token/token.hpp"
#include "token/operator.hpp"
#include <string>
#include <vector>

char Token::Tokenizer::peek() {
    if (index >= src.size()) {
        return '\0';
    }
    return src[index];
}

char Token::Tokenizer::consume() {
    if (index >= src.size()) {
        return '\0';
    }
    char current = src[index++];
    if (current == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return current;
}

int Token::Tokenizer::skipwhitespace() {
    int skipped = 0;
    while (true) {
        char current = peek();
        if (isspace(current)) {
            consume();
            skipped++;
        } else {
            break;
        }
    }
    return skipped;
}

std::vector<Token::Token> Token::Tokenizer::tokenize() {
    std::vector<Token> tokens;
    while (index < src.size()) {
        skipwhitespace();
        int token_line = line;
        int token_column = column;
        char current = peek();

        if (isalpha(current)) {
            std::string lexeme;
            while (isalnum(peek())) {
                lexeme += consume();
            }
            if (lexeme == "def") {
                tokens.push_back(Token(TokenType::KW_DEF, lexeme, token_line, token_column));
            } else if (lexeme == "return") {
                tokens.push_back(Token(TokenType::KW_RETURN, lexeme, token_line, token_column));
            } else {
                tokens.push_back(Token(TokenType::IDENTIFIER, lexeme, token_line, token_column));
            }
        } else if (isdigit(current)) {
            std::string lexeme;
            while (isdigit(peek())) {
                lexeme += consume();
            }
            tokens.push_back(Token(TokenType::NUMBER, lexeme, token_line, token_column));
        } else if (current == '(') {
            consume();
            tokens.push_back(Token(Token(TokenType::PAREN_OPEN, "(", token_line, token_column)));
        } else if (current == ')') {
            consume();
            tokens.push_back(Token(Token(TokenType::PAREN_CLOSE, ")", token_line, token_column)));
        } else if (current == '+') {
            consume();
            tokens.push_back(OperatorToken(OperatorType::SUM, "+", token_line, token_column));
        } else if (current == '-') {
            consume();
            tokens.push_back(OperatorToken(OperatorType::SUB, "-", token_line, token_column));
        } else if (current == '*') {
            consume();
            tokens.push_back(OperatorToken(OperatorType::MUL, "*", token_line, token_column));
        } else if (current == '/') {
            consume();
            tokens.push_back(OperatorToken(OperatorType::DIV, "/", token_line, token_column));
        } else if (current == '^') {
            consume();
            tokens.push_back(OperatorToken(OperatorType::POW, "^", token_line, token_column));
        } else if (current == '%') {
            consume();
            tokens.push_back(OperatorToken(OperatorType::MOD, "%", token_line, token_column));
        } else if (current == '>') {
            consume();
            if (peek() == '=') {
                consume();
                tokens.push_back(OperatorToken(OperatorType::GTE, ">=", token_line, token_column));
            } else {
                tokens.push_back(OperatorToken(OperatorType::GT, ">", token_line, token_column));
            }
        } else if (current == '<') {
            consume();
            if (peek() == '=') {
                consume();
                tokens.push_back(OperatorToken(OperatorType::LTE, "<=", token_line, token_column));
            } else {
                tokens.push_back(OperatorToken(OperatorType::LT, "<", token_line, token_column));
            }
        } else if (current == ':') {
            consume();
            tokens.push_back(Token(TokenType::COLON, ":", token_line, token_column));
        } else if (current == ',') {
            consume();
            tokens.push_back(Token(TokenType::COMMA, ",", token_line, token_column));
        } else if (current == '\0') {
            break;
        } else {
            if (current == '=') {
                consume();
                if (peek() == '=') {
                    consume();
                    tokens.push_back(OperatorToken(OperatorType::EQ, "==", token_line, token_column));
                    continue;
                }
            } else if (current == '!') {
                consume();
                if (peek() == '=') {
                    consume();
                    tokens.push_back(OperatorToken(OperatorType::NEQ, "!=", token_line, token_column));
                    continue;
                }
            } else {
                // Handle unknown character
                std::string lexeme(1, consume());
                tokens.emplace_back(TokenType::UNKNOWN, lexeme, token_line, token_column);
            }
        }
    }
    return tokens;
}

// For debug purposes
std::string& Token::Token::name() {
    static std::string unknown = "UNKNOWN";
    static std::string tok_eof = "TOK_EOF";
    static std::string tok_whitespace = "TOK_WHITESPACE";
    static std::string kw_def = "KW_DEF";
    static std::string kw_return = "KW_RETURN";
    static std::string identifier = "IDENTIFIER";
    static std::string number = "NUMBER";
    static std::string operator_tok = "OPERATOR";
    static std::string colon = "COLON";
    static std::string paren_open = "PAREN_OPEN";
    static std::string paren_close = "PAREN_CLOSE";
    static std::string comma = "COMMA";

    switch (type) {
        case TokenType::UNKNOWN: return unknown;
        case TokenType::TOK_EOF: return tok_eof;
        case TokenType::TOK_WHITESPACE: return tok_whitespace;
        case TokenType::KW_DEF: return kw_def;
        case TokenType::KW_RETURN: return kw_return;
        case TokenType::IDENTIFIER: return identifier;
        case TokenType::NUMBER: return number;
        case TokenType::OPERATOR: return operator_tok;
        case TokenType::COLON: return colon;
        case TokenType::PAREN_OPEN: return paren_open;
        case TokenType::PAREN_CLOSE: return paren_close;
        case TokenType::COMMA: return comma;
        default: return unknown;
    }
}
