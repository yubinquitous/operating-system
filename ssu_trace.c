#include "user.h"

int main(int argc, char *argv[])
{
    int pid, wpid;

    if (argc < 2)
    {
        printf(2, "Usage: %s <mask> <command>\n", argv[0]);
        exit();
    }

    if (argc == 2)
    {
        trace(atoi(argv[1]));
        exit();
    }
    else if (argc == 3)
    {
        trace(atoi(argv[1]));

        pid = fork();
        if (pid < 0)
        {
            printf(1, "init: fork failed\n");
            exit();
        }
        if (pid == 0)
        {
            exec(argv[2], argv + 2);
            printf(1, "init: exec sh failed\n");
            exit();
        }
        while ((wpid = wait()) >= 0 && wpid != pid)
            printf(1, "zombie!\n");
    }
    exit();
}
