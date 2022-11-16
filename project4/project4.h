#ifndef PROJECT4_H
#define PROJECT4_H
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

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

// menu.c
void input(t_menu *menu);

// utils.c
void exit_with_msg(char *msg);

#endif