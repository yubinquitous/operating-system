#define PNUM 5				   // Process 개수
#define PRINT_CYCLE 10000000   // Process가 정보를 출력하는 주기
#define TOTAL_COUNTER 50000000 // Process가 종료할 때 counter 값

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
			int start_time = uptime(); // 프로세스 시작 시간
			weightset(n + 1);
			for (uint j = 0; j < TOTAL_COUNTER; j++) // counter 값만큼 수행
			{
				if (j != 0 && j % PRINT_CYCLE == 0) // PRINT_CYCLE 마다 출력
				{
					int time = (uptime() - start_time) * 10; // 프로세스 정보 출력 시간 - 프로세스 시작 시간
					printf(1, "PID: %d, WEIGHT: %d, TIMES: %d ms\n", getpid(), n + 1, time);
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

