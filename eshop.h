#ifndef ESHOP_H
#define ESHOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define CATALOG_SIZE 10
#define NUM_CUSTOMERS 5
#define NUM_ORDERS 10
#define PORT 8080

// Product structure
typedef struct {
    char description[50];
    float price;
    int item_count;
    int requests;
    int sold;
    char failed_customers[NUM_CUSTOMERS * 10];
} Product;

void RequestOrder(int sockfd);
void ProcessOrder(int client_sock, Product *catalog, int *total_requests, int *successful_orders, int *failed_orders, float *income, int client_id);
void PrintReport(Product *catalog, int total_requests, int successful_orders, int failed_orders, float income);

#endif 