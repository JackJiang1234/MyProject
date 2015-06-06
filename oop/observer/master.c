/*************************************************************************
	> File Name: master.c
	> Author: jackjiang
	> Mail: jjy_8888.com 
	> Created Time: Sat 06 Jun 2015 12:59:39 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "master.h"

static void master_notify(Observer *thiz, void *ctx)
{
	printf("master wake up.\n");
}

static void master_destroy(Observer *thiz)
{
	free(thiz);
}

Observer* master_create(void)
{
	Observer *thiz = (Observer *)malloc(sizeof(Observer));
	if (thiz != NULL)
	{
		thiz->notify = master_notify;
		thiz->destroy = master_destroy;
	}

	return thiz;
}
