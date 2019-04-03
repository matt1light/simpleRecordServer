
#include "client.h"
#include "messageQueueing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getName(char* name){
  printf("Name: ");
  fgets(name, 12, stdin);
}

void getEmployeeNumber(char* employee_number){
  printf("Employee Number: ");
  fgets(employee_number, 12, stdin);
}

void getDepartment(char* department){
  printf("Department: ");
  fgets(department, 12, stdin);
}

void getSalary(char* salary){
  printf("Salary: ");
  fgets(salary, 12, stdin);
}

int run_sender(){
  if(!client_start()){
      perror("Client did not start");
      return(0);
  }
  char buf[12];
  int * command = (int*)malloc(sizeof(int));
  char *name = (char*)malloc(sizeof(char));
  char *employee_number = (char*)malloc(sizeof(char));
  char *department = (char*)malloc(sizeof(char));
  char *salary = (char*)malloc(sizeof(char));
  message_db_t * message = (message_db_t*)malloc(sizeof(message_db_t));
  message_db_t * receive_message = (message_db_t*)malloc(sizeof(message_db_t));

  while(1){
      printf("\n\n\nWhat would you like to do:\n\t1) insert\n\t2) check name\n\t3) check department\n\t4) check salary\n\t5) check employee number\n\t6) check\n\t7) delete\n");

      if (fgets(buf, 12, stdin) == NULL){
        fprintf(stderr, "read failed\n");
        return 1;
      }

      sscanf(buf, "%d", command);

    switch(*command){
      case 1:
        getName(name);
            getEmployeeNumber(employee_number);
            getDepartment(department);
            getSalary(salary);
            create_insert_record_message(name, department, employee_number, salary, message);
            break;
      case 2:
        getEmployeeNumber(employee_number);
            create_check_name_message(employee_number, message);
            break;
      case 3:
        getEmployeeNumber(employee_number);
            create_check_department_message(employee_number, message);
            break;
      case 4:
        getEmployeeNumber(employee_number);
            create_check_salary_message(employee_number, message);
            break;
      case 5:
        getName(name);
            create_check_employee_number_message(name, message);
            break;
      case 6:
        getDepartment(department);
            create_check_message(department, message);
            break;
      case 7:
        getEmployeeNumber(employee_number);
            create_delete_message(employee_number, message);
            break;
      default:
        return(1);
    }
    send_request(*message, receive_message);
    receive_message->request_type = message->request_type;
    process_received(*receive_message);
  }
}
