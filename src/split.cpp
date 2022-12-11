#include "split.h"
#include <malloc.h>

std::vector<char*> strsplit( const char* str, char split )
{
    uint64_t numResults = 0;
    for (int i = 0; str[i]; i++)
    {
        if (str[i] == split && i != 0)
        {
            numResults++;
        }
    }
    std::vector<char*> result;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == split) { continue; }
        char* currentChar = (char*)&str[i];
        size_t strsize = 0;
        
        for (int j = 0; currentChar[j]; j++)
        {
            if (currentChar[j] == split || !currentChar[j]) { break; }
            strsize++;
        }
        
        char* tmpres = (char*)malloc(strsize+1);
        for (int j = 0; currentChar[j]; j++)
        {
            if (currentChar[j] == split || !currentChar[j] ) { tmpres[j] = 0; break; }
            tmpres[j] = currentChar[j];
            i++;
        }
        
        tmpres[strsize] = 0;
        char* resultingString = (char*)malloc(strsize+1);
        
        for (int j = 0; j < strsize+1; j++)
        {
            resultingString[j] = tmpres[j];
        }

        result.push_back(resultingString);
    }


    return result;
}