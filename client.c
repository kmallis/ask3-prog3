#include "eshop.h"

void RequestOrder(int sockfd) {
    srand(time(NULL) ^ (getpid() << 16));

    for (int j = 0; j < NUM_ORDERS; j++) {
        int product_index = rand() % CATALOG_SIZE;
        send(sockfd, &product_index, sizeof(product_index), 0);

        char response[100];
        recv(sockfd, response, sizeof(response), 0);
        printf("Client: %s\n", response);

        sleep(1);
    }
    close(sockfd);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    RequestOrder(sockfd);

    return 0;
}
