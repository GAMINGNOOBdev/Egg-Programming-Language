#include "lex.h"
#include <stdio.h>
#include <malloc.h>
#include "keywords.h"
#include <cstring>
#include "split.h"

static uint8_t cmpStr( const char * str1 , const char * str2 , const size_t & length ) {
    for ( size_t i = 0 ; i < length ; i ++ ) {
        if ( str1[i] != str2[i] ) {
            return 0;
        }
    }
    return 1;
}

Lexer::Lexer( const char* filePath )
{
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Couldn't find the file \"%s\"!\n", filePath);
        exit(-1);
    }

    fseek(file, 0, SEEK_END);
    this->fileContentsSize = ftell(file);
    rewind(file);

    this->fileContents = (char*)malloc(this->fileContentsSize);
    fread(&fileContents[0], 1, this->fileContentsSize, file);
    fclose(file);
}

AbstractSyntaxTree Lexer::Lex()
{
    AbstractSyntaxTree result;
    const char* contents = (const char*)fileContents;
    const std::vector<char*> lines = strsplit( contents, '\n' );
    const std::string fileStr = contents;
    
    size_t fileIndex = 0;

    size_t multilineCommentStart = 0;
    size_t multilineCommentEnd = 0;

    AST_Node node;

    bool commented = false;
    bool multilineComment = false;

    for ( const char* line : lines )
    {
        const size_t lineSize = strlen(line);
        size_t lineIndex = 0;
        const std::vector<char*> words = strsplit(line,' ');

        for ( const char* word : words )
        {
            const size_t wordLength = strlen(word);

            if (wordLength > 2)
            {
                if ( word[0] == '/' && word[1] == '*' )
                {
                    multilineCommentStart = fileIndex;
                    printf("MULTILINE COMMENT START\n");
                    multilineComment = true;
                }

                if ( word[0] == '*' && word[1] == '/' )
                {
                    multilineCommentEnd = fileIndex + 3;
                    printf("MULTILINE COMMENT END\n");
                    multilineComment = false;
                    node.Data = fileStr.substr(multilineCommentStart, multilineCommentEnd-multilineCommentStart);
                    node.Type = AST_NODE_MultiLineComment;
                    result.Nodes.push_back(node);
                    continue;
                }
            }
            if (wordLength > 1) {
                if (cmpStr(word, "//", 2)) {
                    commented = true;
                }
            }

            if ( !commented && !multilineComment ) {
                for (size_t kwIdx = 0; kwIdx < KW_ALL_MAX_AMOUNT; kwIdx++)
                {
                    if (wordLength == strlen(All_Keywords[kwIdx]))
                    {
                        if ( cmpStr(word, All_Keywords[kwIdx], strlen(All_Keywords[kwIdx])) )
                        {
                            node.Data = word;
                            node.Type = AST_NODE_Keyword;
                            result.Nodes.push_back(node);
                            break;
                        }
                    }
                }
            }


            lineIndex += strlen(word)+1;
        }
        commented = false;

        fileIndex += lineIndex + 1;
    }
    
    return result;
}