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

#include "todo.h" //Todo list abstraction

enum Actions
{
        NO_ACTION,
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

/**
 * Parses arguments passed to the program and returns a populated Parsed_Args
 * struct and a corresponding Action to do.
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
        while (  ( opt = getopt( argc, argv, "l:i:aRr:vp:h" ) ) != -1  )
        {
                switch( opt )
                {
                case 'h':
                        if ( action == NO_ACTION )
                                action = HELP;
                        break;
                case 'l': /* select list */
                        args->list_name = optarg;
                        #ifdef DEBUG
                        fprintf( stderr, "Selected list: %s\n", optarg );
                        #endif
                        break;
                case 'i': /* selected item */
                        args->item_name = optarg;
                        #ifdef DEBUG
                        fprintf( stderr, "Selected item: %s\n", optarg );
                        #endif
                        break;
                }
        }
}

int main( int argc, char* argv[] )
{
        
}
