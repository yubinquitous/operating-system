#include "../page_replacement.h"

void simulate_optimal(int n_frames, int *reference, int fd)
{
	int frame[n_frames];
	int page_fault = 0;
	int frame_idx = 0;

	init_frame(frame, n_frames);
	print_frame_array(frame, n_frames, "START", fd);
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		if (is_hit(frame, n_frames, reference[i]))
		{
			print_frame_array(frame, n_frames, "HIT", fd);
			continue;
		}
		++page_fault;
		if (page_fault <= n_frames)
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
		print_frame_array(frame, n_frames, "miss", fd);
	}
	printf("Optimal page fault: %d\n", page_fault);
}