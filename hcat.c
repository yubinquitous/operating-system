#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
int nlines;

void hcat(int fd)
{
  int n = 0;
  int i = 0;
  int cnt = 0;

  while ((cnt < nlines) && ((n = read(fd, buf, sizeof(buf))) > 0))
  {
    for (i = 0; i < n; i++)
    {
      if (buf[i] == '\n')
      {
        ++cnt;
        if (cnt == nlines)
			break;
      }
    }
	++i;
    if (write(1, buf, i) != i)
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
