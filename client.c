//
// Created by mattias on 3/31/19.
//
#include <unistd.h>
#include "structures.h"
#include "messageQueueing.h"

void send_request(message_db_t request_message, message_db_t *response_message);

int run_client(){
    client_start();
    message_db_t request_message, *response_message;
    request_message.request_type;
    request_message.request_record;
    request_message.response_records;
    request_message.response_code1;
    request_message.client_pid = getpid();
    send_request(request_message, response_message);
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

