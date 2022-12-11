#ifndef __LEX_H
#define __LEX_H 1

#include <stdint.h>
#include <vector>
#include <string>

#define ___AST_DEF_NODE(node) node,

#define __AST_NODE_TYPES                                            \
                ___AST_DEF_NODE(AST_NODE_Plus)                      \
                ___AST_DEF_NODE(AST_NODE_Minus)                     \
                ___AST_DEF_NODE(AST_NODE_Asterisk)                  \
                ___AST_DEF_NODE(AST_NODE_Slash)                     \
                ___AST_DEF_NODE(AST_NODE_Percent)                   \
                ___AST_DEF_NODE(AST_NODE_Dot)                       \
                ___AST_DEF_NODE(AST_NODE_Colon)                     \
                ___AST_DEF_NODE(AST_NODE_GreaterThan)               \
                ___AST_DEF_NODE(AST_NODE_LessThan)                  \
                ___AST_DEF_NODE(AST_NODE_Equal)                     \
                ___AST_DEF_NODE(AST_NODE_XOR)                       \
                ___AST_DEF_NODE(AST_NODE_NOR)                       \
                ___AST_DEF_NODE(AST_NODE_AND)                       \
                ___AST_DEF_NODE(AST_NODE_NOT)                       \
                ___AST_DEF_NODE(AST_NODE_Comment)                   \
                ___AST_DEF_NODE(AST_NODE_MultiLineComment)          \
                ___AST_DEF_NODE(AST_NODE_PreProcessorStatement)     \
                ___AST_DEF_NODE(AST_NODE_Keyword)                   \
                ___AST_DEF_NODE(AST_NODE_String)                    \
                ___AST_DEF_NODE(AST_NODE_Character)                 \
                ___AST_DEF_NODE(AST_NODE_Whitespace)                \
                ___AST_DEF_NODE(AST_NODE_Reference)                 \
                ___AST_DEF_NODE(AST_NODE_Identifier)                \
                ___AST_DEF_NODE(AST_NODE_Semicolon)                 \
                ___AST_DEF_NODE(AST_NODE_ParenthesisRight)          \
                ___AST_DEF_NODE(AST_NODE_ParenthesisLeft)           \
                ___AST_DEF_NODE(AST_NODE_BracketRight)              \
                ___AST_DEF_NODE(AST_NODE_BracketLeft)               \
                ___AST_DEF_NODE(AST_NODE_CurlyRight)                \
                ___AST_DEF_NODE(AST_NODE_CurlyLeft)                 \
                ___AST_DEF_NODE(AST_NODE_None)

enum AST_Node_Type{
    __AST_NODE_TYPES
    #undef ___AST_DEF_NODE
};

struct AST_Node{
    AST_Node_Type Type = AST_NODE_None;
    std::string Data;
    std::vector<AST_Node*> Nested;
};

struct AbstractSyntaxTree{
    std::vector<AST_Node> Nodes;
};

AbstractSyntaxTree ReadAST(const char* fileContents);

struct Lexer
{
    Lexer( const char* filePath );

    AbstractSyntaxTree Lex();

private:

    char* fileContents ;
    size_t fileContentsSize ;
};

#endif