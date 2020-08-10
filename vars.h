#ifndef _VARS_H
#define _VARS_H
#define SH_NAME "AJNA"

void
show_var_usage(){
    fprintf(stderr, "\n%s: See: 'syntax var'\n", SH_NAME);
}

char * 
check_and_prep_int(int assigned_val_count, char * assigned_values[], char * type_of_var, int * operator_type_and_index_ptr, int * operand_val_and_index_ptr){
    // type_of_var = "VOID";
    int i, j, operator_count = 0, operand_count = 0, is_digit_check = 0, is_operator_check = 0;

    // Arithmetic expression must be an odd value
    if (assigned_val_count % 2 == 0)
        return "VOID";
    

    type_of_var = strdup("int");

    // Read each operator and operand, and store their values in the corresponding ptrs
    for (i = 0; i < assigned_val_count; i++){
        // identify wether value is operator or operand
        is_digit_check = 0;

        // Check if operator: +: 0  -: 1  *: 2  /: 3 
        if (strcmp(assigned_values[i], "+") == 0){
            // Store type of operator first
            operator_type_and_index_ptr[operator_count++] = 0;
            // printf("[type]  - operator_type_and_index_ptr[%d]: %d\n", operator_count-1, operator_type_and_index_ptr[operator_count-1]);

            // Then index of operator
            operator_type_and_index_ptr[operator_count++] = i;
            // printf("[index] - operator_type_and_index_ptr[%d]: %d\n\n", operator_count-1, operator_type_and_index_ptr[operator_count-1]);
            is_operator_check++;
        } else if (strcmp(assigned_values[i], "-") == 0){
            operator_type_and_index_ptr[operator_count++] = 1;
            // printf("[type]  - operator_type_and_index_ptr[%d]: %d\n", operator_count-1, operator_type_and_index_ptr[operator_count-1]);

            operator_type_and_index_ptr[operator_count++] = i;
            // printf("[index] - operator_type_and_index_ptr[%d]: %d\n\n", operator_count-1, operator_type_and_index_ptr[operator_count-1]);
            is_operator_check++;
        } else if (strcmp(assigned_values[i], "*") == 0){
            operator_type_and_index_ptr[operator_count++] = 2;
            // printf("[type]  - operator_type_and_index_ptr[%d]: %d\n", operator_count-1, operator_type_and_index_ptr[operator_count-1]);

            operator_type_and_index_ptr[operator_count++] = i;
            // printf("[index] - operator_type_and_index_ptr[%d]: %d\n\n", operator_count-1, operator_type_and_index_ptr[operator_count-1]);
            is_operator_check++;
        } else if (strcmp(assigned_values[i], "/") == 0){
            operator_type_and_index_ptr[operator_count++] = 3;
            // printf("[type]  - operator_type_and_index_ptr[%d]: %d\n", operator_count-1, operator_type_and_index_ptr[operator_count-1]);

            operator_type_and_index_ptr[operator_count++] = i;
            // printf("[index] - operator_type_and_index_ptr[%d]: %d\n\n", operator_count-1, operator_type_and_index_ptr[operator_count-1]);
            is_operator_check++;
        } else{
        
            for (j = 0; j < strlen(assigned_values[i]); j++){
                if (assigned_values[i][0] == '-')
                    is_digit_check++;
                else if (isdigit(assigned_values[i][j]))
                    is_digit_check++;
            }
            // Check if int
            if (is_digit_check == strlen(assigned_values[i])){
                // Store val of int first
                operand_val_and_index_ptr[operand_count++] = atoi(assigned_values[i]);
                // printf("[value] - operand_val_and_index_ptr[%d]: %d\n", operand_count-1, operand_val_and_index_ptr[operand_count-1]);

                // Then index of int
                operand_val_and_index_ptr[operand_count++] = i;
                // printf("[index] - operand_val_and_index_ptr[%d]: %d\n\n", operand_count-1, operand_val_and_index_ptr[operand_count-1]);

            } else{   
                // Value[i] is not operator or operand, thus type is not int
                return "VOID";
            }
               
        }

    }

    if (!(assigned_val_count == (operand_count + operator_count) / 2 && operand_count == operator_count + 2))
        return "VOID";
    
    
    return type_of_var;
}

char * 
check_data_type(int assigned_val_count, char * assigned_values[], char * type_of_var, int * operator_type_and_index_ptr, int * operand_val_and_index_ptr){

    // Var property rules:
    // Strings can only have 1 assigned val ("my string")
    // Ints can have multiple assigned vals (1 2 +)
    // commands look like strings but have no quotes (must check if cmd exists from /usr/bin/)

    type_of_var = "VOID";

    // Check if str
    if (assigned_val_count == 1 && assigned_values[0][0] == '"' && assigned_values[0][strlen(assigned_values[0]) - 1] == '"')
        type_of_var = "string";
    else if (assigned_val_count >= 1)
        type_of_var = check_and_prep_int(assigned_val_count, assigned_values, type_of_var, operator_type_and_index_ptr, operand_val_and_index_ptr);
    
    return type_of_var;
}

