#include "page_replacement.h"

// 참조 문자열을 생성하는 함수
void set_reference(int fd, t_reference *reference, int input_method)
{
	if (input_method == 1) // 랜덤하게 생성
	{
		srand((unsigned int)time(NULL)); // 시드 설정
		for (int i = 0; i < REFERENCE_SIZE; i++)
		{
			reference[i].page = rand() % MAX_FRAME + 1;	  // 1 ~ 30
			reference[i].rw_bit = rand() % 2 ? 'R' : 'W'; // R or W
			printf("%d(%c) ", reference[i].page, reference[i].rw_bit);
			dprintf(fd, "%d(%c) ", reference[i].page, reference[i].rw_bit);
		}
		printf("\n");
		dprintf(fd, "\n");
	}
	else // 사용자 생성 파일 오픈
	{
		char file_name[100] = {0};					   // 파일 이름
		printf("사용자 생성 파일을 입력하시오.\n>> "); // 사용자 생성 파일 이름 입력
		scanf("%s", file_name);
		int fd = open(file_name, O_RDONLY);
		if (fd < 0)
			exit_with_msg("파일 오픈 실패");
		get_reference_with_rb_bit(fd, reference); // 파일에서 참조 문자열 읽어오기
		close(fd);
	}
}

// 입력받은 알고리즘을 수행하는 함수
void simulate_algorithm(int n_frames, t_reference *reference, int algorithm_type, int fd)
{
	if (algorithm_type == ESC)
	{
		simulate_esc(n_frames, reference, fd);
		return;
	}

	int page_reference[REFERENCE_SIZE] = {0};
	get_page_reference(page_reference, reference); // 참조 문자열에서 페이지 번호만 추출
	if (algorithm_type == OPTIMAL)
		simulate_optimal(n_frames, page_reference, fd);
	else if (algorithm_type == FIFO)
		simulate_fifo(n_frames, page_reference, fd);
	else if (algorithm_type == LIFO)
		simulate_lifo(n_frames, page_reference, fd);
	else if (algorithm_type == LRU)
		simulate_lru(n_frames, page_reference, fd);
	else if (algorithm_type == LFU)
		simulate_lfu(n_frames, page_reference, fd);
	else // SC algorithm
		simulate_sc(n_frames, page_reference, fd);
}

// menu 구조체를 초기화하는 함수
void init_menu(t_menu *menu)
{
	menu->n_frames = 0;			// 프레임 수
	menu->input_method = 0;		// 참조 문자열 생성 방법
	for (int i = 0; i < 7; i++) // 알고리즘 선택 여부
		menu->algorithm[i] = 0;
}

int main(void)
{
	t_menu menu;								 // UI menu 구조체
	t_reference reference[REFERENCE_SIZE] = {0}; // 참조 문자열

	init_menu(&menu);												 // menu 구조체 초기화
	input(&menu);													 // menu 구조체에 입력받은 값 저장
	int fd = open("result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); // 결과 파일 오픈
	if (fd < 0)
		exit_with_msg("파일 오픈 실패");
	set_reference(fd, reference, menu.input_method); // 참조 페이지 스트링 생성
	for (int i = 0; i < 7; i++)						 // 선택한 알고리즘 모두 수행
	{
		if (menu.algorithm[i])
			simulate_algorithm(menu.n_frames, reference, i, fd);
	}
	close(fd); // 결과 파일 닫기
	return (0);
}