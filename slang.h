#ifndef SLANG_H
#define SLANG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct slang_var {
	char name[15];
	char value[100];
	struct slang_var *next;
};

struct slang_functions {
	char *name;
	void (*func_name)();
	unsigned int args;
};

struct slang_arg {
	char value[100];
	bool is_var;
};


bool debug_lang;
struct slang_var *slang_vars;
unsigned int slang_vnum;
struct slang_arg slang_args[10];

bool exec_var(char *);
void exec_lines(char *);
bool exec_command(char *);
bool exec_function(char *);
void slang_print();
void slang_about();
int slang_get_options(char *);
void slang_clear_options();
void slang_print_vars();
bool slang_write_var(struct slang_var *);
char *slang_get_var(char *);
void slang_debug();

#endif