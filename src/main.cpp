#include "lex.h"
#include <stdio.h>
#include <malloc.h>

int main(const int argc, const char** argv) {
    char* filepath = nullptr;
    if (argc < 2)  {
        printf("Error: you must at least specify one filepath!\n");
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        if (cmpStr(argv[i],"-f" , 2) && i <= argc-1)
        {
            filepath = (char*)argv[i+1];
            break;
        }
    }
    
    if (filepath == nullptr) {
        printf("Error: no filepath specified, specify with the flag \"-f <filename>\"\n");
        return -1;
    }

    Lexer* lexer = new Lexer(filepath);
    AbstractSyntaxTree ast = lexer->Lex();

    for (AST_Node node : ast.Nodes) {
        printf("\"%s\"\tType: ", node.Data.c_str());
        switch (node.Type) {
            #define ___AST_DEF_NODE(node) case node: printf("%s\n",#node); break;
            __AST_NODE_TYPES
            #undef ___AST_DEF_NODE
        }
    }
    scanf("%c");

    return 0;
}