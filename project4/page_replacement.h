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

#define R_BIT 'R'
#define W_BIT 'W'

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

typedef struct s_frame_with_r_bit
{
	int page;
	int r_bit;
	struct s_frame_with_r_bit *next;
} t_frame_with_r_bit;

typedef struct s_frame_with_rw_bit
{
	int page;
	int r_bit;
	int w_bit;
	struct s_frame_with_rw_bit *next;
} t_frame_with_rw_bit;

typedef struct s_reference
{
	int page;
	char rw_bit;
} t_reference;

// menu
void input(t_menu *menu);

// utils
void exit_with_msg(char *msg);
void init_frame(int *frame, int n_frames);
char is_hit(int *frame, int n_frames, int page);
void init_frame_list(t_frame *head, t_frame **tail, int n_frames);
void print_frame_list(int page, t_frame *frame, int n_frames, char *result, int fd);
void print_frame_array(int *frame, int n_frames, char *msg, int fd);
void print_frame_with_r_bit(t_frame_with_r_bit *frame, int n_frames, char *msg, int fd);
void free_frame_list(t_frame *head);

int *get_page_reference(int *page_reference, t_reference *reference);
void get_reference_with_rb_bit(int fd, t_reference *reference);

// simulate
void simulate_optimal(int n_frames, int *reference, int fd);
void simulate_fifo(int n_frames, int *reference, int fd);
void simulate_lifo(int n_frames, int *reference, int fd);
void simulate_lru(int n_frames, int *reference, int fd);
void simulate_lfu(int n_frames, int *reference, int fd);
void simulate_sc(int n_frames, int *reference, int fd);

#endif