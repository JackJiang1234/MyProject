/*************************************************************************
	> File Name: main.c
	> Author: jackjiang
	> Mail: jjy_8888.com 
	> Created Time: Sat 06 Jun 2015 01:27:01 AM EDT
 ************************************************************************/

#include<stdio.h>
#include "observer.h"
#include "subject.h"
#include "mouse.h"
#include "master.h"
#include "cat.h"

int main(void)
{
	Subject *cat = cat_create();
	Observer *mouse = mouse_create();
	Observer *master = master_create();
	
	subject_attach(cat, mouse);
	subject_attach(cat, master);
	subject_notify(cat, NULL);

	subject_destroy(cat);
	observer_destroy(mouse);
	observer_destroy(master);

	return 0;
}
