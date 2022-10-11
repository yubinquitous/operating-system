#define PNUM 5					// Process 개수
#define PRINT_CYCLE 10000000	// Process가 정보를 출력하는 주기
#define TOTAL_COUNTER 500000000 // Process가 종료할 때 counter 값

#include "user.h"
#include "types.h"
#include "stat.h"

void sdebug_func(void)
{
	int n, pid;
	int waitpid;

	printf(1, "start sdebug command\n");

	for (n = 0; n < PNUM; n++) // 프로세스 개수만큼 수행
	{
		pid = fork();
		if (pid == 0) // 자식 프로세스
		{
			int start_tick = uptime(); // 프로세스 시작 시간
			weightset(n + 1);
			for (uint j = 0; j < TOTAL_COUNTER; j++) // counter 값만큼 수행
			{
				if (j == PRINT_CYCLE) // 프로세스 정보를 주기에 맞게 한번만 출력
				{
					int tick = (uptime() - start_tick) * 10; // 프로세스 시작 후 출력까지 걸린 시간
					printf(1, "PID: %d, WEIGHT: %d, TIMES: %d ms\n", getpid(), n + 1, tick);
				}
			}
			exit();
		}
		else if (pid < 0) // fork 실패
			break;
	}

	// if (n == PNUM)
	// {
	//	printf(1, "fork claimed to work %d times!\n", PNUM);
	// 	exit();
	// }

	for (; n > 0; n--)
	{
		if ((waitpid = wait()) < 0)
		{
			printf(1, "wait stopped early\n");
			exit();
		}
		printf(1, "PID: %d terminated\n", waitpid);
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
