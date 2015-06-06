/*************************************************************************
	> File Name: cat.c
	> Author: jackjiang
	> Mail: jjy_8888.com 
	> Created Time: Fri 05 Jun 2015 06:51:58 PM EDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "subject.h"

typedef struct _ObNode
{
	Observer *ob;
	struct _ObNode *next;
}ObNode;

typedef struct _PrivInfo
{
	ObNode *ob_node;
}PrivInfo;

static void cat_notify(Subject *thiz, void *ctx)
{
	printf("cat meow...\n");

	PrivInfo *priv = (PrivInfo *)thiz->priv;
	for(ObNode *n = priv->ob_node; n != NULL; n = n->next)
	{
		observer_notify(n->ob, ctx);
	}
}

static void cat_attach(Subject *thiz, Observer *op)
{
	ObNode *new = (ObNode *)malloc(sizeof(ObNode));
	new->ob = op;
	new->next = NULL;

	PrivInfo *priv = (PrivInfo *)thiz->priv;
	if (priv->ob_node == NULL)
	{
		priv->ob_node = new;
	}
	else 
	{
		ObNode *last = priv->ob_node;
		while(last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
}

static void cat_destroy(Subject *thiz)
{
	PrivInfo *priv = (PrivInfo *)thiz->priv;
	ObNode *cur = priv->ob_node;
	ObNode *next;

	while(cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(thiz);
}

Subject* cat_create(void)
{
	 Subject *thiz = (Subject *)malloc(sizeof(Subject) + sizeof(PrivInfo));
	 if (thiz != NULL)
	 {
		PrivInfo *priv = (PrivInfo *)thiz->priv;
		priv->ob_node = NULL;

		thiz->notify = cat_notify;
		thiz->attach = cat_attach;
		thiz->destroy = cat_destroy;
	 }

	 return thiz;
}

