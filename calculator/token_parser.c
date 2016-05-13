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

typedef struct _OperatorInfo
{
	int op;
	TokenKind kind;	
		
}OperatorInfo;

static OperatorInfo opInfos[] = 
{
	{ .op = '+', .kind = PLUS },
	{ .op = '-', .kind = MINUS },
	{ .op = '*', .kind = MUL },
	{ .op = '/', .kind = DIV }
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
		free(thiz);
	}
}

void token_parser_set_line(TokenParser *thiz, char *line)
{
	return_if_fail(thiz != NULL);

	thiz->line = line;
	thiz->position = 0;
}

static void token_parser_number(TokenParser *thiz, Token *pt)
{
	int ch;
	int pt_pos = 0;
	while(1)
	{
		ch = thiz->line[thiz->position];
		if (isdigit(ch) || (ch == '.'))
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
			pt->str[pt_pos] = NUL;
			sscanf(pt->str, "%lf", &pt->value);
			pt->kind = NUMBER;

			return;
		}
	}
}

static void token_parser_operator(TokenParser *thiz, Token *pt)
{
	int ch = thiz->line[thiz->position++];
	for(int i = 0; i < ARRAY_LEN(opInfos); i++)
	{
		if(opInfos[i].op == ch)
		{
			pt->kind = opInfos[i].kind;
			pt->str[0] = ch;
			pt->str[1] = NUL;
			pt->value = 0.0;

			return;
		}
	}

	pt->kind = BAD_TOKEN;
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

#ifdef TOKEN_PARSER_TEST

static void token_foreach(TokenParser *thiz)
{

	printf("parser:%s\n", thiz->line);

	Token t;
	token_parser_get_token(thiz, &t);

	while((t.kind != END_TOKEN) && (t.kind != BAD_TOKEN))
	{
		if (t.kind == NUMBER)
		{
			printf("%f", t.value);
		}
		else 
		{
			printf("%c", t.str[0]);
		}
		
		token_parser_get_token(thiz, &t);
	}

	printf("\n");
}

int main(void)
{
	TokenParser *thiz = token_parser_create();

	token_parser_set_line(thiz, "5+6");
	token_foreach(thiz);

	token_parser_set_line(thiz, "5.6+6");
	token_foreach(thiz);

	token_parser_set_line(thiz, "5.2+6.6");
	token_foreach(thiz);

	token_parser_set_line(thiz, "5.2+6.6*100/5");
	token_foreach(thiz);

	token_parser_set_line(thiz, "5.2*6.6/100");
	token_foreach(thiz);

	token_parser_destroy(thiz);
}

#endif
