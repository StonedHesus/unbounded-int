//
// Created by Andrei-Paul Ionescu on 11/04/2022.
//

/// VERSION 0.04

// C libraries.
#include <stdio.h>
#include <stdlib.h>

// Custom libraries.
#include "input-manager.h"


#define OPTIONS_BUFFER_SIZE 1024

// Method of the library.
void add_target(command *existing_command, char *target){
    /**
     * @param existing_command; an existing command object which is going to be mutated.
     * @param target; a string object representing the target file.
     *
     * Mutate the existing_command object so that it contains the target file.
     *
     * @since 0.03
     * @version final
     * @author Andrei-Paul Ionescu
     * @location Crous cafeteria, Grands Moulines.
     */

    existing_command->target = target;
}

command new_empty_command(){
    /**
     *
     * Create a new and empty command object and return it to the caller.
     *
     * @since 0.04
     * @version final
     * @author Andrei-Paul Ionescu
     * @location Crous cafeteria, Grands Moulines.
     */

    command *new_command = malloc(sizeof(command));

    if(new_command == NULL){

        printf("\nInitialisation ERROR: There has been an error with the initialisation of the command object!\n");
        abort();
    }

    new_command->number_of_options = 0;
    new_command->options = malloc(sizeof(new_command->options) * OPTIONS_BUFFER_SIZE);

    if(new_command->options == NULL){

        printf("\nInitialisation ERROR: There has been an error with the initialisation of the command object!\n");
        abort();
    }

    return *new_command;
}
void add_option(command *existing_command, char * option){
    /**
     * @param existing_command; an existing command object whose going to be mutated.
     * @param option; a string object containing one sole option which is going to be added to the options list of
     * the existing_command object.
     *
     * This method adds a new option to the options list of the existing_command object.
     *
     * @since 0.03
     * @version final
     * @author Andrei-Paul Ionescu
     * @location Crous cafeteria, Grands Moulines.
     */

    existing_command->options[existing_command->number_of_options++] = option;
}

command new_command(const char* target){
    /**
     * @param target; a string object containing a file name.
     *
     * Create a new command object whose target file is the one passed as an argument to the function by the caller.
     *
     * @since 0.03
     * @version final
     * @author Andrei-Paul Ionescu
     * @location Crous cafeteria, Grands Moulines.
     */

    command *temporary = malloc(sizeof(command));

    if(temporary == NULL){

        printf("\nInitialisation ERROR: There has been an error with the initialisation of the command object!\n");
        abort();
    }

    temporary->target = target;
    temporary->number_of_options = 0;
    temporary->options = malloc(sizeof(temporary->options) * OPTIONS_BUFFER_SIZE);

    if(temporary->options == NULL){

        printf("\nInitialisation ERROR: There has been an error with the initialisation of the command object!\n");
        abort();
    }

    return *temporary;
}

void add_process(round_robin *current_roundRobin, command new_process){
    /**
     * @param current_roundRobin; the current round_robin object.
     * @param new_process; a new process which is bound to added in the round_robin.
     *
     * Add a new position inside the execution chain of the circular list which represents the round_robin object.
     *(this method is essentially an add_back function, since we traverse the round_robin clockwise <right to left>).
     * @since 0.02
     * @version final
     * @author Andrei-Paul Ionescu
     * @location RER B, on the way home.
     */

    if(current_roundRobin->next == NULL && current_roundRobin->previous == NULL){
        // The Round Robin is empty.

        current_roundRobin->command = &new_process;
        current_roundRobin->next = current_roundRobin->previous = current_roundRobin;
    } else{
        // The Round Robin is not empty and thus we not to place the current process at the desired position,
        // for this implementation each new process will be added to the left, so as to save with the insertion
        // operation.

        // TODO: FIX THE INSERTION PROBLEM.

        round_robin temporary = create_round_robin();
        temporary.command = &new_process;

        current_roundRobin->previous->next = &temporary;
        temporary.previous = current_roundRobin->previous;

        temporary.next     =  current_roundRobin;
        current_roundRobin->previous = &temporary;

    }
}

round_robin create_round_robin(){
    /**
     * Create a new round_robin object and return it to the caller.
     *
     * @since 0.02
     * @version final
     * @author Andrei-Paul Ionescu
     * @location: RER B, on the way home.
     */

    round_robin *roundRobin = malloc(sizeof(roundRobin));

    if(roundRobin == NULL){

        printf("\nInitialisation ERROR: There was an error with the creation of the round_robin object!\n");
        abort();
    }

    roundRobin->next = malloc(sizeof(roundRobin));

    if(roundRobin->next == NULL){

        printf("\nInitialisation ERROR: There was an error with the creation of the round_robin object!\n");
        abort();
    }

    roundRobin->previous = malloc(sizeof(roundRobin));

    if(roundRobin->previous == NULL){

        printf("\nInitialisation ERROR: There was an error with the creation of the round_robin object!\n");
        abort();
    }

    roundRobin->next = NULL;
    roundRobin->previous = NULL;

    roundRobin->command = malloc(sizeof(command));

    if(roundRobin->command == NULL){

        printf("\nInitialisation ERROR: There was an error with the creation of the round_robin object!\n");
        abort();
    }

    return *roundRobin;
}

void print_round_robin(round_robin roundRobin){

    round_robin *current = &roundRobin;

    do{

        print_command(*current->command);
        current = current->next;
    }while(current != &roundRobin);
}

void print_command(command command){

    printf("The target file is: %s \n\t The options given to the target are: ", command.target);

    for(int i = 0 ; i < command.number_of_options; ++i){

        printf("%s ", command.options[i]);
    }
    printf("\n");
}




