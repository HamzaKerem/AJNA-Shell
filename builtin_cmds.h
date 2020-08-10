#ifndef _BUILTIN_CMDS_H
#define _BUILTIN_CMDS_H
#define SH_NAME "AJNA"
#define BUILTIN_COUNT 5

void
exec_varinfo(char * assignment_field[], int assignment_field_count, char * var_properties[], int var_count){

    int i, j, given_var_var_count = -1;
    // if no parameters given show all vars:
    if (assignment_field_count == 1 && var_count > -1){
        printf("\n");
        for (i = 0; i < var_count + 3; i += 3){
            printf("[name]  var_properties[%d]: %s\n", i, var_properties[i]);
            printf("[type]  var_properties[%d]: %s\n", i + 1, var_properties[i + 1]);
            printf("[value] var_properties[%d]: %s\n\n", i + 2, var_properties[i + 2]);
        }
    } else if (assignment_field_count > 1){
        // if parameter/s are given
        // check if assignment_field[j] is a valid var name
        for (j = 1; j < assignment_field_count; j++){
            
            given_var_var_count = -1;
            for (i = 0; i < var_count + 3; i += 3){
                if (strcmp(var_properties[i], assignment_field[j]) == 0){
                    given_var_var_count = i;
                }
            }

            if (given_var_var_count > -1){
                i = given_var_var_count;
                printf("\n[name]  var_properties[%d]: %s\n", i, var_properties[i]);
                printf("[type]  var_properties[%d]: %s\n", i + 1, var_properties[i + 1]);
                printf("[value] var_properties[%d]: %s\n\n", i + 2, var_properties[i + 2]);
            } else
                fprintf(stderr, "%s: varinfo: '%s' has not been declared as a variable\n", SH_NAME, assignment_field[j]);
        }

    } else if (var_count < 0)
        fprintf(stderr, "%s: varinfo: No variables have been declared\n", SH_NAME);

}

void
exec_echo(char * assignment_field[], int assignment_field_count){

    int i;
    for (i = 1; i < assignment_field_count; i++){
        printf("%s ", assignment_field[i]);
    }
    printf("\n");

}

void
show_help_guide(char * assignment_field[], int assignment_field_count){

    int i;
    if (assignment_field_count == 1){

        printf("\n%s Shell Help Guide\n", SH_NAME);
        printf("The following are builtin (internal) commands of the shell.\n");
        printf("Type 'help name' to find more about the builtin 'command'.\n\n");
        printf("Type 'syntax' to learn about shell features and their syntax.\n");
        printf("Features implemented so far: variables ('syntax var'), variable expansion ('syntax varexp').\n\n");
        
        printf("exit: exit - exits %s Shell\n", SH_NAME);
        printf("help: help [builtin] - displays information about given builtin and its syntax\n");
        printf("syntax: sytnax [feature] - displays information about given feature and its syntax\n");
        printf("echo: echo [arg ...] - displays given argument(s) to standart output\n");
        printf("varinfo: varinfo [variable ...] - displays information about given variable(s)\n\n");

        
    } else{

        if (strcmp(assignment_field[1], "exit") == 0)
            printf("exit: exit - exits %s Shell\n", SH_NAME);
        else if (strcmp(assignment_field[1], "help") == 0)
            printf("help: help [builtin] - displays information about given builtin and its syntax\n");
        else if (strcmp(assignment_field[1], "syntax") == 0)
            printf("syntax: sytnax [feature] - displays information about given feature and its syntax\n");
        else if (strcmp(assignment_field[1], "echo") == 0)
            printf("echo: echo [arg ...] - displays given argument(s) to standart output\n");
        else if (strcmp(assignment_field[1], "varinfo") == 0)
            printf("varinfo: varinfo [variable ...] - displays information about given variable(s)\n");
        else
            fprintf(stderr, "%s: help: %s is not a builtin\n", SH_NAME, assignment_field[1]);
        
    }
    
}   

