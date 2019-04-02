//
// Created by mattias on 3/31/19.
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"
#include "messageQueueing.h"

void send_request(message_db_t request_message, message_db_t *response_message);

void process_received(message_db_t receive_message);

void create_insert_record_message( char name[MAX_CHAR_LENGTH], char department[MAX_CHAR_LENGTH], char employee_number[MAX_CHAR_LENGTH], char salary[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_name_message( char employee_number[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_department_message( char employee_number[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_salary_message( char employee_number[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_employee_number_message(char name[MAX_CHAR_LENGTH], message_db_t* message);

void create_check_message(char department[MAX_CHAR_LENGTH], message_db_t* message);

void create_delete_message(char employee_number[MAX_CHAR_LENGTH], message_db_t* message);

int run_client(){
    client_start();
    message_db_t request_message, *response_message;
    send_request(request_message, response_message);
}

void process_received(message_db_t receive_message){
    perror("Receive handling on client implemented");
}

void send_request(message_db_t request_message, message_db_t *response_message){
    // send message to server
    send_mess_to_server(request_message);
    int received = 0;
    while(!received){
        received = read_resp_from_server(response_message);
    }
    // read message from server
}


void create_insert_record_message(
        char name[MAX_CHAR_LENGTH],
        char department[MAX_CHAR_LENGTH],
        char employee_number[MAX_CHAR_LENGTH],
        char salary[MAX_CHAR_LENGTH],
        message_db_t* message
        ){
  strcpy(message -> request_record.name, name);
  strcpy(message -> request_record.department, department);
  strcpy(message -> request_record.employee_number, employee_number);
  strcpy(message -> request_record.salary, salary);

  message -> request_type = insert_record_s;
  message -> client_pid = getpid();
}

void create_check_name_message(
    char employee_number[MAX_CHAR_LENGTH],
    message_db_t* message
    ){
  strcpy(message -> request_record.employee_number, employee_number);

  message -> request_type = check_name_s;
  message -> client_pid = getpid();
}

void create_check_department_message(
    char employee_number[MAX_CHAR_LENGTH],
    message_db_t* message
    ){
  strcpy(message -> request_record.employee_number, employee_number);

  message -> request_type = check_department_s;
  message -> client_pid = getpid();
}

void create_check_salary_message(
    char employee_number[MAX_CHAR_LENGTH],
    message_db_t* message){
  strcpy(message -> request_record.employee_number, employee_number);

  message -> request_type = check_salary_s;
  message -> client_pid = getpid();
}

void create_check_employee_number_message(char name[MAX_CHAR_LENGTH],
    message_db_t* message){
  strcpy(message -> request_record.name, name);

  message -> request_type = check_employee_number_s;
  message -> client_pid = getpid();
}

void create_check_message(char department[MAX_CHAR_LENGTH],
    message_db_t* message){
  strcpy(message -> request_record.department, department);

  message -> request_type = check_s;
  message -> client_pid = getpid();
}

void create_delete_message(char employee_number[MAX_CHAR_LENGTH],
    message_db_t* message){

  strcpy(message -> request_record.employee_number, employee_number);

  message -> request_type = delete_s;
  message -> client_pid = getpid();
}
