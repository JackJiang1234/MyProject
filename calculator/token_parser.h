/*************************************************************************
	> File Name: token_parser.h
	> Author: jack
	> Mail: jjy_8888@163.com 
	> Brief: 
	> Created Time: Wed 27 Apr 2016 01:49:37 AM EDT
 ************************************************************************/
#ifndef TOKEN_PARSER_H
#define TOKEN_PARSER_H

struct _TokenParser;
typedef struct _TokenParser TokenParser;

typedef enum 
{
	NUMBER,
	PLUS,
	MINUS,
	MUL,
	DIV
}TokenKind;

typedef struct _Token 
{
	TokenKind kind;
	double valuel;
	char *str;
}Token;

TokenParser* token_parser_create();
void token_parser_destroy(TokenParser *thiz);
void token_parser_set_line(TokenParser *thiz, char *line);
void token_parser_get_token(Token *tp);

#endif

