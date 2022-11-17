#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define REFERENCE_SIZE 500

typedef struct s_menu
{
	char algorithm[7];
	char algorithm_all_flag;
	int n_frames;
	int input_method;
	int cnt;
} t_menu;

enum e_algorithm_type
{
	OPTIMAL = 0,
	FIFO,
	LIFO,
	LRU,
	LFU,
	SC,
	ESC,
};

typedef struct s_frame
{
	int page;
	char r_bit;
	struct s_frame *next;
} t_frame;

// menu.c
void input(t_menu *menu);

// utils.c
void exit_with_msg(char *msg);
void init_frame(int *frame, int n_frames);
char is_hit(int *frame, int n_frames, int page);

// simulate_lfu.c
void simulate_lfu(int n_frames, int *reference);

// simulate_sc.c
void simulate_sc(int n_frames, int *reference);

#endif