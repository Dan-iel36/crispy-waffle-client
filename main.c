#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "job.h"

#define PORT 8080
#define SERVER_ADDRESS "127.0.0.1"


int main() {

    /*
     * This is the client side
     * the user sends printer option
     * nb of pages to print
     * priority
     */
    int printer = 1;
    int pages = 5;
    int priority = 0;
    int rest = 0;

    int sock = 0;
    struct sockaddr_in serv_addr;
// Création du socket client
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Échec de la création du socket client");
        exit(EXIT_FAILURE);
    }
    //Programmation systèmes & réseaux –
    //Sockets et TCP/IP
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
// Convertir l'adresse IPv4 et affecter au socket client
    if (inet_pton(AF_INET, SERVER_ADDRESS,
                  &serv_addr.sin_addr) <= 0) {
        perror("Adresse invalide / Adresse non supportée");
        exit(EXIT_FAILURE);
    }
// Connexion au serveur
    if (connect(sock, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) {
        perror("Connexion échouée");
        exit(EXIT_FAILURE);
    }
// envoyer/recevoir des données avec le serveur via sock
    struct job myjob = {
            1, 1, 1
    };

    while(1){
        send(sock, &myjob, sizeof(struct job), 0);
        printf("%d, %d, %d, %d \n", sock, myjob.priority, myjob.pages, myjob.printerId);
        fflush(stdout);
        sleep(rand() % 20 + 1);

    }


    //printf("%s", myjob);



// Receive data
//recv(sock, buffer, 1024, 0);

    close(sock);


    return 0;
}
