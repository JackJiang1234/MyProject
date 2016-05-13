/*************************************************************************
	> File Name: expr_parser.c
	> Author: jack
	> Mail: jjy_8888@163.com 
	> Brief: 
	> Created Time: Fri 13 May 2016 12:56:30 PM EDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../typedef.h"
#include "token_parser.h"
#include "expr_parser.h"

struct _ExprParser
{
	int is_set_ahead_token;
	Token* ahead_token;
	TokenParser* token_parser;
};

ExprParser* expr_parser_create()
{
	ExprParser* thiz = malloc(sizeof(ExprParser));
	if (thiz != NULL)
	{
		thiz->is_set_ahead_token = 0;
		thiz->ahead_token = NULL;
		thiz->token_parser = malloc(sizeof(TokenParser));
	}
	return thiz;
}

void expr_parser_set_line(ExprParser* thiz, char* line)
{
	return_if_fail(thiz != NULL && line != NULL);	

	token_parser_set_line(thiz->token_parser, line);
}

double expr_parser_parse(ExprParser* thiz)
{
	return_val_if_fail(thiz != NULL && thiz->line != NULL && thiz->token_parser != NULL, 0f);
	
	
}
void expr_parser_destroy(ExprParser* thiz)
{
	if (thiz != NULL)
	{
		if (thiz->token_parser != NULL)
		{
			token_parser_destroy(thiz->token_parser);
		}
		free(thiz);
	}
}

#endif

