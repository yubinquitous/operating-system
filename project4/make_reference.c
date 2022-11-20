#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int page, fd;
	char rb_status;
	char buf[20] = {0};

	fd = open("./reference.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("파일 오픈 실패\n");
		return 1;
	}
	srand((unsigned int)time(NULL)); // 시드 설정
	for (int i = 0; i < 500; i++)
	{
		page = rand() % 30 + 1;
		rb_status = rand() % 2 ? 'R' : 'W';
		sprintf(buf, "%d(%c) ", page, rb_status);
		write(fd, buf, strlen(buf));
	}
	close(fd);
	return 0;
}