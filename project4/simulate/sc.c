#include "../page_replacement.h"

void simulate_sc(int n_frames, int *reference, int fd)
{
	t_frame_with_r_bit frame[n_frames]; // 프레임 구조체 배열
	int page_fault = 0;					// page fault 횟수
	char is_hit;						// hit 여부
	int idx = 0;						// 교체될 프레임을 가리키는 인덱스

	// 프레임 구조체 배열 초기화
	for (int i = 0; i < n_frames; i++)
	{
		frame[i].page = 0;
		frame[i].r_bit = 0;
	}
	print_algorithm_start("SC", n_frames, fd); // 알고리즘 정보 출력
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		int j;
		is_hit = 0; // hit 여부 초기화
		for (j = 0; j < n_frames; j++)
		{
			if (frame[j].page == 0) // 프레임이 비어있다면
				break;
			if (frame[j].page == reference[i]) // hit!
			{
				is_hit = 1;
				frame[j].r_bit = 1;
				break;
			}
		}
		if (is_hit) // hit -> 프레임 출력 후 다음 reference로 넘어간다.
		{
			print_frame_with_r_bit(reference[i], frame, n_frames, "HIT!", fd);
			continue;
		}
		++page_fault;				// page fault 발생
		if (page_fault <= n_frames) // 프레임이 비어있다면
		{
			frame[j].page = reference[i];
			frame[j].r_bit = 0;
		}
		else // 프레임이 가득 차있다면
		{
			while (1)
			{
				if (frame[idx].r_bit == 0) // r_bit가 0이면
				{
					frame[idx].page = reference[i];
					frame[idx].r_bit = 0;
					break;
				}
				else // r_bit가 1이면
				{
					frame[idx].r_bit = 0;		// r_bit를 0으로 바꾸고
					idx = (idx + 1) % n_frames; // 다음 프레임으로 넘어간다.
				}
			}
		}
		idx = (idx + 1) % n_frames;
		print_frame_with_r_bit(reference[i], frame, n_frames, "miss", fd);
	}
	print_result("SC", page_fault, fd);
}