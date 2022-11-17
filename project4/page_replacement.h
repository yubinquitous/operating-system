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
#define MAX_FRAME 30

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

typedef struct s_menu
{
	char algorithm[7];
	char algorithm_all_flag;
	int n_frames;
	int input_method;
	int cnt;
} t_menu;

typedef struct s_frame
{
	int page;
	struct s_frame *next;
} t_frame;

typedef struct s_frame_with_r
{
	int page;
	int r_bit;
	struct s_frame_with_r *next;
} t_frame_with_r;

// menu
void input(t_menu *menu);

// utils
void exit_with_msg(char *msg);
void init_frame(int *frame, int n_frames);
char is_hit(int *frame, int n_frames, int page);
void init_frame_list(t_frame *head, t_frame **tail, int n_frames);
void print_frame_list(t_frame *frame, int n_frames, char *result);
void print_frame_array(int *frame, int n_frames, char *msg);
void free_frame_list(t_frame *head);

// simulate
void simulate_optimal(int n_frames, int *reference);
void simulate_fifo(int n_frames, int *reference);
void simulate_lifo(int n_frames, int *reference);
void simulate_lru(int n_frames, int *reference);
void simulate_lfu(int n_frames, int *reference);
void simulate_sc(int n_frames, int *reference);

#endif