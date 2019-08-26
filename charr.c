#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t getln(char** buffer, FILE* stream);

int main()
{
    char* str = malloc(50);

    ssize_t strlen = getln(&str, stdin);

    printf("The content of the line is:\n");
    printf("%s\n", str);
    printf("Total number of characeters is: ");
    printf("%d\n", (int)strlen);

    free(str);
    str = NULL;
}

ssize_t getln(char** lineptr, FILE* stream)
{

    if (stream == NULL)
    {
        printf("Failed to read stream STOP...\n");
        return -1;
    }
  
    int buffersize = 32;

    // *lineptr might be NULL
    char* buffer = malloc(buffersize);

    int index = 0;
    int c = 0;

    while ((c = fgetc(stream)) && (c != EOF) && (c != '\n') && (c != '\r'))
    {
        buffer[index++] = (char)c;  // index gets increamented AFTERWARDS, can check index without overflow

        if (index ==  buffersize)
        {
            // double if it goes over the initial size
            buffersize *= 2;
      
            // realloc may displace the pointer, play safe here, also it should free the old buffer automatically
            char* newbuffer = realloc(buffer, buffersize);

            if (newbuffer == NULL)
            {
                printf("Failed to re-allocate memory STOP...\n");
                return -1;
            }
            else
            {
                buffer = newbuffer;
            }
        }
    }

    // add '\0' and re-allocate to save space
    buffer[index] = '\0';
    buffer = realloc(buffer, index + 1);

    *lineptr = buffer;

    return index;
}
