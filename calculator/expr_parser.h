/*************************************************************************
	> File Name: expr_parser.h
	> Author: jack
	> Mail: jjy_8888@163.com 
	> Brief: 
	> Created Time: Fri 13 May 2016 12:56:30 PM EDT
 ************************************************************************/
#ifndef EXPR_PARSER_H
#define EXPR_PARSER_H

struct _ExprParser;
typedef _ExprParser ExprParser;

ExprParser* expr_parser_create();
void expr_parser_set_line(ExprParser* thiz, char* line);
double expr_parser_parse(ExprParser* thiz);
void expr_parser_destroy(ExprParser* thiz);

#endif

