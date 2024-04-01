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
Status lexcial_analyser(strinfo *info);
Status check_keyword(char *);
Status check_identifier(char );
Status check_operator(char *);
Status check_operator1(char );
#endif
