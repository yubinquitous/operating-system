#include "../page_replacement.h"

void update_counter(int *counter)
{
	for (int i = 0; i < MAX_FRAME; i++)
	{
		if (counter[i] > 0)
			counter[i] = counter[i] >> 1;
	}
}

void simulate_lfu(int n_frames, int *page)
{
	int frame[n_frames];
	int page_fault = 0;
	int frame_idx = 0;
	int counter[MAX_FRAME] = {0};

	init_frame(frame, n_frames);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		if (i != 0 && i % 10 == 0)
			update_counter(counter);
		if (is_hit(frame, n_frames, page[i]))
		{
			++counter[page[i] - 1];
			continue;
		}
		++page_fault;
		if (page_fault <= n_frames)
		{
			frame[frame_idx] = page[i];
			frame_idx = (frame_idx + 1) % n_frames;
		}
		else
		{
			int min_idx = 0;
			int min_count = 500;
			for (int j = 0; j < n_frames; j++)
			{
				if (counter[frame[j] - 1] < min_count)
				{
					min_count = counter[frame[j] - 1];
					min_idx = j;
				}
			}
			frame[min_idx] = page[i];
		}
		++counter[page[i] - 1];
	}
	// test_print_frame(frame, n_frames); // test
	printf("LFU page fault: %d\n", page_fault);
}