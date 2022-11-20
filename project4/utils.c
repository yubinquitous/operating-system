#include "page_replacement.h"

int *get_page_reference(int *page_reference, t_reference *reference)
{
	int i;

	for (i = 0; i < REFERENCE_SIZE; i++)
	{
		page_reference[i] = reference[i].page;
	}
	return page_reference;
}

void get_reference_with_rb_bit(int fd, t_reference *reference)
{
	int i;
	int stdin;

	stdin = dup(0);
	dup2(fd, 0);
	for (i = 0; i < REFERENCE_SIZE; i++)
	{
		scanf("%d(%c)", &reference[i].page, &reference[i].rw_bit);
	}
	dup2(stdin, 0);
}

void exit_with_msg(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

void print_algorithm_start(char *algorithm_type, int n_frames, int fd)
{
	char buf[100] = {0};

	printf("\033[0;32m<< %s algorithm >> \n\033[0m", algorithm_type);
	dprintf(fd, "<< %s algorithm >>", algorithm_type);
	printf("%10s", "page");
	dprintf(fd, "%10s", "page");
	for (int i = 0; i < n_frames; i++)
	{
		sprintf(buf, "Frame[%d]", i);
		printf("%10s", buf);
		dprintf(fd, "%10s", buf);
	}
	printf("%10s", "Result\n");
	dprintf(fd, "%10s", "Result\n");
}

void print_frame_array(int page, int *frame, int n_frames, char *result, int fd)
{
	char buf[100] = {0};

	// 참조값 출력
	printf("%10d", page);
	// 참조값 파일에 저장
	dprintf(fd, "%10d", page);
	for (int i = 0; i < n_frames; i++)
	{
		// 프레임값 출력
		printf("%10d", frame[i]);
		// 프레임값 파일에 저장
		dprintf(fd, "%10d", frame[i]);
	}
	// 결과 (HIT, miss, START) 출력
	printf("%10s\n", result);
	dprintf(fd, "%10s\n", result);
}

void print_frame_list(int page, t_frame *head, int n_frames, char *result, int fd)
{
	t_frame *tmp = head;
	int cnt = 0;
	char buf[100] = {0};

	// 참조값 출력
	printf("%10d", page);
	// 참조값 파일에 저장
	dprintf(fd, "%10d", page);
	while (tmp->next != NULL)
	{
		// 프레임값 출력
		printf("%10d", tmp->page);
		// 프레임값 파일에 저장
		dprintf(fd, "%10d", tmp->page);
		tmp = tmp->next;
		++cnt;
	}
	while (cnt < n_frames)
	{
		printf("%10s", " ");
		dprintf(fd, "%10s", " ");
		++cnt;
	}
	printf("%10s\n", result);
	dprintf(fd, "%10s\n", result);
}

void print_frame_with_r_bit(int page, t_frame_with_r_bit *frame, int n_frames, char *result, int fd)
{
	char buf[100] = {0};

	// 참조값 출력
	printf("%10d", page);
	// 참조값 파일에 저장
	dprintf(fd, "%10d", page);
	for (int i = 0; i < n_frames; i++)
	{
		// 프레임값과 r_bit 출력
		printf("%7d(%d)", frame[i].page, frame[i].r_bit);
		// 프레임값과 r_bit 파일에 저장
		dprintf(fd, "%7d(%d)", frame[i].page, frame[i].r_bit);
	}
	printf("%10s\n", result);
	dprintf(fd, "%10s\n", result);
}

void print_frame_with_rw_bit(t_reference reference, t_frame_with_rw_bit *frame, int n_frames, char *result, int fd)
{
	char buf[100] = {0};

	// 참조값 출력
	printf("%7d(%c)", reference.page, reference.rw_bit);
	// 참조값 파일에 저장
	dprintf(fd, "%7d(%c)", reference.page, reference.rw_bit);
	for (int i = 0; i < n_frames; i++)
	{
		// 프레임값과 r_bit 출력
		printf("%4d(%d, %d)", frame[i].page, frame[i].r_bit, frame[i].w_bit);
		// 프레임값과 r_bit 파일에 저장
		dprintf(fd, "%4d(%d, %d)", frame[i].page, frame[i].r_bit, frame[i].w_bit);
	}
	printf("%10s\n", result);
	dprintf(fd, "%10s\n", result);
}

void print_result(char *algorithm_type, int page_fault, int fd)
{
	char buf[100] = {0};

	printf("\033[0;31m%s page fault: %d\n\n\033[0m", algorithm_type, page_fault);
	dprintf(fd, "%s page fault: %d\n\n", algorithm_type, page_fault);
}

void init_frame(int *frame, int n_frames)
{
	for (int i = 0; i < n_frames; i++)
		frame[i] = 0;
}

void init_frame_list(t_frame *head, t_frame **tail, int n_frames)
{
	t_frame *cur = head;

	head->page = 0;
	for (int i = 0; i < n_frames; i++)
	{
		t_frame *new_frame = (t_frame *)malloc(sizeof(t_frame));
		new_frame->page = 0;
		cur->next = new_frame;
		cur = cur->next;
	}
	cur->next = NULL;
	*tail = cur;
}

void free_frame_list(t_frame *head)
{
	t_frame *tmp;

	while (head->next != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(head);
}

char is_hit(int *frame, int n_frames, int page)
{
	for (int i = 0; i < n_frames; i++)
	{
		if (frame[i] == page)
			return 1;
	}
	return 0;
}