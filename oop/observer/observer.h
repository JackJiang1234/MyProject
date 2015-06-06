/*************************************************************************
	> File Name: observer.h
	> Author: jackjiang
	> Mail: jjy_8888.com 
	> Created Time: Fri 05 Jun 2015 06:27:21 PM EDT
	> Desc:the observer interface define
 ************************************************************************/

#include <stdio.h>
#ifndef OBSERVER_H
#define OBSERVER_H

struct _Observer;
typedef struct _Observer Observer;

typedef void (*ObserverNotifyFunc)(Observer *thiz, void *ctx);
typedef void (*ObserverDestroyFunc)(Observer *thiz);

struct _Observer
{
	ObserverNotifyFunc notify;
	ObserverDestroyFunc destroy;

	char priv[0];
};

static inline void observer_notify(Observer *thiz, void *ctx)
{
	thiz->notify(thiz, ctx);
}

static inline void observer_destroy(Observer *thiz)
{
	thiz->destroy(thiz);	
}

#endif
