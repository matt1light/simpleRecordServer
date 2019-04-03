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
    if (receive_message.response_code1 == error){
        printf("\nNo results");
        return;
    }
    int i;

    request_code_e type = receive_message.request_type;
    switch(type){
        case 1:
            printf("\nRecord successfully added");
            break;
        case 2:;
            for(i = 0; i<receive_message.number_of_responses; i++){
                printf("\nName: %s", receive_message.response_records[i].name);
            }
            break;
        case 3:
            for(i = 0; i<receive_message.number_of_responses; i++){
                printf("\nDepartment: %s", receive_message.response_records[i].department);
            }
            break;
        case 4:
            for(i = 0; i<receive_message.number_of_responses; i++){
                printf("\nSalary: %s", receive_message.response_records[i].salary);
            }
            break;
        case 5:
            for(i = 0; i<receive_message.number_of_responses; i++){
                printf("\nEmployee number: %s", receive_message.response_records[i].employee_number);
            }
            break;
        case 6:
            for(i = 0; i<receive_message.number_of_responses; i++){
                printf("\nEmployee number: %s", receive_message.response_records[i].employee_number);
            }
            break;
        case 7:
            for(i = 0; i<receive_message.number_of_responses; i++){
                printf("\nEmployee %s deleted successfully", receive_message.response_records[i].employee_number);
            }
            break;
        default:
            printf("\nError did not receive the request type");
            break;
    }
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

  message -> request_type = 1;
  message -> client_pid = getpid();
}

void create_check_name_message(
    char employee_number[MAX_CHAR_LENGTH],
    message_db_t* message
    ){
  strcpy(message -> request_record.employee_number, employee_number);

  message -> request_type = 2;
  message -> client_pid = getpid();
}

void create_check_department_message(
    char employee_number[MAX_CHAR_LENGTH],
    message_db_t* message
    ){
  strcpy(message -> request_record.employee_number, employee_number);

  message -> request_type = 3;
  message -> client_pid = getpid();
}

void create_check_salary_message(
    char employee_number[MAX_CHAR_LENGTH],
    message_db_t* message){
  strcpy(message -> request_record.employee_number, employee_number);

  message -> request_type = 4;
  message -> client_pid = getpid();
}

void create_check_employee_number_message(char name[MAX_CHAR_LENGTH],
    message_db_t* message){
  strcpy(message -> request_record.name, name);

  message -> request_type = 5;
  message -> client_pid = getpid();
}

void create_check_message(char department[MAX_CHAR_LENGTH],
    message_db_t* message){
  strcpy(message -> request_record.department, department);

  message -> request_type = 6;
  message -> client_pid = getpid();
}

void create_delete_message(char employee_number[MAX_CHAR_LENGTH],
    message_db_t* message){

  strcpy(message -> request_record.employee_number, employee_number);

  message -> request_type = 7;
  message -> client_pid = getpid();
}
