#include "../page_replacement.h"

void simulate_fifo(int n_frames, int *reference, int fd)
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
		frame[frame_idx] = reference[i];
		frame_idx = (frame_idx + 1) % n_frames;
		print_frame_array(frame, n_frames, "miss", fd);
	}
	printf("FIFO page fault: %d\n", page_fault);
}