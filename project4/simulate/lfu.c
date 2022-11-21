#include "../page_replacement.h"

void simulate_lfu(int n_frames, int *reference, int fd)
{
	int frame[n_frames];		  // 프레임 배열
	int page_fault = 0;			  // page fault 횟수
	int idx = 0;				  // 교체될 프레임을 가리키는 인덱스
	int counter[MAX_FRAME] = {0}; // 카운터 배열

	init_frame(frame, n_frames);				// 프레임 배열 초기화
	print_algorithm_start("LFU", n_frames, fd); // 알고리즘 정보 출력
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		if (is_hit(frame, n_frames, reference[i])) // hit!
		{
			++counter[reference[i] - 1];
			print_frame_array(reference[i], frame, n_frames, "HIT!", fd);
			continue;
		}
		++page_fault;				// page fault 발생
		if (page_fault <= n_frames) // 프레임이 가득 차지 않은 경우
		{
			frame[idx] = reference[i];
			idx = (idx + 1) % n_frames;
		}
		else
		{
			int min_idx = 0;
			int min_count = REFERENCE_SIZE;
			for (int j = 0; j < n_frames; j++) // 가장 적게 사용된 프레임 찾기
			{
				if (counter[frame[j] - 1] < min_count)
				{
					min_count = counter[frame[j] - 1];
					min_idx = j;
				}
			}
			frame[min_idx] = reference[i]; // 가장 적게 사용된 프레임 교체
		}
		counter[reference[i] - 1] = 1;								  // 카운터 배열 값 1로 설정
		print_frame_array(reference[i], frame, n_frames, "miss", fd); // 프레임 배열 출력
	}
	print_result("LFU", page_fault, fd); // page fault 횟수 출력
}