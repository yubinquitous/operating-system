#include "page_replacement.h"

void simulate_sc(int n_frames, int *reference)
{
	int frame[n_frames];
	int page_fault = 0;
	int frame_idx = 0;
	int r_bit[n_frames];

	init_frame(frame, n_frames);
	// init_r_bit(r_bit, n_frames);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		if (is_hit(frame, n_frames, reference[i]))
		{
			r_bit[reference[i]] = 1;
			continue;
		}
		++page_fault;
		if (page_fault < n_frames)
		{
			frame[frame_idx] = reference[i];
			frame_idx = (frame_idx + 1) % n_frames;
			r_bit[reference[i]] = 1;
		}
		else
		{
			while (r_bit[frame[frame_idx]] == 1)
			{
				r_bit[frame[frame_idx]] = 0;
				frame_idx = (frame_idx + 1) % n_frames;
			}
			frame[frame_idx] = reference[i];
			frame_idx = (frame_idx + 1) % n_frames;
			r_bit[reference[i]] = 1;
		}
	}
	// test_print_frame(frame, n_frames); // test
	printf("SC page fault: %d\n", page_fault);
}
