/*************************************************************************
	> File Name: mouse.c
	> Author: jackjiang
	> Mail: jjy_8888.com 
	> Created Time: Sat 06 Jun 2015 12:59:39 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "mouse.h"

static void mouse_notify(Observer *thiz, void *ctx)
{
	printf("get message, mouse running...\n");
}

static void mouse_destroy(Observer *thiz)
{
	free(thiz);
}

Observer* mouse_create(void)
{
	Observer *thiz = (Observer *)malloc(sizeof(Observer));
	if (thiz != NULL)
	{
		thiz->notify = mouse_notify;
		thiz->destroy = mouse_destroy;
	}

	return thiz;
}
