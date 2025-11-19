#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int 
main(int argc, char *argv[])
{

    if (argc < 2)
    {
        fprintf(2, "No arguments passed to xargs\n");
        exit(1);
    }

    char textBuffer[256];
    int index = 0;

    while ((read(0, &textBuffer[index], 1)) > 0)
    {

        if (textBuffer[index] == '\n')
        {
            // while reading if we hit the end aka a '\n' turn into a \0 for C compiler to process eof
            textBuffer[index] = '\0';

            // reaching the end of the file means we have read in the output from whatver is being piped
            // now we need to prepare the arguments for exec

            char *argsToNextCommand[MAXARG];
            int argIndex = 0;

            for (int i = 1; i < argc; i++)
            {
                argsToNextCommand[argIndex++] = argv[i];
            }

            argsToNextCommand[argIndex++] = textBuffer;
            argsToNextCommand[argIndex] = 0;

            // must fork to run exec
            if (fork() == 0)
            {
                exec(argv[1], argsToNextCommand); // executes the command found in argv[1] with arguments argsToNextCommand which includes the piped input
                fprintf(2, "exec failed\n");
                exit(1);
            }
            wait(0); // sleep time until child process is done

            index = 0;
        }
        else
        {
            index++;
        }
    }
    exit(0);
}
