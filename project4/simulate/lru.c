#include "../page_replacement.h"

void simulate_lru(int n_frames, int *page, int fd)
{
	t_frame *head = NULL; // 가장 최근에 들어온 프레임을 가리키는 포인터
	t_frame *cur, *prev;
	int page_fault = 0; // page fault 횟수
	char is_hit = 0;	// hit 여부

	print_algorithm_start_list("LRU", n_frames, fd);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		cur = head;
		is_hit = 0;
		for (int j = 0; j < n_frames; j++) // hit 여부 확인
		{
			if (!cur) // 프레임이 비어있거나 마지막 프레임일 경우
				break;
			if (cur->page == page[i]) // hit
			{
				is_hit = 1;
				if (cur != head) // cur==head라면 이미 가장 최근에 들어온 프레임이므로 다음 참조값 비교
				{
					prev->next = cur->next;
					cur->next = head;
					head = cur;
				}
				break;
			}
			if (!cur->next) // 마지막 프레임일 경우
				break;
			prev = cur;
			cur = cur->next;
		}
		if (is_hit) // hit!
		{
			print_frame_list(page[i], head, n_frames, "HIT!", fd);
			continue;
		}
		++page_fault;				// page fault 발생
		if (page_fault <= n_frames) // 프레임이 가득 차지 않았을 경우
		{
			t_frame *new_frame = (t_frame *)malloc(sizeof(t_frame));
			new_frame->page = page[i];
			new_frame->next = head;
			head = new_frame;
		}
		else // 프레임이 가득 찼을 경우
		{
			prev->next = cur->next;
			cur->next = head;
			cur->page = page[i];
			head = cur;
		}
		print_frame_list(page[i], head, n_frames, "miss", fd);
	}
	free_frame_list(head); // 할당된 프레임 메모리 해제
	print_result("LRU", page_fault, fd);
}