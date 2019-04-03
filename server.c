//
// Created by mattias on 3/31/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
#include "structures.h"
#include "messageQueueing.h"
#include "linkedlist.h"

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
void record_copy(record *clone, record original);
void print_list();

void service_request(message_db_t request_message);

struct Node * head;

int run_server(){
    server_start();
    head = malloc(sizeof(struct Node));

    while(1){
        message_db_t *receive_message = malloc(sizeof(message_db_t));
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

    int type = request_message.request_type;

    switch(type){
        case 1:
            response_message = insert_record(
                    request_message.request_record.name,
                    request_message.request_record.department,
                    request_message.request_record.employee_number,
                    request_message.request_record.salary
            );
            break;
        case 2:
            response_message = check_name(
                    request_message.request_record.employee_number
            );
            break;
        case 3:
            response_message = check_department(
                    request_message.request_record.employee_number
            );
            break;
        case 4:
            response_message = check_salary(
                    request_message.request_record.employee_number
            );
            break;
        case 5:
            response_message = check_employee_number(
                    request_message.request_record.name
            );
            break;
        case 6:
            response_message = check(
                    request_message.request_record.department
            );
            break;
        case 7:
            response_message = delete(
                    request_message.request_record.employee_number
            );
            break;
        default:
            break;
    }

    response_message.client_pid = request_message.client_pid;
    send_resp_to_client(response_message);
}

message_db_t insert_record(
        char name[MAX_CHAR_LENGTH],
        char department[MAX_CHAR_LENGTH],
        char employee_number[MAX_CHAR_LENGTH],
        char salary[MAX_CHAR_LENGTH]) {

    message_db_t message;

    struct Node * e = malloc(sizeof(struct Node));

    strcpy(e->data.name, name);
    strcpy(e->data.department, department);
    strcpy(e->data.employee_number, employee_number);
    strcpy(e->data.salary, salary);

    insertAfter(head, e);

    message.response_code1 = success;

    return message;
}

message_db_t check_name(char employee_number[MAX_CHAR_LENGTH]){
    message_db_t message;
    message.response_code1 = error;

    struct Node * e = head;
    int response_count = 0;

    while(e != NULL){
        if(strcmp(employee_number, e->data.employee_number) == 0){
            record_copy(&message.response_records[response_count], e->data);
            response_count ++;
            message.response_code1 = success;
        }
        e = e->next;
    }
    message.number_of_responses = response_count;

    return message;
}

message_db_t check_department(char employee_number[MAX_CHAR_LENGTH]){
    return check_name(employee_number);
}

message_db_t check_salary(char employee_number[MAX_CHAR_LENGTH]){
    return check_name(employee_number);
}

message_db_t check_employee_number(char name[MAX_CHAR_LENGTH]){
    message_db_t message;
    message.response_code1 = error;

    struct Node * e = head;
    int response_count = 0;

    while(e != NULL){
        if(strcmp(name, e->data.name) == 0){
            record_copy(&message.response_records[response_count], e->data);
            response_count ++;
            message.response_code1 = success;
        }
        e = e->next;
    }
    // iterate through the list
    message.number_of_responses = response_count;
    message.number_of_responses = response_count;

    return message;
}

message_db_t check(char department[MAX_CHAR_LENGTH]) {
    message_db_t message;
    message.response_code1 = error;

    struct Node * e = head;
    int response_count = 0;

    while(e != NULL){
        if(strcmp(department, e->data.department) == 0){
            record_copy(&message.response_records[response_count], e->data);
            response_count ++;
            message.response_code1 = success;
        }
        e = e->next;
    }
    // iterate through the list
    message.number_of_responses = response_count;

    return message;
}
message_db_t delete(char employee_number[MAX_CHAR_LENGTH]){
    message_db_t message;
    message.response_code1 = error;

    struct Node * e = head;
    int response_count = 0;

    while(e != NULL){
        if(strcmp(employee_number, e->data.employee_number) == 0){
            record_copy(&message.response_records[response_count], e->data);
            response_count ++;
            message.response_code1 = success;

            e = removeItem(e);
        }
        else{
            e = e->next;
        }
    }
    message.number_of_responses = response_count;

    return message;
}

void record_copy(record * clone, record original){
    strcpy(clone -> employee_number, original.employee_number);
    strcpy(clone -> name, original.name);
    strcpy(clone -> department, original.department);
    strcpy(clone -> salary, original.salary);
}

void print_list(){
    struct Node * e = head;
    while(e != NULL){
        printf("%s", e->data.name);
        e = e->next;
    }
}
