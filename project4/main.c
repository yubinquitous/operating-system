#include "project4.h"

void test_print_frame(int *frame, int n_frames) // test
{
	for (int i = 0; i < n_frames; i++)
	{
		if (frame[i] == -1)
			printf("  ");
		else
			printf("%d ", frame[i]);
	}
	printf("\n");
}

void set_reference(int *reference, int input_method)
{
	if (input_method == 1)
	{
		// 랜덤하게 생성
		srand((unsigned int)time(NULL)); // 시드 설정
		for (int i = 0; i < REFERENCE_SIZE; i++)
		{
			reference[i] = rand() % 30 + 1;
			printf("%d ", reference[i]);
		}
		printf("\n");
	}
	else // 입력값 유효 검사를 했으므로 1이 아닌 input_method는 항상 2이다
	{
		// 사용자 생성 파일 오픈
		// char reference_file[100] = {
		// 	'\0',
		// };
		// test
		char *reference_file = "reference.txt";
		// printf("사용자 생성 파일을 입력하시오.\n>> ");
		// scanf("%s", reference_file);
		int fd = open(reference_file, O_RDONLY);
		if (fd < 0)
			exit_with_msg("파일 오픈 실패");
		for (int i = 0; i < REFERENCE_SIZE; i++)
			read(fd, &reference[i], sizeof(int));
		/* test
		// int fd = open("./reference.txt", O_RDONLY);
		// int r;
		// read(fd, &r, sizeof(int));
		// printf("%d\n", r);
		// close(fd);
		*/
	}
}

void init_frame(int *frame, int n_frames)
{
	for (int i = 0; i < n_frames; i++)
		frame[i] = 0;
}

void simulate_fifo(int n_frames, int *reference)
{
	int frame[n_frames];
	int page_fault = 0;
	int frame_idx = 0;

	init_frame(frame, n_frames);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		char is_hit = 0;
		for (int j = 0; j < n_frames; j++)
		{
			if (reference[i] == frame[j])
			{
				is_hit = 1;
				break;
			}
		}
		if (is_hit)
			continue;
		else
		{
			++page_fault;
			frame[frame_idx] = reference[i];
			frame_idx = (frame_idx + 1) % n_frames;
		}
	}
	printf("FIFO page fault: %d\n", page_fault);
}

void simulate_optimal(int n_frames, int *reference)
{
	int frame[n_frames];
	int page_fault = 0;
	int frame_idx = 0;

	init_frame(frame, n_frames);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		char is_hit = 0;
		for (int j = 0; j < n_frames; j++)
		{
			if (reference[i] == frame[j])
			{
				is_hit = 1;
				break;
			}
		}
		if (is_hit)
			continue;
		else
		{
			++page_fault;
			if (page_fault < n_frames)
			{
				frame[frame_idx] = reference[i];
				frame_idx = (frame_idx + 1) % n_frames;
			}
			else
			{
				int max_idx = 0;
				int max_dist = 0;
				for (int j = 0; j < n_frames; j++)
				{
					int dist = 0;
					for (int k = i + 1; k < REFERENCE_SIZE; k++)
					{
						++dist;
						if (frame[j] == reference[k])
							break;
					}
					if (dist > max_dist)
					{
						max_dist = dist;
						max_idx = j;
					}
				}
				frame[max_idx] = reference[i];
			}
		}
	}
	printf("Optimal page fault: %d\n", page_fault);
}

void simulate_lifo(int n_frames, int *reference)
{
	int frame[n_frames];
	int page_fault = 0;
	int frame_idx = 0;

	init_frame(frame, n_frames);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		char is_hit = 0;
		for (int j = 0; j < n_frames; j++)
		{
			if (reference[i] == frame[j])
			{
				is_hit = 1;
				break;
			}
		}
		if (is_hit)
			continue;
		else
		{
			++page_fault;
			frame[frame_idx] = reference[i];
			if (frame_idx != n_frames - 1)
				frame_idx = (frame_idx + 1) % n_frames;
		}
	}
	printf("LIFO page fault: %d\n", page_fault);
}

void simulate_lru(int n_frames, int *reference)
{
	int frame[n_frames];
	int page_fault = 0;
	int frame_idx = 0;

	init_frame(frame, n_frames);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		char is_hit = 0;
		for (int j = 0; j < n_frames; j++)
		{
			if (reference[i] == frame[j])
			{
				is_hit = 1;
				break;
			}
		}
		if (is_hit)
			continue;
		else
		{
			++page_fault;
			if (page_fault < n_frames)
			{
				frame[frame_idx] = reference[i];
				frame_idx = (frame_idx + 1) % n_frames;
			}
			else
			{
				int max_idx = 0;
				int max_dist = 0;
				for (int j = 0; j < n_frames; j++)
				{
					int dist = 0;
					for (int k = i - 1; k >= 0; k--)
					{
						++dist;
						if (frame[j] == reference[k])
							break;
					}
					if (dist > max_dist)
					{
						max_dist = dist;
						max_idx = j;
					}
				}
				frame[max_idx] = reference[i];
			}
		}
	}
	// test_print_frame(frame, n_frames); // test
	printf("LRU page fault: %d\n", page_fault);
}

void simulate_algorithm(int n_frames, int *reference, int algorithm_type)
{
	if (algorithm_type == OPTIMAL)
		simulate_optimal(n_frames, reference);
	else if (algorithm_type == FIFO)
		simulate_fifo(n_frames, reference);
	else if (algorithm_type == LIFO)
		simulate_lifo(n_frames, reference);
	else if (algorithm_type == LRU)
		simulate_lru(n_frames, reference);
	else if (algorithm_type == LFU)
		;
	else if (algorithm_type == SC)
		;
	else if (algorithm_type == ESC)
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
	int reference[REFERENCE_SIZE] = {0}; // 참조 페이지 스트링

	init_menu(&menu);
	input(&menu);
	set_reference(reference, menu.input_method); // 참조 페이지 스트링 생성
	for (int i = 0; i < 7; i++)
	{
		if (menu.algorithm[i])
			simulate_algorithm(menu.n_frames, reference, i);
	}
	return (0);
}