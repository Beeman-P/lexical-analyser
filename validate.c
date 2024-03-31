#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
Status check_operator(char *opt)
{
	char oper[50][20]={"[","]","->",".","++","--","!","~","++","--",
		           "*","&","*","/","%","+","-",">>","<<","<<=",">>=",
			   "==","!=","&","^","|","&&","||","?:","=","+=","-=",
			   "*=","/=","%=","<<=",">>=","&=","^=","|=",",",";","{","}","(",")"};
	for(int i=0;i<50;i++)
	{
		if(strcmp(opt,oper[i]) == 0)
		{
			printf("Operator      :    %s\n",opt);
			return l_true;
		}
	}
	return l_false;
}
Status check_keyword(char *str)
{
	  const char* keywords[]  = { "auto",     "break",    "case",     "char", 
                                      "const",    "continue", "default",  "do", 
                                      "double",   "else",     "enum",     "extern", 
                                      "float",    "for",      "goto",     "if", 
                                      "int",      "long",     "register", "return", 
                                      "short",    "signed",   "sizeof",   "static", 
                                      "struct",   "switch",   "typedef",  "union", 
                                      "unsigned", "void",     "volatile", "while" }; 
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) { 
        if (strcmp(str, keywords[i]) == 0) { 
		return l_true;
        } 
    } 
    return l_false; 
}
Status lexcial_analyser(strinfo *info)
{
	char st;
	int i=0,j=0,k=0,l=0;
	int flag=0;
	char str[30];
	char n[20];
	char con[20];
	char hd[20];
	while((st=fgetc(info->str_edit))!=-1)
	{
		  if(isalpha(st))
		  {
			  str[i++]=st;
			  while(isalpha(st=fgetc(info->str_edit)))
			  {
				  str[i++]=st;
			  }
			  str[i]='\0';
			  if(strcmp(str,"sizeof")==0)
			  {
				  printf("Operator      :    %s\n",str);
			  }
			  else
			  {
			  if(check_keyword(str)==l_true)
			   {
	                 	printf("Keyword       :    %s\n",str);
			   }
			  i=0;
			  fseek(info->str_edit, -1, SEEK_CUR);
			  }
		  }
		  else if (st=='#')
		  {
			  hd[l++]=st;
			  while((st=fgetc(info->str_edit))!='\n')
			  {
				  hd[l++]=st;
			  }
			  hd[l]='\0';
			  l=0;
			  fseek(info->str_edit,-1,SEEK_CUR);
			  printf("Preprocess    :    %s\n",hd);
		  }
	      else if(ispunct(st))
		  {
			  n[j++]=st;
			  while(ispunct(st=fgetc(info->str_edit)))
			  {
				  n[j++]=st;
			  }
			  n[j]='\0';
			  check_operator(n);
			  j=0;
			  fseek(info->str_edit, -1, SEEK_CUR);
		  }
	      else if(isdigit(st))
		  {
			  con[k++]=st;
			  while(isdigit(st=fgetc(info->str_edit)))
			  {
				  con[k++]=st;
			  }
			  con[k]='\0';
			  k=0;
			  fseek(info->str_edit, -1, SEEK_CUR);
			  printf("Constant      :     %s\n",con);
		  }	
	
	}

}
Status start_process(strinfo *info)
{
	printf("Parsing    :    %s     :    Started \n",info->src_file);
	if(lexcial_analyser(info)==l_true)
	{
		return l_true;
	}

		
}
        
