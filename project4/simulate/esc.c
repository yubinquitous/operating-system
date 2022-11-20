#include "../page_replacement.h"

void simulate_esc(int n_frames, int *reference, int fd)
{
	t_frame_with_rb_bit frame[n_frames];
	int page_fault = 0;
	char is_hit;
	int idx = 0;

	// init frame
	for (int i = 0; i < n_frames; i++)
	{
		frame[i].page = 0;
		frame[i].r_bit = 0;
		frame[i].b_bit = 0;
	}
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		int cnt = -1;
		int j;
		is_hit = 0;
		for (j = 0; j < n_frames; j++)
		{
			if (frame[j].page == 0)
				break;
			if (frame[j].page == reference[i])
			{
				is_hit = 1;
				frame[j].r_bit = 1;
				frame[j].b_bit = 1;
				break;
			}
		}
		if (is_hit)
		{
			print_frame_with_rb_bit(frame, n_frames, "HIT", fd);
			continue;
		}
		++page_fault;
		if (j < n_frames) // frame is not full
		{
			frame[j].page = reference[i];
			frame[j].r_bit = 0;
			frame[j].b_bit = 1;
		}
		else // frame is full
		{
			while (1)
			{
				if (frame[idx].r_bit == 0 && frame[idx].b_bit == 0)
				{
					frame[idx].page = reference[i];
					frame[idx].r_bit = 0;
					frame[idx].b_bit = 1;
					break;
				}
				else if (frame[idx].r_bit == 0 && frame[idx].b_bit == 1)
				{
					frame[idx].r_bit = 0;
					frame[idx].b_bit = 0;
					idx = (idx + 1) % n_frames;
				}
				else if (frame[idx].r_bit == 1 && frame[idx].b_bit == 0)
				{
					frame[idx].r_bit = 0;
					idx = (idx + 1) % n_frames;
				}
				else if (frame[idx].r_bit == 1 && frame[idx].b_bit == 1)
				{
					frame[idx].r_bit = 0;
					frame[idx].b_bit = 0;
					idx = (idx + 1) % n_frames;
				}
			}
		}
		print_frame_with_rb_bit(frame, n_frames, "MISS", fd);
	}
	printf("page fault: %d\n", page_fault);
}
