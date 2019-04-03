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

message_db_t insert_record(
        char name[MAX_CHAR_LENGTH],
        char department[MAX_CHAR_LENGTH],
        char employee_number[MAX_CHAR_LENGTH],
        char salary[MAX_CHAR_LENGTH]) {

    message_db_t message;

    strcpy(message.response_records[count].name, name);
    strcpy(message.response_records[count].department, department);
    strcpy(message.response_records[count].employee_number, employee_number);
    strcpy(message.response_records[count].salary, salary);
    message.response_code1 = success;
    count += 1;

    return message;
}

message_db_t check_name(char employee_number[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(message.response_records[i].employee_number == employee_number) {
      strcpy(message.e, response_records[i].name);
      message.response_code1 = success;
    }
    else {
      message.response_code1 = error;
    }
  }
  return message;
}
message_db_t check_department(char employee_number[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(message.response_records[i].employee_number == employee_number) {
      strcpy(message.e, response_records[i].department);
      message.response_code1 = success;
    }
    else {
      message.response_code1 = error;
    }
  }
  return message;
}
message_db_t check_salary(char employee_number[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(message.response_records[i].employee_number == employee_number) {
      strcpy(message.e, response_records[i].salary);
      message.response_code1 = success;
    }
    else {
      message.response_code1 = error;
    }
  }
  return message;
}
message_db_t check_employee_number(char name[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(message.response_records[i].name == name) {
      strcpy(message.e, response_records[i].employee_number);
      message.response_code1 = success;
    }
    else {
      message.response_code1 = error;
    }
  }
  return message;
}
message_db_t check(char department[MAX_CHAR_LENGTH]) {
  message_db_t message;
  char employeeNumbers[100];

  for(int i = 0; i <= count; i++) {
    if(message.response_records[i].department == department) {
      strcpy(employeeNumbers[i], message.response_records[i].employee_number);
      message.response_code1 = success;
    }
    else {
      message.response_code1 = error;
    }
  }

  return message;
}
message_db_t delete(char employee_number[MAX_CHAR_LENGTH]){
  message_db_t message;
  for(int i = 0; i <= count; i++) {
    if(message.response_records[i].employee_number == employee_number) {
      for (int c = i - 1; c < count - 1; c++) {
        message.response_records[c] = message.response_records[c+1];
        message.response_code1 = success;
      }
    }
    else {
      message.response_code1 = error;
    }
  }
  count -= 1;

  return message;
}
