#include "page_replacement.h"

void update_counter(int *counter)
{
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		if (counter[i] > 0)
			counter[i] = counter[i] >> 1;
	}
}

void init_counter(int *counter, int n_frames)
{
	for (int i = 0; i < n_frames; i++)
		counter[i] = 0;
}

void simulate_lfu(int n_frames, int *reference)
{
	int frame[n_frames];
	int page_fault = 0;
	int frame_idx = 0;
	int counter[n_frames];

	init_frame(frame, n_frames);
	init_counter(counter, n_frames);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		if (i != 0 && i % 10 == 0)
			update_counter(counter);
		if (is_hit(frame, n_frames, reference[i]))
		{
			++counter[reference[i]];
			continue;
		}
		++page_fault;
		if (page_fault < n_frames)
		{
			frame[frame_idx] = reference[i];
			frame_idx = (frame_idx + 1) % n_frames;
			++counter[reference[i]];
		}
		else
		{
			int min_idx = 0;
			int min_count = 0;
			for (int j = 0; j < n_frames; j++)
			{
				if (counter[frame[j]] < min_count)
				{
					min_count = counter[frame[j]];
					min_idx = j;
				}
			}
			frame[min_idx] = reference[i];
			++counter[reference[i]];
		}
	}
	// test_print_frame(frame, n_frames); // test
	printf("LFU page fault: %d\n", page_fault);
}