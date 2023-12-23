#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

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
    struct job myjob;
    char printer[16];
    int userPrinter;
    int pages;
    int priority;
    int rest = 0;

    char *ipArray[4];
    ipArray[1] = "123.0.213.0";
    ipArray[2] = "123.0.213.1";
    ipArray[3] = "123.0.213.2";


    printf("select printer 1 - 3. 0 exists the program \n");
    scanf("%d", &userPrinter);
    if (userPrinter == 0) {
        printf("app outed");
    } else if (userPrinter == 1) {
        strcpy(printer, ipArray[1]);
    } else if (userPrinter == 2) {
        strcpy(printer, ipArray[2]);
    } else if (userPrinter == 3) {
        strcpy(printer, ipArray[3]);
    } else {
        printf("something went wrong not sure what but pls restart O__- \n");
    }
    printf("%s \n", printer);
    strcpy(myjob.printerId, printer);

    printf("select number of pages 1 - 10. 0 exists the program \n");
    scanf("%d", &pages);
    if (pages == 0) {
        printf("app outed \n");
    } else if (pages >= 1 && pages <= 10) {
        pages = pages;
    } else {
        printf("something went wrong not sure what but pls restart O__- \n");
    }
    printf("%d \n", pages);
    myjob.pages = pages;

    printf("select priority of pages 1 - 2. 0 exists the program \n");
    scanf("%d", &priority);
    if (priority == 0) {
        printf("app outed \n");
    } else if (priority > 0 && priority < 3) {
        priority = priority;
    } else {
        printf("something went wrong not sure what but pls restart O__- \n");
    }
    printf("%d \n", priority);
    myjob.priority = priority;

    printf("you asked the printer %s to print %d copies with %d stars \n", myjob.printerId, myjob.pages,
           myjob.priority);


    int sock = 0;
    struct sockaddr_in serv_addr;

    // Création du socket client
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Échec de la création du socket client");
        exit(EXIT_FAILURE);
    }

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

    //while (1) {
         for (int i = 0; i < 2; ++i) {

        send(sock, &myjob, sizeof(struct job), 0);
        printf("%d, %d, %d, %s \n", sock, myjob.priority, myjob.pages, myjob.printerId);
        fflush(stdout);
        int time = rand() % 20 + 1;
        printf("sleeping for %d \n", time);
        sleep(time);

        //close(sock);
        //breakout of loop
         }


    //}


    return 0;
}
