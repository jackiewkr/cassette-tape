#ifndef __TODO_H
#define __TODO_H

/* If adding any new priorities, add between P_DEFAULT and P_DONE
 * or i_setPrio() will fail
 * Priorities start at 1 as failed atoi() calls give 0 as output */
enum Priority
{
        P_DEFAULT = 1,
        P_PRIORITY,
        P_WORKING,
        P_SUBMITTED,
        P_APPROVED,
        P_DONE
};

struct Item;
void i_setPrio( struct Item*, int priority );
void i_setName( struct Item*, char* buf, int buf_sz );

/* Given a null pointer to a string, returns the size of the name, and copies
 * the string to *buf */
int i_getName( struct Item*, char* buf );

struct List;
struct List* l_init( char* name, int name_sz );
void l_free( struct List* );
void l_add( struct List*, char* item_name, int n_sz, int priority );
struct Item* l_get( struct List* l, int index );


#endif //__TODO_H
