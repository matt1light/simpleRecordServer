//
// Created by mattias on 3/31/19.
//

#ifndef A3_MESSAGEQUEUEING_H
#define A3_MESSAGEQUEUEING_H

int server_start();

void server_ending();

int read_request_from_client(message_db_t *rec_ptr);

int send_resp_to_client(const message_db_t mess_to_send);

int client_start();

void client_ending();

int send_mess_to_server(message_db_t mess_to_send);

int read_resp_from_server(message_db_t *rec_ptr);
#endif //A3_MESSAGEQUEUEING_H
