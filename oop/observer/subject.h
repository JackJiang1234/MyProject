/*************************************************************************
	> File Name: subject.h
	> Author: jackjiang
	> Mail: jjy_8888.com 
	> Created Time: Fri 05 Jun 2015 06:35:10 PM EDT
 ************************************************************************/
#ifndef SUBJECT_H
#define SUBJECT_H
#include "observer.h"

struct _Subject;
typedef struct _Subject Subject;

typedef void (*SubjectNotifyObserversFunc)(Subject *thiz, void *ctx);
typedef void (*SubjectAttachFunc)(Subject *thiz, Observer *ob);
typedef void (*SubjectDestroyFunc)(Subject *thiz);

struct _Subject
{
	SubjectNotifyObserversFunc notify;
	SubjectAttachFunc attach;
	SubjectDestroyFunc destroy;

	char priv[0];
};

static inline void subject_notify(Subject *thiz, void *ctx)
{
	thiz->notify(thiz, ctx);
}

static inline void subject_attach(Subject *thiz, Observer *ob)
{
	thiz->attach(thiz, ob);
}

static inline void subject_destroy(Subject *thiz)
{
	thiz->destroy(thiz);
}

#endif
