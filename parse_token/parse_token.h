/*************************************************************************
	> File Name: parse_token.h
	> Author: jack
	> Mail: jjy_8888@163.com 
	> Brief: 
	> Created Time: Sat 26 Mar 2016 10:58:12 PM EDT
 ************************************************************************/
#ifndef _PARSE_TOKEN_H 
#define _PARSE_TOKEN_H

#define return_if_fail(p) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
			__func__, __LINE__); return;}
#define return_val_if_fail(p, ret) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
			__func__, __LINE__); return (ret);}

#define SAFE_FREE(p) if(p != NULL){free(p); p = NULL;}

typedef void (*OnTokenFunc)(void* ctx, int index, const char* token);
int parse_token(const char *text, const char *delims, OnTokenFunc on_token, void *ctx);

#endif

