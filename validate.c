#include <stdio.h>
#include <string.h>
#include "lex.h"
#include "lexical.h"

Status read_and_validate(char *argv[],strinfo *info)
{
	if(strstr(argv[1],".c")!=NULL )
	{
	        info->src_file = argv[1];
	}
	else
	{
		printf("ERROR : pass the c progaming file\n");
		return l_false;
	}
	return l_true;
}
Status open_file(strinfo *info)
{
	info->str_edit = fopen(info->src_file,"r");
	if(info->str_edit != NULL)
		return l_true;
	else
		return l_false;
}
Status start_process(strinfo *info)
{
	printf("Parsing    :    %s     :    Started \n",info->src_file);
		
}
        
