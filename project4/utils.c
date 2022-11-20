#include "page_replacement.h"

// 참조 문자열을 배열에 저장하는 함수
void get_page_reference(int *page_reference, t_reference *reference)
{
	for (int i = 0; i < REFERENCE_SIZE; i++)
		page_reference[i] = reference[i].page;
}

// 참조 문자열을 구조체 t_reference에 저장하는 함수
void get_reference_with_rb_bit(int fd, t_reference *reference)
{
	int stdin;

	stdin = dup(STDIN_FILENO); // stdin을 복사
	dup2(fd, STDIN_FILENO);	   // fd를 stdin으로 복사
	for (int i = 0; i < REFERENCE_SIZE; i++)
		scanf("%d(%c)\t", &reference[i].page, &reference[i].rw_bit);
	dup2(stdin, STDIN_FILENO); // stdin 복구
}

// 에러 메시지 출력 후 프로그램을 종료하는 함수
void exit_with_msg(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

// 알고리즘 정보를 출력하는 함수
void print_algorithm_start(char *algorithm_type, int n_frames, int fd)
{
	char buf[100] = {0};

	printf("\033[0;32m=============================%s algorithm=============================\n\033[0m", algorithm_type);
	dprintf(fd, "=============================%s algorithm=============================\n", algorithm_type);
	printf("%10s", "Page");
	dprintf(fd, "%10s", "Page");
	for (int i = 0; i < n_frames; i++)
	{
		sprintf(buf, "Frame[%d]", i);
		printf("%10s", buf);
		dprintf(fd, "%10s", buf);
	}
	printf("%10s\n", "Result");
	dprintf(fd, "%10s\n", "Result");
}

// 알고리즘 정보를 출력하는 함수 - 연결리스트
void print_algorithm_start_list(char *algorithm_type, int n_frames, int fd)
{
	printf("\033[0;32m=============================%s algorithm=============================\n\033[0m", algorithm_type);
	dprintf(fd, "=============================%s algorithm=============================\n", algorithm_type);
	printf("%10s", "Page");
	dprintf(fd, "%10s", "Page");
	printf("%10s", "Front");
	dprintf(fd, "%10s", "Front");
	for (int i = 1; i < n_frames - 1; i++)
	{
		printf("%10s", "->");
		dprintf(fd, "%10s", "->");
	}
	printf("%10s", "Rear");
	dprintf(fd, "%10s", "Rear");
	printf("%10s\n", "Result");
	dprintf(fd, "%10s\n", "Result");
}

// 프레임 배열을 출력하는 함수
void print_frame_array(int page, int *frame, int n_frames, char *result, int fd)
{
	// 참조값 출력
	printf("%10d", page);
	// 참조값 파일에 저장
	dprintf(fd, "%10d", page);
	for (int i = 0; i < n_frames; i++)
	{
		// 프레임값 출력
		printf("%10d", frame[i]);
		// 프레임값 파일에 저장
		dprintf(fd, "%10d", frame[i]);
	}
	printf("%10s\n", result);	   // 결과 (HIT, miss) 출력
	dprintf(fd, "%10s\n", result); // 결과 (HIT, miss) 파일에 저장
}

// 프레임 연결 리스트를 출력하는 함수
void print_frame_list(int page, t_frame *head, int n_frames, char *result, int fd)
{
	t_frame *tmp = head;
	int cnt = 0;

	// 참조값 출력
	printf("%10d", page);
	// 참조값 파일에 저장
	dprintf(fd, "%10d", page);
	while (tmp->next != NULL)
	{
		// 프레임값 출력
		printf("%10d", tmp->page);
		// 프레임값 파일에 저장
		dprintf(fd, "%10d", tmp->page);
		tmp = tmp->next;
		++cnt;
	}
	while (cnt < n_frames)
	{
		printf("%10d", 0);
		dprintf(fd, "%10d", 0);
		++cnt;
	}
	printf("%10s\n", result);
	dprintf(fd, "%10s\n", result);
}

// r_bit가 있는 프레임 배열을 출력하는 함수
void print_frame_with_r_bit(int page, t_frame_with_r_bit *frame, int n_frames, char *result, int fd)
{
	// 참조값 출력
	printf("%10d", page);
	// 참조값 파일에 저장
	dprintf(fd, "%10d", page);
	for (int i = 0; i < n_frames; i++)
	{
		// 프레임값과 r_bit 출력
		printf("%7d(%d)", frame[i].page, frame[i].r_bit);
		// 프레임값과 r_bit 파일에 저장
		dprintf(fd, "%7d(%d)", frame[i].page, frame[i].r_bit);
	}
	printf("%10s\n", result);	   // 결과 (HIT, miss) 출력
	dprintf(fd, "%10s\n", result); // 결과 (HIT, miss) 파일에 저장
}

// rw 비트가 있는 프레임 구조체 배열을 출력하는 함수
void print_frame_with_rw_bit(t_reference reference, t_frame_with_rw_bit *frame, int n_frames, char *result, int fd)
{
	// 참조값 출력
	printf("%7d(%c)", reference.page, reference.rw_bit);
	// 참조값 파일에 저장
	dprintf(fd, "%7d(%c)", reference.page, reference.rw_bit);
	for (int i = 0; i < n_frames; i++)
	{
		// 프레임값과 r_bit 출력
		printf("%4d(%d, %d)", frame[i].page, frame[i].r_bit, frame[i].w_bit);
		// 프레임값과 r_bit 파일에 저장
		dprintf(fd, "%4d(%d, %d)", frame[i].page, frame[i].r_bit, frame[i].w_bit);
	}
	printf("%10s\n", result);	   // 결과 (HIT, miss) 출력
	dprintf(fd, "%10s\n", result); // 결과 (HIT, miss) 파일에 저장
}

// page fault 횟수를 출력하는 함수
void print_result(char *algorithm_type, int page_fault, int fd)
{
	printf("\033[0;31m%s page fault: %d\n\n\033[0m", algorithm_type, page_fault);
	dprintf(fd, "%s page fault: %d\n\n", algorithm_type, page_fault);
}

// 프레임 배열을 초기화하는 함수
void init_frame(int *frame, int n_frames)
{
	for (int i = 0; i < n_frames; i++)
		frame[i] = 0;
}

// 프레임 연결 리스트 할당 해제하는 함수
void free_frame_list(t_frame *head)
{
	t_frame *tmp;

	while (head->next != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(head);
}

// 프레임 배열에서 hit인지 miss인지 확인하는 함수
char is_hit(int *frame, int n_frames, int page)
{
	for (int i = 0; i < n_frames; i++)
	{
		if (frame[i] == page)
			return 1;
	}
	return 0;
}