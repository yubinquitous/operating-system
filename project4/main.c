#include "page_replacement.h"

void test_print_frame(int *frame, int n_frames) // test
{
	for (int i = 0; i < n_frames; i++)
	{
		if (frame[i] == 0)
			printf("  ");
		else
			printf("%d ", frame[i]);
	}
	printf("\n");
}

void set_reference(t_reference *reference, int input_method)
{
	int page;
	char rb_state;

	if (input_method == 1)
	{
		// 랜덤하게 생성
		srand((unsigned int)time(NULL)); // 시드 설정
		for (int i = 0; i < 500; i++)
		{
			page = rand() % 30 + 1;
			rb_state = rand() % 2 ? 'R' : 'W';
			reference[i].page = page;
			reference[i].rw_bit = rb_state;
		}
	}
	else // 입력값 유효 검사를 했으므로 1이 아닌 input_method는 항상 2이다
	{
		// 사용자 생성 파일 오픈
		char file_name[100] = {0};
		printf("사용자 생성 파일을 입력하시오.\n>> ");
		scanf("%s", file_name);
		int fd = open(file_name, O_RDONLY);
		if (fd < 0)
			exit_with_msg("파일 오픈 실패");
		get_reference_with_rb_bit(fd, reference);
		close(fd);
	}
}

void simulate_algorithm(int n_frames, t_reference *reference, int algorithm_type, int fd)
{
	int page_reference[REFERENCE_SIZE] = {0};

	get_page_reference(page_reference, reference);
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
	else if (algorithm_type == SC)
		simulate_sc(n_frames, page_reference, fd);
	else if (algorithm_type == ESC)
		simulate_esc(n_frames, reference, fd);
	;
}

void init_menu(t_menu *menu)
{
	menu->algorithm_all_flag = 0;
	menu->n_frames = 0;
	menu->input_method = 0;
	menu->cnt = 0;
	for (int i = 0; i < 7; i++)
		menu->algorithm[i] = 0;
}

int main(void)
{
	t_menu menu;
	t_reference reference[REFERENCE_SIZE] = {0};

	init_menu(&menu);
	input(&menu);
	set_reference(reference, menu.input_method); // 참조 페이지 스트링 생성
	int fd = open("result.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	for (int i = 0; i < 7; i++)
	{
		if (menu.algorithm[i])
			simulate_algorithm(menu.n_frames, reference, i, fd);
	}
	return (0);
}