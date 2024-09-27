#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

// Taille maximal du message
#define MSG_SIZE 256

// Structure de message 
struct msg_buffer {
    long msg_type; // Type du message
    char msg_text[MSG_SIZE]; // Message
    pid_t pid; // nombre de pid
};

int main() {
    // Initialisation 
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Récupération du file de message
    key = ftok("server_client", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Récupère le message
    printf("Entrez une chaîne à envoyer au serveur : ");
    fgets(message.msg_text, MSG_SIZE, stdin);
    message.msg_type = 1;
    message.pid = getpid();

    // Envoie le message au server
    msgsnd(msgid, &message, sizeof(message), 0);

    // Recoit le message inverser du server
    msgrcv(msgid, &message, sizeof(message), getpid(), 0);

    printf("Message inversé reçu du serveur : %s\n", message.msg_text);
    printf("PID du client : %d\n", message.pid);

    // Supprime la file de message
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
