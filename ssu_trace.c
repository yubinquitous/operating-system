#include "user.h"

int main(int argc, char *argv[])
{
    // int pid, wpid;
    int mask;

    if (argc < 2)
    {
        printf(2, "Usage: %s <mask> <command>\n", argv[0]);
        exit();
    }

    if ((mask = atoi(argv[1])) < 0 || mask > 0x7FFFFFFF)
    {
        printf(2, "Invalid mask\n");
        exit();
    }
    trace(mask);
}
