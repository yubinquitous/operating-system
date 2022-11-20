#include "../page_replacement.h"

void simulate_esc(int n_frames, t_reference *reference, int fd)
{
	t_frame_with_rw_bit frame[n_frames]; // 프레임 구조체 배열
	int page_fault = 0;					 // page fault 횟수
	char is_hit;						 // hit 여부
	int idx = 0;						 // 교체될 프레임을 가리키는 인덱스
	char find_victim = 0;				 // victim을 찾았는지 확인하는 변수

	// frame 초기화
	for (int i = 0; i < n_frames; i++)
	{
		frame[i].page = 0;
		frame[i].r_bit = 0;
		frame[i].w_bit = 0;
	}
	print_algorithm_start("ESC", n_frames, fd); // 알고리즘 정보 출력
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		find_victim = 0;
		is_hit = 0;
		int j = 0;
		for (j = 0; j < n_frames; j++)
		{
			if (frame[j].page == 0)
				break;
			if (frame[j].page == reference[i].page) // hit!
			{
				is_hit = 1;
				frame[j].r_bit = 1;								 // r_bit을 1로 설정
				frame[j].w_bit = (reference[i].rw_bit == W_BIT); // w_bit을 1로 설정
				break;
			}
		}
		if (is_hit) // hit!
		{
			print_frame_with_rw_bit(reference[i], frame, n_frames, "HIT!", fd); // frame 출력
			continue;															// 다음 참조값으로 넘어감
		}
		++page_fault;				// page fault 발생
		if (page_fault <= n_frames) // 비어있는 프레임이 있으면
		{
			frame[j].page = reference[i].page;
			frame[j].r_bit = 1;
			frame[j].w_bit = (reference[i].rw_bit == W_BIT);
		}
		else // frame이 가득 찬 경우
		{
			while (1)
			{
				// 단계 1: (0, 0) 찾기
				for (j = 0; j < n_frames; j++)
				{
					if (frame[idx].r_bit == 0 && frame[idx].w_bit == 0)
					{
						find_victim = 1;
						break;
					}
					idx = (idx + 1) % n_frames; // 포인터를 다음 프레임으로 이동
				}
				// (0, 0)을 찾았다면 교체 후 반복문 탈출
				if (find_victim)
				{
					frame[idx].page = reference[i].page;
					frame[idx].r_bit = 1;
					frame[idx].w_bit = (reference[i].rw_bit == W_BIT);
					break;
				}
				// 단계 2: (0, 1) 찾기
				for (j = 0; j < n_frames; j++)
				{
					if (frame[idx].r_bit == 0 && frame[idx].w_bit == 1)
					{
						find_victim = 1;
						break;
					}
					idx = (idx + 1) % n_frames;
					frame[j].r_bit = 0; // 지나쳐가는 모든 프레임의 사용 비트를 0으로 설정
				}
				// (0, 1)을 찾았다면
				if (find_victim)
				{
					frame[idx].page = reference[i].page;
					frame[idx].r_bit = 1;
					frame[idx].w_bit = (reference[i].rw_bit == W_BIT);
					break;
				}
			}
			idx = (idx + 1) % n_frames; // 포인터를 다음 프레임으로 이동
		}
		print_frame_with_rw_bit(reference[i], frame, n_frames, "miss", fd); // frame 출력
	}
	print_result("ESC", page_fault, fd); // page fault 횟수 출력
}