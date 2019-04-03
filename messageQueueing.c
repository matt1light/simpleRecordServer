//
// Created by mattias on 3/31/19.
//

#include <sys/msg.h>
#include "structures.h"
#include <unistd.h>
#include <stdio.h>


#define SERVER_MQUEUE 2234
#define CLIENT_MQUEUE 4322

struct msg_passed {
    long int msg_key;
    message_db_t real_message;
};

static int serv_qid = -1;
static int cli_qid = -1;


int server_start() {
    serv_qid = msgget((key_t) SERVER_MQUEUE, 0666 | IPC_CREAT);
    if (serv_qid == -1) return (0);


    cli_qid = msgget((key_t) CLIENT_MQUEUE, 0666 | IPC_CREAT);
    if (cli_qid == -1) return (0);

    return (1);
}


void server_ending() {
    (void)msgctl(serv_qid, IPC_RMID, 0);
    (void)msgctl(cli_qid, IPC_RMID, 0);


    serv_qid = -1;
    cli_qid = -1;
}


int read_request_from_client(message_db_t *rec_ptr){
    struct msg_passed message;

    if (msgrcv(serv_qid, (void *)&message, sizeof(*rec_ptr), 0, 0) == -1){
        return(0);
    }
    message_db_t rm = message.real_message;
    *rec_ptr = rm;
    return(1);
}

int send_resp_to_client(const message_db_t mess_to_send){
    struct msg_passed message;

    message.real_message = mess_to_send;
    message.msg_key = mess_to_send.client_pid;

    if (msgsnd(cli_qid, (void *)&message, sizeof(mess_to_send), 0) == -1){
        return(0);
    }
    return(1);
}


int client_start(){
    serv_qid = msgget((key_t)SERVER_MQUEUE, 0666);
    if (serv_qid == -1) return(0);

    cli_qid = msgget((key_t)CLIENT_MQUEUE, 0666);
    if (cli_qid == -1) {
        perror("");
        return(0);
    }
    return(1);
}


void client_ending(){
    serv_qid = -1;
    cli_qid = -1;
}


int send_mess_to_server(const message_db_t mess_to_send){
    struct msg_passed message;

    message.real_message = mess_to_send;
    message.msg_key = mess_to_send.client_pid;

    if (msgsnd(serv_qid, (void *)&message, sizeof(mess_to_send), 0) == -1){
        perror("Message send failed, make sure that server is running");
        return(0);
    }
    return(1);
}

int read_resp_from_server(message_db_t *rec_ptr){
    struct msg_passed message;

    if (msgrcv(cli_qid, (void *)&message, sizeof(*rec_ptr), 0, 0) == -1){
        return(0);
    }

    *rec_ptr = message.real_message;
    return(1);
}
