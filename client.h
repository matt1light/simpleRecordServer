#ifndef client
#define client
#include "structures.h"

void send_request(message_db_t request_message, message_db_t *response_message);

void process_received(message_db_t received_message);

void create_insert_record_message( char name[MAX_CHAR_LENGTH], char department[MAX_CHAR_LENGTH], char employee_number[MAX_CHAR_LENGTH], char salary[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_name_message( char employee_number[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_department_message( char employee_number[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_salary_message( char employee_number[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_employee_number_message(char name[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_message(char department[MAX_CHAR_LENGTH], message_db_t* message);

void create_delete_message(char employee_number[MAX_CHAR_LENGTH], message_db_t* message);

#endif
