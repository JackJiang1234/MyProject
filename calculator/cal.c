/*************************************************************************
	> File Name: cal.c
	> Author: jack
	> Mail: jjy_8888@163.com 
	> Brief: 
	> Created Time: Fri 13 May 2016 07:16:04 AM EDT
 ************************************************************************/
#include<stdio.h>
#include "expr_parser.h"
#include "cal.h"
#define LINE_BUF_SIZE 100

double parser_line(char *line)
{
	ExprParser* thiz = expr_parser_create();	
	expr_parser_set_line(thiz, line);
	double ret = expr_parser_parse(thiz);
	expr_parser_destroy(thiz);

	return ret;
}

int main(void)
{
	char line[LINE_BUF_SIZE];

	while(fgets(line, LINE_BUF_SIZE, stdin) != NULL)
	{
		printf(">>%f\n", parser_line(line));
	}

	return 0;
}


