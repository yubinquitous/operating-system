#define SIZE 2048

int main(void)
{
    int msize = memsize();
    printf(1, "The process is using %dB\n", msize);

    char *tmp = (char *)malloc(SIZE * sizeof(char));

    printf(1, "Allocating more momory\n");
    msize = memsize();
    print(1, "The process is using %dB\n", msize);

    free(tmp);
    print(1, "Freeing memory\n");
    msize = memsize();
    print(1, "The process is using %dB\n", msize);

    exit();
}