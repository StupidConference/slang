
#include "slang.h"

int main(int argc, char *args[])
{
	char buffer[9000], c;
	unsigned int counter = 0;
	FILE *fp;

	if (argc < 2) {
		printf("Error: Incorrect args.\n");
		return 1;
	}

	if (!(fp = fopen(args[1], "r"))) {
		printf("Error: Can't get access to source file.\n");
		return 1;
	}

	while (counter++, (c = getc(fp)) != EOF) {
		if (counter >= 9000)
			break;

		strncat(buffer, &c, 1);
	}

	debug_lang = false;
	slang_vars = NULL;
	slang_vnum = 0;

	exec_lines(buffer);
}

void exec_lines(char *data)
{
	char *tok, buffer[250];

	if (!data || data == NULL) {
		printf("Error: Buffer is empty.\n");
		return;
	}

	tok = strtok(data, "\n");

	while (tok != NULL) {
		memcpy(buffer, tok, strlen(tok) + 1);
		
		if (!exec_command(buffer)) {
			printf("Incorrect line: %s\n", buffer);
			exit(1);
		}
		tok = strtok(NULL, "\n");
	}
}

bool exec_command(char *line)
{
	bool status = false;

	if (!line || line == NULL) {
		printf("Error: Executable line is empty.\n");
		exit(1);
	}

	if (line[0] == '#')
		return true;

	if (strstr(line, " = ") && strstr(line, "$"))
		status = exec_var(line);
	else if (strstr(line, "(") && strstr(line, ")"))
		status = exec_function(line);

	return status;
}

bool exec_function(char *line)
{
	struct slang_functions funcs[] = {
		{"print", slang_print, 1},
		{"about", slang_about, 0},
		{"enable_debug", slang_debug, 0}
	};
	char func_name[30], params[100] = {0x00};
	bool status = false;

	sscanf(line, "%29[^(]%99[^)]", func_name, params);

	for (int i = 0; i < 3; i++)
		if (strcmp(func_name, funcs[i].name) == 0) {
			if (slang_get_options(params) == funcs[i].args) {
				funcs[i].func_name();
				status = true;
			}

			slang_clear_options();
		}

	return status;
}

bool exec_var(char *line)
{
	struct slang_var temp;

	if (!line || line == NULL)
		return false;

	sscanf(line, "$%14s = %99[0-9a-zA-Z ]", temp.name, temp.value);
	return slang_write_var(&temp);
}