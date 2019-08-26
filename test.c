
        if (ch == '*')
        {
            if (peek(inptr) == '/')
            {
                startBlockComment = false;
            }
        }

        if ((ch == '"') && !startLineComment)
        {
            /*
             Commented out // "Yes we are"
                    */
            printf("/* Here is a block comment */");
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
