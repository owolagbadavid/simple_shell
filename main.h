#ifndef __MAIN_H__
#define __MAIN_H__
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <stdio.h>
void handle_sig(int sig);
int char_check(char *str, const char *delim);
char *_strtok(char *str, const char *delim);
int _strlen(const char *);
void sheller(void);
#endif
