/*
File:         arg_parse.h
Author:       Anton Jaska
Created:      2024.12.00
Modified:     2024.04.20
Description:  Header file for arg_parse.c. Data struct definitions, macros
              etc.
*/

#ifndef _ARG_PARSE
#define _ARG_PARSE

//#define ERR_MSG_LEN 256
//#define MSG_MAX_LEN 128
//#define FILE_NAME_MAX_LEN 256
#define ARG_MAX_NAME_LEN 64

enum argument_cases {ADD_LOC, RM_LOC, DISP_FORECAST,
                     ARG_SUPPORTED_CNT};

/*
    Description of a command line argument. arg_value denotes custom switch case
    action. arg_name is the first word of the argument typed on the CLI.
    arg_mems denotes how many words the argument consists of.
*/
struct argument_description
{
    enum argument_cases arg_value;
    char arg_name[ARG_MAX_NAME_LEN];
    int arg_mems;
};

/*
    If needed, this struct holds values, that are the result of parsing CLI
    arguments.
*/
struct argument
{
    bool display_forecast;
};


/*
Description:    Checks if every command line argument in **arg_vec is supported
                by comparing them against supported arguments stored as strings
                in struct array *opts. Calls function change_argument_value to
                change default values stored in struct *args.
                
Parameters:     *opts - Struct for supported command line arguments.
                *args - Struct that holds the final argument values.
                arg_cnt - Number of arguments provided by command line.
                **arg_vec - Array of strings from command line.
                
Return:         -
*/
void parse_arguments(struct argument_description *opts, struct argument *args,
                     int arg_cnt, char **arg_vec);


/*
Description:    Handles changing of argument values, that are stored in a struct
                and that the program uses. Also checks if enough arguments are
                provided in cases, where argument consists of multiple strings.
                
Parameters:     *args - Struct which holds the argument values that the program
                uses.
                event - An enum, that describes what argument will be changed.
                **arg_vec - Array of strings from command line.
                arg_vec_len - Number of strings provided by command line.
                cnt - The index number (in **arg_vec) of the command line argument
                currently being parsed.
                arg_mems - The number of strings the argument consists of.
                
Return:         The number of extra strings the argument consisted of. An extra
                string is every string that was not the first string.
*/
int change_argument_value(struct argument *args, enum argument_cases arg,
                          char **arg_vec, int arg_vec_len, int cnt, int arg_mems);

#endif
