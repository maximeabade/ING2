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
    double result;

    // Création de la clé
    key = ftok("calculator", 65);

    // Création de la file de messages
    msgid = msgget(key, 0666 | IPC_CREAT);

    message.msg_type = 1;

    printf("Entrer une opération (exemple: + 3 2): ");
    scanf("%c %lf %lf", &message.op.operator, &message.op.operand1, &message.op.operand2);
    message.pid = getpid();

    // Envoi du message
    msgsnd(msgid, &message, sizeof(message), 0);

    // Réception de la réponse
    msgrcv(msgid, &message, sizeof(message), getpid(), 0);

    printf("Résultat reçu du serveur : %.2lf\n", message.op.result);

    // Destruction de la file de messages
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
