#include "../page_replacement.h"

void simulate_lru(int n_frames, int *page, int fd)
{
	t_frame *frame = (t_frame *)malloc(sizeof(t_frame));
	t_frame *head = frame;
	int page_fault = 0;
	char is_hit;

	frame->page = 0;
	frame->next = NULL;
	print_frame_list(0, head, n_frames, "START", fd);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		// check_hit
		t_frame *cur = head;
		t_frame *prev = NULL;
		is_hit = 0;
		for (int j = 0; j < n_frames; j++)
		{
			if (cur->next == NULL)
				break;
			if (cur->page == page[i]) // hit
			{
				is_hit = 1;
				if (cur != head)
				{
					prev->next = cur->next;
					cur->next = head;
					head = cur;
				}
				break;
			}
			prev = cur;
			cur = cur->next;
		}
		if (is_hit)
		{
			print_frame_list(page[i], head, n_frames, "HIT!", fd);
			continue;
		}
		// miss
		++page_fault;
		if (page_fault <= n_frames) // frame is not full
		{
			t_frame *new_frame = (t_frame *)malloc(sizeof(t_frame));
			new_frame->page = page[i];
			new_frame->next = head;
			head = new_frame;
		}
		else // frame is full
		{
			prev->next = cur->next;
			prev = cur;
			cur->next = head;
			cur->page = page[i];
			head = cur;
		}
		print_frame_list(page[i], head, n_frames, "miss", fd);
	}
	free_frame_list(head);
	printf("LRU page fault: %d\n", page_fault);
}