#ifndef MAIN_H
#define MAIN_H

#include "lexical.h"

typedef struct _strinfo
{
	FILE *str_edit;
	FILE *new_file;
	char *src_file;


}strinfo;

Status read_and_validate(char *argv[],strinfo *info);
Status start_process(strinfo *info);
Status open_file(strinfo *info);

#endif
