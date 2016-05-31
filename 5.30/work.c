#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//@text is the original text
//@openSymbol, closeSymbol are the tags to find
//@start, end are the addresses found
void getContent(char* text, char* openSymbol, char* closeSymbol,
                char** start, char** end) {
    *start = *end = NULL; //initialize to null

    //find open symbol
    int openLength = strlen(openSymbol);
    char* first = strstr(text, openSymbol);
    if(first == NULL) return;


    //find close symbol
    first += openLength;
    char* second = strstr(first, closeSymbol);
    if(second == NULL) return;

    //save
    *start = first;
    *end = second;
}

int main() {

    FILE* file = fopen("a.htm", "rb");
    if(file == NULL) {
        puts("Failed to open the file \"a.htm\"");
        exit(0);
    }

    char line[1000];
    //the title symbol
    char openSymbol[] = "<title>", closeSymbol[] = "</title>";

    char* start = NULL, *end = NULL; //to save the title address
    int haveTitle = 0, lineNumber = 0; //make for the title
    while(fgets(line, 1000, file) != NULL) {
        ++lineNumber;

        //try to get the title content
        getContent(line, openSymbol, closeSymbol, &start, &end);

        if(start != NULL && end != NULL) {
            haveTitle = 1; // ok, found the title
            break;
        }
    }

    if(!haveTitle) {
        puts("\"a.htm\" has no title");
    } else {
        char title[1000];
        int idx = 0, digits = 0, alphas = 0;
        for(char* p = start; p != end; ++p) {
            title[idx++] = *p;   //copy the title content
            if(isdigit(*p)) ++digits;  //digit
            if(isalpha(*p)) ++alphas;  //alphabet
        }

        printf("a.htm网页的标题是: %s\n", title);
        printf("标题在文件a.htm网页的第几行: %d\n", lineNumber);
        printf("标题中数字字符的个数: %d\n", digits);
        printf("标题中字母字符的个数: %d\n", alphas);
    }

    fclose(file);

    return 0;
}
