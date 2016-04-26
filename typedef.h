/*************************************************************************
	> File Name:typedef.h 
	> Author: jack
	> Mail: jjy_8888@163.com 
	> Brief: 
	> Created Time: Sat 26 Mar 2016 10:58:12 PM EDT
 ************************************************************************/
#ifndef TYPEDEH_H 
#define TYPEDEF_H

#define NUL '\0'

typedef enum _Ret
{
	RET_OK,
	RET_OOM,
	RET_STOP,
	RET_INVALID_PARAMS,
	RET_FAIL
}Ret;


#define return_if_fail(p) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
			__func__, __LINE__); return;}
#define return_val_if_fail(p, ret) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
			__func__, __LINE__); return (ret);}

#endif

