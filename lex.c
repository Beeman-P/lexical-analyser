#include<stdio.h>
#include "lex.h"
#include "lexical.h"

int main(int argc,char *argv[])
{
  if(argc>1)
  {
     strinfo info;
	  if(read_and_validate(argv,&info)==l_true)
	  {
		  printf("<<<<<<<    Read and validate is success    >>>>>>>>>\n");
	  }
	  else
	  {
		  printf("--------    Read and validate is failure    --------\n");
		  return 0;
	  }

	  if(open_file(&info)==l_true)
	  {
		printf("open       :    %s     :    Success\n",info.src_file);
	  }
	  else
	  {
		printf("open       :    %s     :    Failed\n",info.src_file);
		return 0;
	  }

	  if(start_process(&info)==l_true)
		  printf("Parsing    :    %s     :    Done\n",info.src_file);
	  else
         	  printf("Parsing    :    %s     :    Fail\n",info.src_file);

  }
}

