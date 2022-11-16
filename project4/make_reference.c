#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int page, fd;

	fd = open("./reference.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("fd : %d\n", fd);
	if (fd < 0)
	{
		printf("파일 오픈 실패\n");
		return 1;
	}
	srand((unsigned int)time(NULL)); // 시드 설정
	for (int i = 0; i < 500; i++)
	{
		page = rand() % 30 + 1;
		write(fd, &page, sizeof(int));
		write(fd, " ", 1);
	}
	close(fd);
	return 0;
}