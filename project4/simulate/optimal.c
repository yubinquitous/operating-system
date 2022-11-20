#include "../page_replacement.h"

void simulate_optimal(int n_frames, int *reference, int fd)
{
	int frame[n_frames]; // 프레임 배열
	int page_fault = 0;	 //  page fault 횟수
	int idx = 0;		 // 교체될 프레임을 가리키는 인덱스

	init_frame(frame, n_frames);					// 프레임 배열 초기화
	print_algorithm_start("OPTIMAL", n_frames, fd); // 알고리즘 정보 출력
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		if (is_hit(frame, n_frames, reference[i])) // hit!
		{
			print_frame_array(reference[i], frame, n_frames, "HIT!", fd);
			continue;
		}
		++page_fault;				// page fault 발생
		if (page_fault <= n_frames) // 프레임이 비어있다면
		{
			frame[idx] = reference[i];
			idx = (idx + 1) % n_frames;
		}
		else // 프레임이 가득 차있다면
		{
			int max_idx = 0;
			int max_dist = 0;
			for (int j = 0; j < n_frames; j++) // 가장 오랫동안 쓰이지 않은 page를 찾는다.
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
			frame[max_idx] = reference[i]; // 가장 오랫동안 쓰이지 않은 page를 교체한다.
		}
		print_frame_array(reference[i], frame, n_frames, "miss", fd);
	}
	print_result("OPTIMAL", page_fault, fd); // page fault 횟수 출력
}