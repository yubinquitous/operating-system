#define PNUM 5					// Process 개수
#define PRINT_CYCLE 10000000	// Process가 정보를 출력하는 주기
#define TOTAL_COUNTER 500000000 // Process가 종료할 때 counter 값

#include "user.h"
#include "proc.h"
#include "stat.h"

void sdebug_func(void)
{
	int n, pid;

	printf(1, "start sdebug command\n");

	int i = 0;
	for (i = 0; i < PNUM; i++) // 프로세스 개수만큼 수행
	{
		pid = fork();
		if (pid == 0) // 자식 프로세스
		{
			int start_time = uptime();							   // 프로세스 시작 시간
			for (unsigned long long j = 0; j < TOTAL_COUNTER; j++) // counter 값만큼 수행
			{
				if (j % PRINT_CYCLE == 0) // PRINT_CYCLE 마다 출력
				{
					struct proc *p = myproc();
					int time = (uptime() - start_time) * 10; // 프로세스 정보 출력 시간 - 프로세스 시작 시간
					printf(1, "PID: %d, WEIGHT: %d, TIMES: %d ms\n", p->pid, p->weight, time);
				}
			}
			exit();
		}
		else if (pid < 0) // fork 실패
			break;
	}

	if (i = PNUM)
	{
		printf(1, "fork claimed to work PNUM times!\n", PNUM);
		exit();
	}

	for (; i > 0; i--)
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