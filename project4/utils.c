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

void print_frame_array(int *frame, int n_frames, char *msg, int fd)
{
	char buf[100] = {0};

	for (int i = 0; i < n_frames; i++)
	{
		printf("%d\t", frame[i]);
		sprintf(buf, "%d\t", frame[i]);
		write(fd, buf, strlen(buf));
	}
	printf("%s\n", msg);
	sprintf(buf, "%s\n", msg);
	write(fd, buf, strlen(buf));
}

void print_frame_list(int page, t_frame *head, int n_frames, char *result, int fd)
{
	t_frame *tmp = head;
	int cnt = 0;
	char buf[100] = {0};

	printf("%d\t", page);
	sprintf(buf, "%d\t", page);
	write(fd, buf, strlen(buf));
	while (tmp->next != NULL)
	{
		printf("%d\t", tmp->page);
		sprintf(buf, "%d\t", tmp->page);
		write(fd, buf, strlen(buf));
		tmp = tmp->next;
		++cnt;
	}
	while (cnt < n_frames)
	{
		printf("0\t");
		sprintf(buf, "0\t");
		write(fd, buf, strlen(buf));
		++cnt;
	}
	printf("%s\n", result);
	sprintf(buf, "%s\n", result);
	write(fd, buf, strlen(buf));
}

void print_frame_with_r_bit(t_frame_with_r_bit *frame, int n_frames, char *msg, int fd)
{
	char buf[100] = {0};

	for (int i = 0; i < n_frames; i++)
	{
		printf("%d(%d)\t", frame[i].page, frame[i].r_bit);
		sprintf(buf, "%d(%d)\t", frame[i].page, frame[i].r_bit);
		write(fd, buf, strlen(buf));
	}
	printf("%s\n", msg);
	sprintf(buf, "%s\n", msg);
	write(fd, buf, strlen(buf));
}

void print_result(char *algorithm_type, int page_fault, int fd)
{
	char buf[100] = {0};

	printf("\033[0;31m%s page fault: %d\n\n\033[0m", algorithm_type, page_fault);
	sprintf(buf, "%s page fault: %d\n\n", algorithm_type, page_fault);
	write(fd, buf, strlen(buf));
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