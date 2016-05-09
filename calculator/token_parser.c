/*************************************************************************
	> File Name: token_parser.c
	> Author: jackjiang
	> Mail: jjy_8888.com 
	> Created Time: Mon 09 May 2016 11:32:34 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "token_parser.h"
#include "../typedef.h"

#define LINE_MAX_CHARS 1000

struct _TokenParser
{
	char *line;
	int position;
};


TokenParser* token_parser_create()
{
	TokenParser *thiz = (TokenParser *)malloc(sizeof(TokenParser));
	if (thiz != NULL)
	{
		thiz->line = NULL;
		thiz->position = 0;
	}
	return thiz;
}

void token_parser_destroy(TokenParser *thiz)
{
	if(thiz != NULL)
	{
		if (thiz->line != NULL)
		{
			free(thiz->line);
		}
		free(thiz);
	}
}

void token_parser_set_line(TokenParser *thiz, char *line)
{
	return_if_fail(thiz != NULL);
	thiz->line = malloc(strlen(line) + 1);
	strncpy(thiz->line, line, LINE_MAX_CHARS)
	thiz->position = 0;
}

static void token_parser_number(TokenParser *thiz, Token *pt)
{
	int ch;
	int pt_pos = 0;
	while(1)
	{
		ch = thiz->line[thiz->position];
		if (isdigit(ch) || ch == '.')
		{
			if (pt_pos < MAX_TOKEN_LEN)
			{
				pt->str[pt_pos] = ch;
				pt_pos++;	
			}
			thiz->position++;
		}
		else 
		{
			sscanf(pt->str, "%lf", &pt->value);
			thiz->position--;	
			return;
		}
	}
}

static void token_parser_operator(TokenParser *thiz, Token *pt)
{

}

void token_parser_get_token(TokenParser *thiz, Token *pt)
{
	return_if_fail(thiz != NULL && pt != NULL);
	
	int ch = thiz->line[thiz->position];
	if (isdigit(ch))
	{
		token_parser_number(thiz, pt);
	}
	else if (ch == NUL)
	{
		pt->kind = END_TOKEN;
	}
	else 
	{
		token_parser_operator(thiz, pt);	
	}
}

