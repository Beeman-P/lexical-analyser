#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lex.h"
#include "lexical.h"

Status read_and_validate(char *argv[],strinfo *info)                                       //check the given file is c or not
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

Status open_file(strinfo *info)                                                          //open the file
{
	info->str_edit = fopen(info->src_file,"r");
	if(info->str_edit != NULL)
		return l_true;
	else
		return l_false;
}
Status check_operator(char *opt)                                                        //check the operator using array of string
{

	char oper[60][10]={"->","++","--","++","--",">>","<<","<<=",">>=",
			   "==","!=","&&","||","?:","+=","-=","{","}","[","]",
			   ".","!","~","*","&","*","%","/","+","-","&","=","^",
			   ",",";","*=","/=","%=","<<=",">>=","&=","^=","|="};
	for(int i=0;i<60;i++)
	{
		if(strcmp(opt,oper[i])==0)
		{
			printf("Operator      :    %s\n",opt);
			return l_true;
		}
	}
	return l_false;
}
Status check_keyword(char *str)                                                 //check the keyword using const char or we use array of string
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
Status lexcial_analyser(strinfo *info)                             //function to get a character from file
{
	char st;
	int i=0,j=0,k=0,l=0,m=0;
	int flag=0;
	char str[30];
	char n[20];
	char con[20];
	char hd[20];
	char lt[50];
	while((st=fgetc(info->str_edit))!=-1)                                     //get a character from file using fgetc to EOF
	{
		if(isalpha(st))                                                  //if char is atoz
		  {
			  str[i++]=st;                                           //store first letter in string      
			  while(isalpha(st=fgetc(info->str_edit)))               //run a loop to get a characters
			  {
				        str[i++]=st;                             // store in string
			  }
			  str[i]='\0';
			  if(strcmp(str,"sizeof")==0)
			  {
				  printf("Operator      :    %s\n",str);         //check sizeof
			  }
			  else
			  {
				  if(check_keyword(str)==l_true)                //check the keyword
				  {
					  printf("Keyword       :    %s\n",str);
				  }
				  else if(st=='(' || st=='_')                   //if character start from (,),_
				  {
					  printf("Indetifier    :    %s\n",str);
				  }
				  else
				  {
					  printf("variable      :    %s\n",str);
				  }
			  }
			  i=0;
			  fseek(info->str_edit, -1, SEEK_CUR);                       //now st=( so go one cursor back to check the char
		  }
	      else if(ispunct(st))                                                  //check not a char not a digit
		  {
		         if (st=='#')                                               //char start with # is a preprosser
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
			 else if (st==')'|| st == '(')                             //else strat with " it is a literal ex.inside a printf
			 {
				 printf("Operator      :     %c\n",st);
				 if((st=getc(info->str_edit))=='"')
				 {
					 lt[m++]=st;                                 
					 while((st=getc(info->str_edit))!='"')
					 {
						 lt[m++]=st;
					 }
					 lt[m++]='"',lt[m]='\0';                   //store " to " in lt string
					 m=0;
			                 fseek(info->str_edit,1,SEEK_CUR);         //now st=" one step back
					 printf("Literal       :    %s\n",lt);
				 }
			         fseek(info->str_edit,-1,SEEK_CUR);                //if fget not equal to " one step back
			 }
			  else                                                    
			  {
			  n[j++]=st;                                              //check operation

			  while(ispunct(st=fgetc(info->str_edit)))
			  {
				  n[j++]=st;
			  }
			  n[j]='\0';
			  check_operator(n);
			  j=0;
			  fseek(info->str_edit, -1, SEEK_CUR);
			  }
		  }
	      else if(isdigit(st))                                               //check digit
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
	return l_true;

}
Status start_process(strinfo *info)                                             //start process 
{
	printf("Parsing    :    %s     :    Started \n",info->src_file);
	if(lexcial_analyser(info)==l_true)
	{
		return l_true;
	}
		
}
        
