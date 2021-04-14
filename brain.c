/* See LICENSE file for copyright and license details. */

#include <stdio.h>
#include <stdlib.h>

/* search for matching `[` command */
void goto_open(char **codep)
{
	int search = 1;
	while (search > 0) {
		--*codep;
		switch (**codep) {
		case '[':
			--search;
			break;
		case ']':
			++search;
			break;
		default:
			break;
		}
	}
}

/* search for matching `]` command */
void goto_close(char **codep)
{
	int search = 1;
	while (search > 0) {
		++*codep;
		switch (**codep) {
		case '[':
			++search;
			break;
		case ']':
			--search;
			break;
		default:
			break;
		}
	}
}

/* execute given command */
void exec_command(char **codep, char **memp)
{
	switch (**codep) {
	case '>':
		++*memp;
		break;
	case '<':
		--*memp;
		break;
	case '+':
		++**memp;
		break;
	case '-':
		--**memp;
		break;
	case '.':
		fputc(**memp, stdout);
		break;
	case ',':
		**memp = fgetc(stdin);
		break;
	case '[':
		if (!**memp)
			goto_close(codep);
		break;
	case ']':
		if (**memp)
			goto_open(codep);
		break;
	default:
		break;
	}
}

/* interpret brainfuck code */
void interpret(FILE *fp)
{
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char code[fsize];
	char *codep = code;
	fread(code, 1, fsize, fp);

	char mem[30000] = {0};
	char *memp = mem;

	while (codep < code + fsize) {
		exec_command(&codep, &memp);
		++codep;
	}
}

/* handle command-line arguments and open file */
int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		fprintf(stderr, "Error: failed to open file '%s'\n", argv[1]);
		return EXIT_FAILURE;
	}

	interpret(fp);

	fclose(fp);
	return EXIT_SUCCESS;
}