char *
calculate_assigned_values(int assigned_val_count, char * assigned_values[], int * operator_type_and_index_ptr, int * operand_val_and_index_ptr){

    if (assigned_val_count == 1)
        return assigned_values[0];

    return "ARITHEMTIC_EXP";
}

char *
remove_from_str(char * assigned_values[], char * value_of_var, int assignment_field_count){

    int i = 0, j = 1;

    for (i = 0, j = 1; i < strlen(assigned_values[assignment_field_count]) - 2; i++, j++){
        value_of_var[i] = assigned_values[assignment_field_count][j];
    }

    return value_of_var;
}

int
assign_var(char ** assignment_field, int assignment_field_count, char * var_properties[], int var_count){
    
    static int local_var_count = -3;
    int i, assigned_val_count = 0, var_previously_declared = 1, matching_name_of_var_index;
    int * operator_type_and_index_ptr = malloc(255);
    int * operand_val_and_index_ptr = malloc(255);

    char * assigned_values[30];
    char * name_of_var = malloc(255);
    char * type_of_var = malloc(255);
    char * value_of_var = malloc(255);

    // Init char * s and assign 1st field to be name of var
    name_of_var[0] = 0;
    type_of_var[0] = 0; 
    value_of_var[0] = 0;
    name_of_var = assignment_field[0];

    // printf("\nassignment_field[%d]: %s\n\n", assignment_field_count - 1, assignment_field[assignment_field_count - 1]);

    // Check if nothing is assigned if so assign NULL_TYPE for type
    if (strcmp(assignment_field[assignment_field_count - 1], "") == 0)
        type_of_var = strdup("NULL_TYPE");
    else if ((strcmp(assignment_field[assignment_field_count - 1], "=") == 0 && assignment_field_count - 1 == 1)){
        type_of_var = strdup("NULL_TYPE");
    } else{
        // Assign the assigned fields to assigned values
        for (i = 2; i < assignment_field_count; i++){
            assigned_values[assigned_val_count++] = assignment_field[i];
            // printf("assigned_values[%d]: %s\n", assigned_val_count - 1, assigned_values[assigned_val_count - 1]);
        }

        // expand_if_var(); vars start with a special char 
        type_of_var = strdup(check_data_type(assigned_val_count, assigned_values, type_of_var, operator_type_and_index_ptr, operand_val_and_index_ptr));
    }

    // Assign value according to data type
    if (strcmp(type_of_var, "string") == 0)
        value_of_var = strdup(remove_from_str(assigned_values, value_of_var, 0));
    else if (strcmp(type_of_var, "int") == 0)
        // calculate value of the assignment if data type is int or float
        value_of_var = strdup(calculate_assigned_values(assigned_val_count, assigned_values, operator_type_and_index_ptr, operand_val_and_index_ptr));
    else if (strcmp(type_of_var, "command") == 0)
        // Assign the stdout of cmd to value of var 
        // value_of_var = get_stdout_of_cmd();
        ;
    else if (strcmp(type_of_var, "NULL_TYPE") == 0)
        value_of_var = strdup("");
    else{
        show_var_usage();
        return local_var_count;
    }
    // printf("\n\nname_of_var: %s, type_of_var: %s, value: %s\n", name_of_var, type_of_var, value_of_var);

    // Error cases:
    if (strcmp(name_of_var, "") == 0 || strstr(name_of_var, "=") != 0 || strcmp(value_of_var, "=") == 0 || isdigit(name_of_var[0])){
        show_var_usage();
        return local_var_count;
    } 

    local_var_count += 3;

    // Check if given var_name already exists
    // if so assign val and type to same var
    for (i = 0; i < local_var_count; i++){
        if (strcmp(name_of_var, var_properties[i]) == 0){
            var_previously_declared = 0;
            matching_name_of_var_index = i;
        }
    }
    
    if (var_previously_declared == 0){
        var_properties[matching_name_of_var_index] = strdup(name_of_var);
        var_properties[matching_name_of_var_index + 1] = strdup(type_of_var);
        var_properties[matching_name_of_var_index + 2] = strdup(value_of_var);

        local_var_count -= 3;
        var_count = local_var_count;
    } else{
        var_count = local_var_count;

        var_properties[var_count] = strdup(name_of_var);
        var_properties[var_count + 1] = strdup(type_of_var);
        var_properties[var_count + 2] = strdup(value_of_var);
    }
    
    free(value_of_var);
    free(type_of_var);
    free(name_of_var);
    free(operand_val_and_index_ptr);
    free(operator_type_and_index_ptr);

    return var_count;
}

#endif