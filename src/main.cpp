#include "lex.h"
#include <stdio.h>
#include <malloc.h>

int main(const int argc, const char** argv)
{
    char* filepath;
    if (argc < 2) 
    {
        printf("Error: you must at least specify one filepath!\n");
        return -1;
    }
    //char* filepath = 0;
    
    /*for (int i = 0; i < argc; i++)
    {
        if (argv[i] == "-f" && i < argc-1)
        {
            filepath = (char*)argv[i+1];
        }
    }*/
    
    filepath = (char*)argv[argc-1];

    Lexer* lexer = new Lexer(filepath);
    AbstractSyntaxTree ast = lexer->Lex();

    /*FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Couldn't find the file \"%s\"!\n", filepath);
        return -1;
    }
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* fileContents = (char*)malloc(fileSize);
    fread(&fileContents[0], 1, fileSize, file);
    fclose(file);

    AbstractSyntaxTree ast = ReadAST((const char*)fileContents);*/

    for (AST_Node node : ast.Nodes)
    {
        printf("\"%s\"\tType: ", node.Data.c_str());
        switch (node.Type)
        {
            #define ___AST_DEF_NODE(node) case node: printf("%s\n",#node); break;
            __AST_NODE_TYPES
            #undef ___AST_DEF_NODE
        }
    }
    scanf("%c");

    return 0;
}