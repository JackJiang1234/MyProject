/*************************************************************************
	> File Name: parse_token.c
	> Author: jack
	> Mail: jjy_8888@163.com 
	> Brief: 
	> Created Time: Sat 26 Mar 2016 11:05:20 PM EDT
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parse_token.h"

int parse_token(const char *text, const char *delims, OnTokenFunc on_token, void *ctx)
{
	return_val_if_fail((text != NULL) && (delims != NULL), 0);

	enum _State 
	{
		STAT_INIT,
		STAT_IN,
		STAT_OUT
	}state = STAT_INIT;

	char *copy_text = (char *)malloc(strlen(text) + 1);
	return_val_if_fail(copy_text != NULL, 0);
	strcpy(copy_text, text);

	char *p = copy_text;
	char *token = copy_text;
	int count = 0;
	while(*p != '\0')
	{
		switch(state)
		{
			case STAT_INIT:
			case STAT_OUT:
			{
				if (strchr(delims, *p) == NULL)
				{	
					state = STAT_IN;
					token = p;
				}
			}
			break;
			case STAT_IN:
			{
				if (strchr(delims, *p) != NULL)
				{
					state = STAT_OUT;
					*p = '\0';
					if (on_token != NULL)
					{
						on_token(ctx, count++, token);
					}
				}
			}
			break;
			default:
			break;
		}
		p++;
	}

	if (state == STAT_IN)
	{
		on_token(ctx, count++, token);
	}
	//on_token(ctx, -1, NULL);

	free(copy_text);

	return count;
}

#ifdef PARSE_TOKEN_TEST

void print_token(void *ctx, int index, const char *token)
{
	printf("the %d of token is: *%s*\n", index, token);
}

void test_parse_str(const char *str, const char* delims)
{
	printf("The test string: *%s*\n", str);
	parse_token(str, delims, print_token, NULL);
}

int main(void)
{
	test_parse_str("aWord", "&");
	test_parse_str("&aWord", "&");
	test_parse_str("aWord&", "&");
	test_parse_str("&aWord&", "&");
	test_parse_str("country=china&company=google", "&");

	return 0; 
}

#endif
