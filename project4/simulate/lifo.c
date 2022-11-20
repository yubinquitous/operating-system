#include "../page_replacement.h"

void simulate_lifo(int n_frames, int *reference, int fd)
{
	int frame[n_frames]; // 프레임 배열
	int page_fault = 0;	 // page fault 횟수
	int idx = 0;		 // 교체될 프레임을 가리키는 인덱스

	init_frame(frame, n_frames);				 // 프레임 배열 초기화
	print_algorithm_start("LIFO", n_frames, fd); // 알고리즘 정보 출력
	for (int i = 0; i < REFERENCE_SIZE; i++)
	{
		if (is_hit(frame, n_frames, reference[i])) // hit!
		{
			print_frame_array(reference[i], frame, n_frames, "HIT!", fd);
			continue;
		}
		++page_fault;												  // page fault 발생
		frame[idx] = reference[i];									  // 교체될 프레임에 새로운 페이지 삽입
		if (idx < n_frames - 1)										  // 프레임이 비어있다면
			++idx;													  // 포인터(인덱스)를 다음 프레임으로 이동
		print_frame_array(reference[i], frame, n_frames, "miss", fd); // 프레임 배열 출력
	}
	print_result("LIFO", page_fault, fd); // page fault 횟수 출력
}