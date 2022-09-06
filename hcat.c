#include "types.h"
#include "stat.h"
#include "user.h"

char c;
int nlines;

void hcat(int fd)
{
  int n = 0;
  int cnt = 0;

  while ((cnt < nlines) && ((n = read(fd, &c, 1)) > 0))
  {
    if (c == '\n')
      ++cnt;
    if (write(1, &c, 1) != 1)
    {
      printf(1, "hcat: write error\n");
      exit();
    }
  }
  if (n < 0)
  {
    printf(1, "cat: read error\n");
    exit();
  }
}

int main(int argc, char *argv[])
{
  int fd;

  if ((argc != 2 && argc != 3) || !argv[1])
  {
    printf(1, "usage: hcat line file_name\n");
    exit();
  }

  nlines = atoi(argv[1]);
  if (!argv[2])
    fd = 0;
  else if ((fd = open(argv[2], 0)) < 0) // O_RDONLY가 0임
  {
    printf(1, "hcat: cannot open %s\n", argv[2]);
    exit();
  }

  hcat(fd);
  if (fd)
    close(fd);
  exit();
}
