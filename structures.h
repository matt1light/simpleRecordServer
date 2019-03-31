//
// Created by mattias on 3/31/19.
//

#include <fcntl.h>

#define MAX_CHAR_LENGTH 12
#define MAX_RESPONSES 10

typedef enum {
    insert_record_s,
    check_name_s,
    check_department_s,
    check_salary_s,
    check_employee_number_s,
    check_s,
    delete_s
} request_code_e;

typedef enum {
    error,
    success
} response_code_e;

typedef struct {
    char name[MAX_CHAR_LENGTH];
    char department[MAX_CHAR_LENGTH];
    char employee_number[MAX_CHAR_LENGTH];
    char salary[MAX_CHAR_LENGTH];
} record;

typedef struct {
    pid_t client_pid;
    request_code_e request_type;
    response_code_e response_code1;
    record request_record;
    record response_records[MAX_RESPONSES];
    int number_of_responses;
    char e;
} message_db_t;
