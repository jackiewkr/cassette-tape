/**
 * CASSETTE-TAPE
 * ------------
 * A simple command-line todo list application, aiming to emulate and expand on
 * the simplicity of Aeriform's Tape.
 *
 * By Jacqueline W.
 * Licensed under the Mozilla MPL v2 license.
 **/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "todo.h" //Todo list abstraction

enum Actions
{
        NO_ACTION = 0,
        ADD_LIST,
        REMOVE_LIST,
        RENAME_LIST,
        SHOW_LIST,

        ADD_ITEM,
        REMOVE_ITEM,
        RENAME_ITEM,
        REPRIO_ITEM,
        HELP
};

struct Parsed_Args
{
        char* list_name;
        char* item_name;
        char* buf; /* general use char buffer */
        int priority;
};

#ifdef DEBUG
static char* action_to_str( int action )
{
        char* buf;
        switch ( action )
        {
        default:
        case 0:
                buf = "NO_ACTION";
                break;
        case 1:
                buf = "ADD_LIST";
                break;
        case 2:
                buf = "REMOVE_LIST";
                break;
        case 3:
                buf = "RENAME_LIST";
                break;
        case 4:
                buf = "SHOW_LIST";
                break;
        case 5:
                buf = "ADD_ITEM";
                break;
        case 6:
                buf = "REMOVE_ITEM";
                break;
        case 7:
                buf = "RENAME_ITEM";
                break;
        case 8:
                buf = "REPRIO_ITEM";
                break;
        case 9:
                buf = "HELP";
                break;
        }
        return buf;
}
#endif

/**
 * Parses arguments passed to the program and returns a populated Parsed_Args
 * struct and a corresponding Action to do.
 * This function does not care if the arguments are valid actions to do.
 *
 * Arguments:
 *  - -l <foo> : selected list
         -a : add list called <foo>
         -R : remove list called <foo>
         -r <bar> : rename list <foo> to <bar>
         -v : view list <foo>
 *  - -i <pchoo> : selected item in list
         -a : add item <pchoo> to list <foo>
         -R : remove item <pchoo> from <foo>
         -r <bar> : rename item <pchoo> to <bar>
         -p <prio> : changes priority of item <pchoo>
 * - -h : shows help menu
 **/
int parse_arguments( struct Parsed_Args* args, int argc, char* argv[] )
{
        int opt;
        int action = NO_ACTION;
        unsigned int has_list, has_item = 0;
        
        while (  ( opt = getopt( argc, argv, "l:i:aRr:vp:h" ) ) != -1  )
        {
                switch( opt )
                {
                case 'h':
                        action = HELP;
                        break;
                case 'l': /* select list */
                        args->list_name = optarg;
                        has_list = 1;
                        #ifdef DEBUG
                        fprintf( stderr, "Selected list: %s\n", optarg );
                        #endif
                        break;
                case 'i': /* selected item */
                        args->item_name = optarg;
                        has_item = 1;
                        #ifdef DEBUG
                        fprintf( stderr, "Selected item: %s\n", optarg );
                        #endif
                        break;
                /* Arguments dependant on what is selected */
                case 'v': /* view list */
                        if ( action == NO_ACTION && has_list )
                                action = SHOW_LIST;
                        break;
                case 'p':
                        if ( action == NO_ACTION && has_list && has_item )
                        {
                                action = REPRIO_ITEM;
                                //TODO: guard against non-integer priorities
                                args->priority = atoi(optarg);
                                #ifdef DEBUG
                                fprintf( stderr, "Priority: %i\n",
                                         args->priority );
                                #endif
                        }
                        break;
                case 'a': /* add list or item */
                        /* if both action and item, add item */
                        if ( has_list && has_item && action == NO_ACTION )
                                action = ADD_ITEM;
                        /* if only has list, add list */
                        else if ( has_list && action == NO_ACTION )
                                action = ADD_LIST;
                        break;
                case 'R': /* remove item or list */
                        /* if both action and item, remove item */
                        if ( has_list && has_item && action == NO_ACTION )
                                action = REMOVE_ITEM;
                        /* if only has list, remove list */
                        else if ( has_list && action == NO_ACTION )
                                action = REMOVE_LIST;
                        break;
                case 'r': /* rename item or list */
                        /* if both action and item, rename item */
                        if ( has_list && has_item && action == NO_ACTION )
                        {
                                action = RENAME_ITEM;
                                args->buf = optarg;
                                #ifdef DEBUG
                                fprintf( stderr, "Buf: %s\n", args->buf );
                                #endif
                        }
                        /* if only has list, add list */
                        else if ( has_list && action == NO_ACTION )
                        {
                                action = RENAME_LIST;
                                args->buf = optarg;
                                #ifdef DEBUG
                                fprintf( stderr, "Buf: %s\n", args->buf );
                                #endif
                        }
                        break;
                default:
                        break;
                }
        }
        #ifdef DEBUG
        fprintf( stderr, "Selected action: %s\n", action_to_str( action ) );
        #endif

        if ( action == NO_ACTION )
                action = HELP;
        
        return action;
}

int main( int argc, char* argv[] )
{
        struct Parsed_Args args;
        int action = parse_arguments( &args, argc, argv );

        switch ( action )
        {
        case HELP:
                printf("HELP!!!!!!!!!!!!!!!!!");
                break;
        default:
                break;
        }

        return 0;
}
