#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#include "job.h"

#define PORT 8080
#define SERVER_ADDRESS "127.0.0.1"

// Function to generate a random priority level between 1 and 3
int randomPriority() {
    srand(time(NULL));
    int priority = rand() % 3 + 1;
    printf("%d \n", priority);
    return priority;
}

// Function to randomly select a printer from the given IP addresses
void randomPrinter(char *printer) {
    char *ipArray[3];
    ipArray[0] = "123.0.213.0";
    ipArray[1] = "123.0.213.1";
    ipArray[2] = "123.0.213.2";

    int userPrinter = rand() % 3;
    if (strlen(ipArray[userPrinter]) < 16) {
        strcpy(printer, ipArray[userPrinter]);
        printf("%s : %d \n", printer, userPrinter);
    } else {
        printf("Error: Printer ID too long\n");
    }
}


int main() {

    /*
     * This is the client side
     * the user sends printer option
     * nb of pages to print and
     * priority
     */
    struct job myjob;
    char printer[16];
    int pages;


    // Generate a random number of pages between 1 and 10
    srand(time(NULL));
    pages = rand() % 10 + 1;
    printf("%d \n", pages);
    myjob.pages = pages;

    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create a client socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Échec de la création du socket client");
        exit(EXIT_FAILURE);
    }

    // Set up the socket address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert the IPv4 address and assign it to the client socket
    if (inet_pton(AF_INET, SERVER_ADDRESS,
                  &serv_addr.sin_addr) <= 0) {
        perror("Adresse invalide / Adresse non supportée");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) {
        perror("Connexion échouée");
        exit(EXIT_FAILURE);
    }

    // Loop to send multiple print jobs
    for (int i = 0; i < myjob.pages; ++i) {
        // Select a random printer
        randomPrinter(myjob.printerId);

        // Assign a random priority
        myjob.priority = randomPriority();

        // Send the print job to the server
        send(sock, &myjob, sizeof(struct job), 0);

        printf("sockID : %d, priority : %d, pages : %d / %d, printerId : %s \n", sock, myjob.priority, i + 1, myjob.pages,
               myjob.printerId);

        fflush(stdout);

        int time = rand() % 20 + 1;
        printf("sleeping for %d \n", time);

        // Sleep for a random amount of time before sending the next print job
        sleep(time);
    }

    // Close the socket
    close(sock);

    return 0;
}