void
show_syntax_guide(char * assignment_field[], int assignment_field_count){

    int i;
    if (assignment_field_count == 1){

        printf("\n%s Shell Syntax Guide\n", SH_NAME);
        printf("The following are builtin (internal) features of the shell.\n");
        printf("Type 'syntax feature' to find more about the builtin 'feature'.\n\n");
        printf("Type 'syntax' to learn about shell features and their syntax.\n");
        printf("Features implemented so far: variables ('syntax var'), variable expansion ('syntax varexp').\n\n");
        printf("Soon to be implemented: conditions, ...\n");
        printf("Type 'help' to learn about %s's builtin (internal) commands\n\n\n", SH_NAME);

        printf("Basics:\n\n");
        printf("%s Shell uses white space to parse standart input.\n", SH_NAME);
        printf("The amount of spaces between commands won't matter altough tabs don't work yet.\n\n", SH_NAME);
        printf("Use quotes in order to avoid word-splitting.\n", SH_NAME);
        printf("echo 1 2 3 - read as 4 different arguments.\n", SH_NAME);
        printf("echo \" 1 2 3 \" - read as only 2 arguments.\n", SH_NAME);
        printf("echo here       there - displays: here there\n", SH_NAME);
        printf("echo \" here       there \" - displays: here       there\n\n\n", SH_NAME);

        printf("Declare and Assign Variables:\n\n");
        printf("one_word_str = \"testing\"\n");
        printf("mutliword_string = \" \"Quotes stop word-splitting\" \"\n\n");
        printf("my_int = 10\n");
        printf("num1 = -43\n\n");
        printf("my_null_var = \n");
        printf("noValVar = \n\n");
        printf("Type 'echo %%var' to see the value of a variable.\n");
        printf("Type 'varinfo var' to see the name, type, and value of a variable.\n");
        printf("Typing only 'varinfo' will display every variable and its properties.\n\n");
        printf("Soon to be implemented: Assign variables arithmetic expressions, standart output of commands, ...\n\n\n");

        printf("Variable Expansion:\n\n");
        printf("If a variable is proceded by '%%' it will be expanded into its value.\n");
        printf("If a variable is proceded by '%%' but the variable being expanded doesn't exist,\n");
        printf("the value will be expanded into NULL.\n\n");
        printf("a = %%b\n");
        printf("echo %%my_str\n");


    } else{
            if (strcmp(assignment_field[1], "basics") == 0){
                printf("Basics:\n\n");
                printf("%s Shell uses white space to parse standart input.\n", SH_NAME);
                printf("The amount of spaces between commands won't matter altough tabs don't work yet.\n\n", SH_NAME);
                printf("Use quotes in order to avoid word-splitting.\n", SH_NAME);
                printf("echo 1 2 3 - read as 4 different arguments.\n", SH_NAME);
                printf("echo \" 1 2 3 \" - read as only 2 arguments.\n", SH_NAME);
            } else if (strcmp(assignment_field[1], "var") == 0){
                printf("Declare and Assign Variables:\n\n");
                printf("one_word_str = \"testing\"\n");
                printf("mutliword_string = \" \"Quotes stop word-splitting\" \"\n\n");
                printf("my_int = 10\n");
                printf("num1 = -43\n\n");
                printf("my_null_var = \n");
                printf("noValVar = \n\n");
                printf("Type 'echo %%var' to see the value of a variable.\n");
                printf("Type 'varinfo var' to see the name, type, and value of a variable.\n");
                printf("Typing only 'varinfo' will display every variable and its properties.\n\n");
                printf("Soon to be implemented: Assign variables arithmetic expressions, standart output of commands, ...\n");
            } else if (strcmp(assignment_field[1], "varexp") == 0){
                printf("Variable Expansion:\n\n");
                printf("If a variable is proceded by '%%' it will be expanded into its value.\n");
                printf("If a variable is proceded by '%%' but the variable being expanded doesn't exist,\n");
                printf("the value will be expanded into NULL.\n\n");
                printf("a = %%b\n");
                printf("echo %%my_str\n");
            } else
                fprintf(stderr, "%s: syntax: %s is not a feature title\n", SH_NAME, assignment_field[1]);
            
    }
    printf("\n");
}

int
execute_builtin_cmd(char * assignment_field[], int assignment_field_count, char * var_properties[], int var_count, int selected_builtin_cmd){
  
    switch (selected_builtin_cmd)
    {
        case 0:
            exit(0);
            break;
        
        case 1:
            exec_echo(assignment_field, assignment_field_count);
            break;
        
        case 2:
            show_help_guide(assignment_field, assignment_field_count);
            break;
        
        case 3:
            exec_varinfo(assignment_field, assignment_field_count, var_properties, var_count);
            break;
        case 4:
            show_syntax_guide(assignment_field, assignment_field_count);
            break;

        default: 
            fprintf(stderr, "Error occured, exiting\n");
            exit(1);
            break;
    }

    return 0;
}


#endif

/*
    fprintf(stderr, "\nUsage: Declare and assign a variable:\n\n");
    fprintf(stderr, "one_word = \"testing\"\n");
    fprintf(stderr, "words = \" \"Quotes stop word-splitting\" \"\n\n");
    fprintf(stderr, "my_int = 10\n");
    fprintf(stderr, "Arithmetic_Exp1 = 10 14 +\n");
    fprintf(stderr, "Arithmetic_Exp2 = -8 7 - 56 * \n\n");
    
    fprintf(stderr, "my_command = ls\n");
    fprintf(stderr, "cmd1 = \" ls ; echo \" hi\n");
    fprintf(stderr, "Note: 'cmd1 = ls ; echo hi' would parse \n'echo' and 'hi' as parameters of 'ls'\n");
    */