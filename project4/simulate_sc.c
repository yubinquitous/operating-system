#include "page_replacement.h"

// char is_hit_list(t_frame *frame, int cnt, int page)
// {
// 	t_frame *tmp = frame;
// 	for (int i = 0; i < cnt; i++)
// 	{
// 		if (tmp->page == page)
// 		{
// 			tmp->r_bit = 1;
// 			return 1;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return 0;
// }

static void init_frame_list_with_r(t_frame *frame, int n_frames)
{
	t_frame *tmp = frame;
	for (int i = 0; i < n_frames; i++)
	{
		tmp->page = 0;
		tmp->r_bit = 0;
		tmp->next = (t_frame *)malloc(sizeof(t_frame));
		tmp = tmp->next;
	}
	tmp->next = frame;
}

void simulate_sc(int n_frames, int *reference)
{
	t_frame *frame = (t_frame *)malloc(sizeof(t_frame));
	t_frame *tail;
	int page_fault = 0;
	int frame_idx = 0;

	// reference[0] 값으로 frame 초기화
	init_frame_list_with_r(t_frame * frame, int n_frames)
	{
		(frame, n_frames);
		++page_fault;
		frame->page = reference[0];
		frame->r_bit = 1;
		tail = frame;
		printf("reference[%d] = %d\t", 0, reference[0]);
		print_frame_list(frame, n_frames);
		printf("miss\n");

		for (int i = 1; i < REFERENCE_SIZE; i++)
		{
			printf("reference[%d] = %d\t", i, reference[i]);
			if (is_hit_list(frame, i, reference[i]))
			{
				print_frame_list(frame, n_frames);
				printf("hit\n");
				continue;
			}
			++page_fault;
			if (page_fault <= n_frames)
			{
				t_frame *new = (t_frame *)malloc(sizeof(t_frame));
				new->page = reference[i];
				new->r_bit = 1;
				new->next = frame;
				tail->next = new;
				tail = new;
			}
			else
			{
				t_frame *cur = frame;
				t_frame *head = frame;
				t_frame *prev = tail;
				while (1)
				{
					if (cur->r_bit == 0)
					{
						if (cur == head)
							head = cur->next;
						prev->next = cur->next;
						cur->page = reference[i];
						cur->r_bit = 1;
						cur->next = head;
						tail->next = cur;
						tail = cur;
						break;
					}
					else
					{
						cur->r_bit = 0;
						prev = cur;
						cur = cur->next;
					}
				}
			}
			print_frame_list(frame, n_frames);
			printf("miss\n");
		}
		// test_print_frame(frame, n_frames); // test
		printf("SC page fault: %d\n", page_fault);
	}
