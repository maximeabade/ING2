#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>

// Taille maximal du message
#define MSG_SIZE 256

// Structure de message 
struct msg_buffer {
    long msg_type; // Type du message
    char msg_text[MSG_SIZE]; // Message
    pid_t pid; // nombre de pid
};

// Fonction qui renvoie 
void reverse_string(char* str) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}


int main() {
    // Initialisation
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Obtiens la file de message
    key = ftok("server_client", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Récupération du message 
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Message reçu du client : %s\n", message.msg_text);  

    // Inversion de la chaine 
    reverse_string(message.msg_text);

    message.msg_type = message.pid;

    // Renvoie du message au client
    msgsnd(msgid, &message, sizeof(message), 0);


    return 0;
}
