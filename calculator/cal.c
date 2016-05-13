/*************************************************************************
	> File Name: cal.c
	> Author: jack
	> Mail: jjy_8888@163.com 
	> Brief: 
	> Created Time: Fri 13 May 2016 07:16:04 AM EDT
 ************************************************************************/
#include<stdio.h>
#include "token_parser.h"
#include "cal.h"

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

static double parser_primary_expression(TokenParser *thiz)
{
	Token t = token_parser_get_token(thiz, &t);
	if (t.kind == NUMBER)
	{
		return t.value;
	}
	else 
	{
		fprintf(stderr, "bad format\n");
		exit(1);
		return 0;
	}
}

static double parser_term(TokenParser *thiz)
{
	double v1 = parser_primary_expression(thiz);	

	while(1)
	{
		Token t;
		token_parser_get_token(thiz, &t);

		if (t.kind == MUL || t.kind == DIV)
		{
			double v2 = parser_primary_expression(thiz);
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
			//unget token
			break;
		}
	}
}

static double parser_expression(TokenParser *thiz)
{
	double v1 = parser_term(thiz);	
	
	while(1)
	{
		Token t;	
		token_parser_get_token(thiz, &t); 

		if (t.kind == PLUS || t.kind == MINUS)
		{
			double v2 = parser_term(thiz);
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
			break;
		}
	}

	return v1;
}

double parser_line(char *line)
{
	
}

