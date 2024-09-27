#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct operation {
    char operator;
    double operand1;
    double operand2;
    double result;
};

struct msg_buffer {
    long msg_type;
    struct operation op;
    int pid;
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Création de la clé
    key = ftok("calculator", 65);

    // Création de la file de messages
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Attente de la requête du client
    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    // Traitement de l'opération
    double result;
    switch (message.op.operator) {
        case '+':
            result = message.op.operand1 + message.op.operand2;
            break;
        case '-':
            result = message.op.operand1 - message.op.operand2;
            break;
        case '*':
            result = message.op.operand1 * message.op.operand2;
            break;
        case '/':
            if (message.op.operand2 != 0) {
                result = message.op.operand1 / message.op.operand2;
            } else {
                printf("Division par zéro\n");
                return 1;
            }
            break;
        default:
            printf("Opérateur invalide\n");
            return 1;
    }

    // Mise à jour du message avec le résultat
    message.msg_type = message.pid;
    message.op.result = result;
    printf("Opération reçue du client : %.2lf %c %.2lf\n", message.op.operand1, message.op.operator, message.op.operand2);
    printf("Résultat de l'opération : %.2lf\n", message.op.result);


    // Envoi de la réponse
    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        return 1;
    }


    // Destruction de la file de messages
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }

    return 0; 
}
