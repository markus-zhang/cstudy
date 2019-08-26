#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int peek(FILE* infp);

int main(int argc, char* argv[])
{
    if (argc < 2 || strlen(argv[1]) == 0)
    {
        printf("Usage: rmcomment -<filename>\n");
        return 1;
    }

    FILE* inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        printf("Failed to read file %s\n", argv[1]);
        return 2;
    }

    int ch = 0;
    int bufferSize = 4096;
    int bufferIndex = 0;
    bool inString = false;
    bool inChar = false;
    bool startLineComment = false;
    bool startBlockComment = false;

    char* buffer = malloc(bufferSize);

    while ((ch = fgetc(inptr)) && (ch != EOF))
    {
        if (inString && ch != '"')
        {
            // easy part
            buffer[bufferIndex] = ch;
            bufferIndex += 1;
            continue;
        }

        if (ch == '\n')
        {
            // if we already set startLineComment to true
            printf("Line comment ends\n");
            startLineComment = false;
        }

        if (ch == '*')
        {
            if (peek(inptr) == '/')
            {
                startBlockComment = false;
                // skip these two chars
                fgetc(inptr);
                continue;
            }
        }

        if (ch == '\'')
        {
            inChar = !inChar;
        }

        if ((ch == '"') && !startLineComment && !startBlockComment && !inChar)
        {
            inString = !inString;
        }
        else
        {
            if (!inString)
            {
                // do we reach '/'?
                if (ch == '/')
                {
                    if (peek(inptr) == '/')
                    {
                        // Comment starts here if not in string
                        printf("Line comment starts\n");
                        startLineComment = true;
                    }
                    else
                    {
                        if (peek(inptr) == '*')
                        {
                            // Block comment starts
                            printf("Block comment starts\n");
                            startBlockComment = true;
                        }
                    }
                }
            }
        }

        // The above rules say that if not in string and comments do not start
        if (inString || (!startLineComment && !startBlockComment))
        {
            buffer[bufferIndex] = ch;
            bufferIndex += 1;
        }
    }

    buffer[bufferIndex] = '\0';

    printf("%s\n", buffer);

    fclose(inptr);
    return 0;
}

int peek(FILE* inptr)
{
    int ch = fgetc(inptr);
    ungetc(ch, inptr);

    return ch;
}
