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
		if (pid == 0) // 자식 프로세스
		{
			int start_tick = uptime(); // 프로세스 시작 시간
			weightset(n + 1);

			for (int j = 0; j < TOTAL_COUNTER; j++) // counter 값만큼 수행
			{
				if (j == PRINT_CYCLE) // 프로세스 정보를 주기에 맞게 한번만 출력
				{
					int tick = (uptime() - start_tick) * 10; // 프로세스 시작 후 출력까지 걸린 시간
					printf(1, "PID: %d, WEIGHT: %d, TIMES: %d ms\n", getpid(), n + 1, tick);
				}
			}
			printf(1, "PID: %d terminated\n", getpid());
			exit();
		}
		else if (pid < 0) // fork 실패
			break;
	}

	for (; n > 0; n--) // 생성된 프로세스의 수만큼 wait()
	{
		if (wait() < 0) // 반복문이 끝나기 전인데 더 이상 기다릴 자식 프로세스가 없을 경우
		{
			printf(1, "wait stopped early\n"); // 에러문 출력 후 exit을 통해 종료
			exit();
		}
	}

	if (wait() != -1) // 생성된 프로세스의 수만큼 wait를 수행한 후에도 더 기다릴 자식 프로세스가 있을 경우
	{
		printf(1, "wait got too many\n"); // 에러문 출력 후 exit을 통해 종료
		exit();
	}

	printf(1, "end of sdebug command\n");
}

int main(void)
{
	sdebug_func();
	exit();
}