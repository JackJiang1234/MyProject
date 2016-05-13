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
	Token ahead_token;
	TokenParser* token_parser;
};

/*
 *	expression: term
 *				| expression + term
 *				| expression - term
 *	term: primary_expression 
 *		  | term * primary_expression
 *		  | term / primary_expression 
 *  primary_expression: number
 *
 * */

static void expr_parser_get_token(ExprParser* thiz, Token* pt)
{
	if (thiz->is_set_ahead_token)
	{
		thiz->is_set_ahead_token = 0;
		*pt = thiz->ahead_token;
	}
	else 
	{
		token_parser_get_token(thiz->token_parser, pt);
	}
}

static void expr_parser_unget_token(ExprParser* thiz, Token* pt)
{
	thiz->is_set_ahead_token = 1;
	thiz->ahead_token = *pt; 
}

static double expr_parser_primary_expression(ExprParser* thiz)
{
	Token t;
	expr_parser_get_token(thiz, &t);
	if (t.kind == NUMBER)
	{
		return t.value;
	}
	else 
	{
		fprintf(stderr, "bad format, %s\n", t.str);
		exit(1);
		return 0;
	}
}

static double expr_parser_term(ExprParser* thiz)
{
	double v1 = expr_parser_primary_expression(thiz);	

	while(1)
	{
		Token t;
		expr_parser_get_token(thiz, &t);

		if (t.kind == MUL || t.kind == DIV)
		{
			double v2 = expr_parser_primary_expression(thiz);
			if (t.kind == MUL)
			{
				v1 *= v2;
			}
			else 
			{
				v1 /= v2;
			}
		}
		else 
		{
			expr_parser_unget_token(thiz, &t);
			break;
		}
	}

	return v1;
}

static double expr_parser_expression(ExprParser *thiz)
{
	double v1 = expr_parser_term(thiz);	
	
	while(1)
	{
		Token t;	
		expr_parser_get_token(thiz, &t); 
		if (t.kind == PLUS || t.kind == MINUS)
		{
			double v2 = expr_parser_term(thiz);
			if (t.kind == PLUS)
			{
				v1 += v2;
			}
			else 
			{
				v1 -= v2;
			}
		}
		else 
		{
			expr_parser_unget_token(thiz, &t);
			break;
		}
	}

	return v1;
}


ExprParser* expr_parser_create()
{
	ExprParser* thiz = malloc(sizeof(ExprParser));
	if (thiz != NULL)
	{
		thiz->is_set_ahead_token = 0;
		thiz->token_parser = token_parser_create();
	}
	return thiz;
}

void expr_parser_set_line(ExprParser* thiz, char* line)
{
	return_if_fail(thiz != NULL && line != NULL);	

	thiz->is_set_ahead_token = 0;
	token_parser_set_line(thiz->token_parser, line);
}

double expr_parser_parse(ExprParser* thiz)
{
	return_val_if_fail(thiz != NULL && thiz->token_parser != NULL, 0.0l);
	
	return expr_parser_expression(thiz);	
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

#ifdef EXPR_PARSER_TEST

int main(void)
{
	ExprParser* thiz = expr_parser_create();	

	char *arr[] = 
	{
		"5+100-22",
		"5+6*2",
		"5*6*2",
		"6-3-4",
		"5*6/2"

	};

	for(int i = 0; i < ARRAY_LEN(arr); i++)
	{
		expr_parser_set_line(thiz, arr[i]);
		printf("%s=%f\n", arr[i], expr_parser_parse(thiz));
	}

	expr_parser_destroy(thiz);
}


#endif
