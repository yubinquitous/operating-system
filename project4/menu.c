#include "project4.h"

void set_algorithm(char *algorithm, int num)
{
	if (num == 8)
	{
		for (int i = 0; i < 7; i++)
			algorithm[i] = 1;
	}
	else
		algorithm[num - 1] = 1;
}

static void input_algorithm(t_menu *menu)
{
	int cnt = 0;
	int num;
	char *line;
	size_t tmp;

	getline(&line, &tmp, stdin);
	if (!line)
		exit_with_msg("메모리 할당에 실패했습니다.");
	char *token = strtok(line, " ");
	while (token != NULL)
	{
		// 4개 이상의 알고리즘을 입력받았으면 에러
		if (cnt == 3)
			exit_with_msg("4개 이상의 알고리즘을 입력할 수 없습니다.");
		num = atoi(token);
		// 1~8 이외의 숫자가 들어오면 에러
		if (num < 1 || num > 8)
			exit_with_msg("1~8 사이의 숫자를 입력해주세요.");
		set_algorithm(menu->algorithm, num); // 알고리즘 배열 설정
		++cnt;
		token = strtok(NULL, " ");
	}
	if (cnt == 0)
		exit_with_msg("알고리즘을 입력해주세요.");
	menu->cnt = cnt;
	// free(line);
	line = 0;
}

void input(t_menu *menu)
{
	int n_frames = -1;
	int input_method = -1;

	// Page Replacement 알고리즘 시뮬레이터 선택 (최대 3개)
	printf("Page Replacement 알고리즘 시뮬레이터 선택 (최대 3개)\n");
	printf("(1) Optimal\t(2) FIFO\t(3) LIFO\t(4) LRU\n");
	printf("(5) LFU\t\t(6) SC\t\t(7) ESC\t\t(8) ALL\n>> ");
	input_algorithm(menu);

	// 페이지 프레임 개수를 입력하시오
	printf("페이지 프레임 개수를 입력하시오. (3~10)\n>> ");
	scanf("%d", &n_frames);
	if (n_frames < 3 || n_frames > 10)
		exit_with_msg("3~10 사이의 숫자를 입력해주세요.");
	menu->n_frames = n_frames;

	// 데이터 입력 방식을 선택하시오
	printf("데이터 입력 방식을 선택하시오. (1, 2)\n");
	printf("(1) 랜덤하게 생성\t(2) 사용자 생성 파일 오픈\n>> ");
	scanf("%d", &input_method);
	if (input_method != 1 && input_method != 2)
		exit_with_msg("1 또는 2를 입력해주세요.");
	menu->input_method = input_method;
}