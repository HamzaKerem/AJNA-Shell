#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "vars.h"
#include "builtin_cmds.h"

#define SH_NAME "AJNA"
#define BUILTIN_COUNT 5

int global_var_count = -6;

int
execute_stdin(char * assignment_field[], int assignment_field_count, char * var_properties[]){

    static int var_count = -3, i;

    char * builtin_cmds[] = {"exit", "echo", "help", "varinfo", "syntax"};
    int builtin_cmd_count = 4, selected_builtin_cmd = -1;

    // check if builtin (chdir, syntax, help, varinfo...)
    for (i = 0; i < BUILTIN_COUNT; i++){
        if (strcmp(assignment_field[0], builtin_cmds[i]) == 0)
            selected_builtin_cmd = i;
    }
    if (selected_builtin_cmd > -1)
        execute_builtin_cmd(assignment_field, assignment_field_count, var_properties, var_count, selected_builtin_cmd);

    // Check if assignment
    else if (assignment_field_count > 1 && strcmp(assignment_field[1], "=") == 0){
        var_count = assign_var(assignment_field, assignment_field_count, var_properties, var_count);
    } else{
        printf("%s: %s: command not found\n", SH_NAME, assignment_field[0]);
        return -1;
    }
    
    // Check if condition
    // if (strcmp(assignment_field[1], "==") == 0)

    // check if builtin (chdir, syntax, help, varinfo...)

    // if not check if cmd or prg from /usr/bin, and if so execute
    global_var_count = var_count;
    return 0;
}

char *
remove_quotes_from_str(char * value_of_var){

    int i = 0, j = 1;

    char * temp_str = malloc(255);
    temp_str = strdup(value_of_var);

    for (i = 0, j = 1; i < strlen(value_of_var) - 2; i++, j++){
        value_of_var[i] = temp_str[j];
    }

    free(temp_str);
    // printf("value_of_var: %s\n", value_of_var);
    return value_of_var;
}

void
check_for_expansion(char * assignment_field[], int assignment_field_count, char * var_properties[]){

    int i, j, matching_var_count = -1, quoted_str_to_expand = 1;
    char * var_to_expand = malloc(255);

    for (i = 0; i < assignment_field_count; i++){

        // check if quoted
        if ((assignment_field[i][0] == '"' && assignment_field[i][strlen(assignment_field[i]) - 1] == '"' && assignment_field[i][1] == '%' && strlen(assignment_field[i]) > 3))
            quoted_str_to_expand = 0;
        
        // Check if variable expansion 
        if ((assignment_field[i][0] == '%' && strlen(assignment_field[i]) > 1) || quoted_str_to_expand == 0){
            
            /*if (quoted_str_to_expand == 0)
                var_to_expand = remove_quotes_from_str(var_to_expand);
            */
           
            // assign field to a str without %
            for (j = 0; j < strlen(assignment_field[i]); j++){
                var_to_expand[j] = assignment_field[i][j+1];
            }
            // printf("var_to_expand: %s\n", var_to_expand);

            for (j = 0; j < global_var_count + 3; j += 3){
                
                // if it matches a var, assign it to the var's value
                if (strcmp(var_properties[j],var_to_expand) == 0)
                    matching_var_count = j;
                    
            }

            // printf("matching_var_count: %d\n\n", matching_var_count);
            if (matching_var_count > -1){
                assignment_field[i] = strdup(var_properties[matching_var_count + 2]);
            } else{
                assignment_field[i] = strdup("");
            }

        }
    }

    free(var_to_expand);
    // return assignment_field;
}

int
parse_stdin(char * stdin_str, char * var_properties[300]){

    // printf("\nstdin_str: %s\n", stdin_str);
    int temp_var = -6;
    int * var_count_ptr = &temp_var;
    int ** var_count_double_ptr = &var_count_ptr;
    int i, assignment_field_count = 0, single_argument_char_count = 0;
    short int bool_increase_field_count = 0;
    char * assignment_field[32];
    char * temp_field = malloc(255);
    char * single_argument = malloc(255);
    
    // Initialize char * s
    temp_field = strdup("");
    strcpy(single_argument, "");
    for (i = 0; i < 32; i++){
        assignment_field[i] = 0;
    }

    for (i = 0; i < strlen(stdin_str); i++){ 
        if (isspace(stdin_str[i])){

                // Check if quotes exist, if so stop increasing the field count
            if (strcmp(single_argument, "\"") == 0 && bool_increase_field_count == 1){
                bool_increase_field_count = 0;
                // Remove space from the start and end of str
                temp_field = remove_from_str(assignment_field, temp_field,assignment_field_count);
                assignment_field[assignment_field_count++] = strdup(temp_field);
            } else if (strcmp(single_argument, "\"") == 0 && bool_increase_field_count == 0){
                bool_increase_field_count = 1;
                single_argument = strdup("");
                assignment_field[assignment_field_count] = single_argument;
            }
            
            if (bool_increase_field_count == 0 && strcmp(single_argument, "\"") != 0){
                // if end quote is met, continue to increase field count
                assignment_field[assignment_field_count++] = strdup(single_argument);
            } else if (bool_increase_field_count == 1){
                // if end quote is not met, continue to catanate the fields together
                strcat(assignment_field[assignment_field_count], single_argument);
                while (stdin_str[i++] == ' ')
                    strcat(assignment_field[assignment_field_count], " ");
                i--;
            }
            
            single_argument = strdup("");
            single_argument_char_count = 0;

            while (stdin_str[i] == ' ')
                i++;
        } 

        single_argument[single_argument_char_count++] = stdin_str[i];
    }

    free(single_argument);
    free(temp_field);

    // check for variable expansions:
    // printf("global_var_count: %d\n", global_var_count);
    check_for_expansion(assignment_field, assignment_field_count, var_properties);
    
    for (i = 0; i < assignment_field_count; i++){
        // printf("assignment_field[%d]: %s\n", i, assignment_field[i]);
    }

    execute_stdin(assignment_field, assignment_field_count, var_properties);

    return 0;
}

void
cleanup_and_exit(){
}

int main(){
    
    char * var_properties[300];
    // 0: name - 1: type - 2: value

    char * stdin_str = malloc(255);
    strcpy(stdin_str, "");

    // setup();
    // Make sure given env is right. (correct dir and files exist.)
    // Read vals from .ajnarc

    printf("\n%s Shell (early beta stage) by Hamza Kerem Mumcu\n\n", SH_NAME);
    printf("Type 'help' to learn about %s's builtin (internal) commands\n", SH_NAME);
    printf("Builtins implemented so far: 'exit', 'help', 'syntax', 'echo', 'varinfo'.\n\n");

    printf("Type 'syntax' to learn about shell features and their syntax.\n");
    printf("Features implemented so far: variables ('syntax var'), variable expansion ('syntax varexp').\n\n");
    printf("Try it out:\na = 4\necho %%a\nvarinfo a\n\n");
    
    while (1){

        printf(">> ");
        fgets(stdin_str, 255, stdin);

        if (strlen(stdin_str) > 1){
            stdin_str[strlen(stdin_str) - 1] = '\0';
            strcat(stdin_str, " ");
            parse_stdin(stdin_str, var_properties);
        }

    }

    free(stdin_str);    
    return 0;
}
