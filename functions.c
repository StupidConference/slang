
#include "slang.h"


void slang_print()
{
	char *temp;

	temp = slang_args[0].value;
	if (slang_args[0].is_var)
		temp = slang_get_var(slang_args[0].value);

	printf("%s\n", temp);
}

void slang_debug()
{
	debug_lang = true;
}

void slang_about()
{
	printf("THAT IS SIMON LANGUAGE (Slang).\n* Langu"
		"age was created for downloading porno videos.\n");
}

char *slang_get_var(char *varname)
{
	struct slang_var *temp = slang_vars;

	while (temp != NULL) {
		if (strcmp(varname, temp->name) == 0)
			return temp->value;
		temp = temp->next;
	}
}

int slang_get_options(char *line)
{
	int len = 0;

	if (strlen(line) <= 1)
		return 0;

	for (int i = 1; i < strlen(line); i++) {
		if (len >= 10)
			break;

		if (line[i] == '$') {
			slang_args[len].is_var = true;
			continue;
		}

		if (line[i] == ',') {
			len++;
			continue;
		}

		if (strlen(slang_args[len].value) < 100)
			strncat(slang_args[len].value, &line[i], 1);
	}

	return len + 1;
}

bool slang_write_var(struct slang_var *var)
{
	struct slang_var *temp;

	if (!var || var == NULL || strlen(var->name) < 1
		|| strlen(var->value) < 1)
		return false;

	temp = (struct slang_var *)malloc(sizeof(struct slang_var));
	memcpy(temp, var, sizeof(struct slang_var));

	temp->next = slang_vars;
	slang_vars = temp;
	slang_vnum++;

	if (debug_lang)
		printf("[Debug] New var: %s - %s\n", slang_vars->name, slang_vars->value);

	return true;
}

void slang_clear_options()
{
	for (int i = 0; i < 10; i++)
		memset(slang_args[i].value, 0x00, 100);
}