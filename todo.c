/**
 * todo.c
 * ======
 * This file contains an ADT for a todo list.
 **/

#include "todo.h"

#include <stdlib.h>
#include <string.h>

struct Item
{
        char* name;
        int n_sz;

        int priority;
};

struct Item* i_init( char* name, int n_sz )
{
        struct Item* i = malloc( sizeof(struct Item) );

        i->name = malloc( n_sz );
        i->n_sz = n_sz;
        memcpy( i->name, name, n_sz );

        i->priority = P_DEFAULT;

        return i;
}

void i_free( struct Item* i )
{
        if ( i == NULL )
                return;

        free( i->name );
        free( i );
}

void i_setPrio( struct Item* i, int prio )
{
        if ( prio < P_DEFAULT || prio > P_DONE )
                return;
        
        i->priority = prio;
}

void i_setName( struct Item* i, char* name, int n_sz )
{
        if ( name == NULL )
                return;

        free( i->name );
        i->n_sz = n_sz;
        memcpy( i->name, name, n_sz );
}

int i_getName( struct Item* i, char* buf )
{
        if ( buf != NULL )
                free( buf );

        memcpy( buf, i->name, i->n_sz );

        return i->n_sz;
}

int i_getPrio( struct Item* i )
{
        return i->priority;
}

struct List
{
        char* name;
        int n_sz;

        struct Item** list;
        int l_sz;
};

struct List* l_init( char* name, int n_sz )
{
        struct List* l = malloc( sizeof(struct List) );

        l->l_sz = 0;
        l->list = NULL;

        l->name = malloc( n_sz );
        l->n_sz = n_sz;
        memcpy( l->name, name, n_sz );

        return l;
}

void l_free( struct List* l )
{
        if ( l == NULL )
                return;

        if ( l->l_sz != 0 )
        {
                for ( int i = 0; i < l->l_sz; i++ )
                {
                        i_free( l->list[i] );
                }
        }
        
        free( l->name );
        free( l );
}

void l_add( struct List* l, char* name, int n_sz, int priority )
{
        l->list = realloc( l->list, sizeof(struct Item*) * ++l->l_sz );
        l->list[l->l_sz - 1] = i_init( name, n_sz );
        i_setPrio( l->list[l->l_sz - 1], priority );
}

struct Item* l_get( struct List* l, int index )
{
        if ( index >= l->l_sz || index < 0 )
                return NULL;

        return l->list[index];
}
