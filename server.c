//
// Created by mattias on 3/31/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "messageQueueing.h"

message_db_t insert_record(
        char name[MAX_CHAR_LENGTH],
        char department[MAX_CHAR_LENGTH],
        char employee_number[MAX_CHAR_LENGTH],
        char salary[MAX_CHAR_LENGTH]);

message_db_t check_name(char employee_number[MAX_CHAR_LENGTH]);
message_db_t check_department(char employee_number[MAX_CHAR_LENGTH]);
message_db_t check_salary(char employee_number[MAX_CHAR_LENGTH]);
message_db_t check_employee_number(char name[MAX_CHAR_LENGTH]);
message_db_t check(char department[MAX_CHAR_LENGTH]);
message_db_t delete(char employee_number[MAX_CHAR_LENGTH]);

void service_request(message_db_t request_message);

int run_server(){
    server_start();
    while(1){
        message_db_t *receive_message = (message_db_t*) malloc(sizeof(message_db_t));
        int i = read_request_from_client(receive_message);
        if (i == 0){
            continue;
        }
        service_request(*receive_message);
    }
}

void service_request(message_db_t request_message){
    // read message from client
    message_db_t response_message;

    request_code_e type = request_message.request_type;

    switch(type){
        case insert_record_s:
            response_message = insert_record(
                    request_message.request_record.name,
                    request_message.request_record.department,
                    request_message.request_record.employee_number,
                    request_message.request_record.salary
            );
            break;
        case check_name_s:
            response_message = check_name(
                    request_message.request_record.employee_number
            );
            break;
        case check_department_s:
            response_message = check_department(
                    request_message.request_record.employee_number
            );
            break;
        case check_salary_s:
            response_message = check_salary(
                    request_message.request_record.employee_number
            );
            break;
        case check_employee_number_s:
            response_message = check_employee_number(
                    request_message.request_record.name
            );
            break;
        case check_s:
            response_message = check(
                    request_message.request_record.department
            );
            break;
        case delete_s:
            response_message = delete(
                    request_message.request_record.employee_number
            );
            break;
        default:
            break;
    }

    send_resp_to_client(response_message);
}

int count = 0;
record records[100];

// message_db_t* message
// message -> client_pid = getpid();

message_db_t insert_record(
        char name[MAX_CHAR_LENGTH],
        char department[MAX_CHAR_LENGTH],
        char employee_number[MAX_CHAR_LENGTH],
        char salary[MAX_CHAR_LENGTH]) {

    strcpy(records[count].name, name);
    strcpy(records[count].department, department);
    strcpy(records[count].employee_number, employee_number);
    strcpy(records[count].salary, salary);
    count += 1;

    message_db_t message;
    return message;
}

message_db_t check_name(char employee_number[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(records[i].employee_number == employee_number) {
      message.e = records[i].name;
    }
  }
  return message;
}
message_db_t check_department(char employee_number[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(records[i].employee_number == employee_number) {
      message.e = records[i].department;
    }
  }
  return message;
}
message_db_t check_salary(char employee_number[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(records[i].employee_number == employee_number) {
      message.e = records[i].salary;
    }
  }
  return message;
}
message_db_t check_employee_number(char name[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(records[i].name == name) {
      message.e = records[i].employee_number;
    }
  }
  return message;
}
message_db_t check(char department[MAX_CHAR_LENGTH]){
  perror("Check not implemented");
  message_db_t message;
  return message;
}
message_db_t delete(char employee_number[MAX_CHAR_LENGTH]){
  for(int i = 0; i <= count; i++) {
    if(records[i].employee_number == employee_number) {
      for (int c = i - 1; c < count - 1; c++) {
        records[c] = records[c+1];
      }
    }
  }
  count -= 1;

  message_db_t message;
  return message;
}
