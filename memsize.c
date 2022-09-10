#include "types.h"
#include "proc.h"
#include "defs.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"

int memsize(void)
{
    uint size;
    struct proc *p;

    // 기능 구현
    p = myproc();
    size = p->sz;
    printf(1, "size: %d\n", size);

    return size;
}