#define PNUM 5					// Process 개수
#define PRINT_CYCLE 10000000	// Process가 정보를 출력하는 주기
#define TOTAL_COUNTER 500000000 // Process가 종료할 때 counter 값

#include "user.h"
#include "types.h"
#include "stat.h"

void sdebug_func(void)
{
	int n, pid;

	printf(1, "start sdebug command\n");

	for (n = 0; n < PNUM; n++) // 프로세스 개수만큼 수행
	{
		pid = fork();
		if (pid < 0)
			break;
		if (pid == 0) // 자식 프로세스
		{
			int counter = -1;
			int first = 1;
			int print_counter = PRINT_CYCLE;

			weightset(n + 1);
			int start_tick = uptime();

			while (++counter < TOTAL_COUNTER)
			{
				--print_counter;
				if (print_counter == 0)
				{
					if (first)
					{
						int end_tick = uptime();
						printf(1, "PID: %d, WEIGHT: %d, TIMES: %d ms\n", getpid(), n + 1, (end_tick - start_tick) * 10);
						first = 0;
					}
					print_counter = PRINT_CYCLE;
				}
			}

			printf(1, "PID: %d terminated\n", getpid());
			exit();
		}
	}

	// if (n == PNUM)
	// {
	//	printf(1, "fork claimed to work %d times!\n", PNUM);
	// 	exit();
	// }

	for (; n > 0; n--)
	{
		if (wait() < 0)
		{
			printf(1, "wait stopped early\n");
			exit();
		}
	}

	if (wait() != -1)
	{
		printf(1, "wait got too many\n");
		exit();
	}

	printf(1, "end of sdebug command\n");
}

int main(void)
{
	sdebug_func();
	exit();
}
