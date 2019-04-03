//
// Created by mattias on 3/31/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>
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
void record_copy(record *clone, record original);
void print_list();

void service_request(message_db_t request_message);

struct node_t {
    record record;
    LIST_ENTRY(node_t) nodes;
};

static LIST_HEAD(head_s, node_t) head;

int run_server(){
    server_start();
    LIST_INIT(&head);


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

    struct node_t * e = malloc(sizeof(struct node_t));

    strcpy(e->record.name, name);
    strcpy(e->record.department, department);
    strcpy(e->record.employee_number, employee_number);
    strcpy(e->record.salary, salary);

    LIST_INSERT_HEAD(&head, e, nodes);

    message.response_code1 = success;

    return message;
}

message_db_t check_name(char employee_number[MAX_CHAR_LENGTH]){
    message_db_t message;
    message.response_code1 = error;

    struct node_t * e = malloc(sizeof(struct node_t));
    int response_count = 0;

    // iterate through the list
    LIST_FOREACH(e, &head, nodes){
      if(strcmp(employee_number, e->record.employee_number) == 0){
          record_copy(&message.response_records[response_count], e->record);
          response_count ++;
          message.response_code1 = success;
      }
        if (response_count>=10){
            break;
        }
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

    struct node_t * e = malloc(sizeof(struct node_t));
    int response_count = 0;

    // iterate through the list
    LIST_FOREACH(e, &head, nodes){
        if(strcmp(name, e->record.name) == 0){
            record_copy(&message.response_records[response_count], e->record);
            response_count ++;
            message.response_code1 = success;
        }
        if (response_count>=10){
            break;
        }
    }
    message.number_of_responses = response_count;

    return message;
}

message_db_t check(char department[MAX_CHAR_LENGTH]) {
    message_db_t message;
    message.response_code1 = error;

    struct node_t * e = malloc(sizeof(struct node_t));
    int response_count = 0;

    // iterate through the list
    LIST_FOREACH(e, &head, nodes){
        if(strcmp(department, e->record.department) == 0){
            record_copy(&message.response_records[response_count], e->record);
            response_count ++;
            message.response_code1 = success;
        }
        if (response_count>=10){
            break;
        }
    }
    message.number_of_responses = response_count;

    return message;
}
message_db_t delete(char employee_number[MAX_CHAR_LENGTH]){
    message_db_t message;
    message.response_code1 = error;

    struct node_t * e = malloc(sizeof(struct node_t));
    int response_count = 0;

    // iterate through the list
    LIST_FOREACH(e, &head, nodes){
        if(strcmp(employee_number, e->record.employee_number) == 0){
            record_copy(&message.response_records[response_count], e->record);
            response_count ++;
            message.response_code1 = success;

            LIST_REMOVE(e, nodes);
            free(e);
        }
        if (response_count>=10){
            break;
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
    struct node_t * e = NULL;
    LIST_FOREACH(e, &head, nodes){
        printf("%s", e->record.name);
    }
}
