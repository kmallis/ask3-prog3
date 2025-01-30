#include "eshop.h"

void PrintReport(Product *catalog, int total_requests, int successful_orders, int failed_orders, float income) {

    printf("\n-------- Report --------\n");

    for (int i = 0; i < CATALOG_SIZE; i++) {    //for all the products of the catalog, print the statistics

        printf("-> %s\n", catalog[i].description);
        printf("  Requests: %d\n", catalog[i].requests);
        printf("  Sold: %d\n", catalog[i].sold);

        if (strlen(catalog[i].failed_customers) > 0) {
            printf("  Unserved Customers: %s\n", catalog[i].failed_customers);
        } else {
            printf("  Unserved Customers: None\n");
        }
    }

    //print the summary report of the e-shop
    printf("\nTotal Requests: %d\n", total_requests);
    printf("Successful Orders: %d\n", successful_orders);
    printf("Failed Orders: %d\n", failed_orders);
    printf("Total Revenue: €%.2f\n", income);
}


void ProcessOrder(int client_sock, Product *catalog, int *total_requests, int *successful_orders, int *failed_orders, float *income, int client_id) {
    for (int j = 0; j < NUM_ORDERS; j++) {
        int product_index;
        recv(client_sock, &product_index, sizeof(product_index), 0);

        char response[100];
        (*total_requests)++;

        if (product_index >= 0 && product_index < CATALOG_SIZE) {
            catalog[product_index].requests++;

            if (catalog[product_index].item_count > 0) {
                catalog[product_index].item_count--;
                catalog[product_index].sold++;
                *income += catalog[product_index].price;
                (*successful_orders)++;
                snprintf(response, sizeof(response), "Order successful: %s - €%.2f", catalog[product_index].description, catalog[product_index].price);
            } else {
                snprintf(response, sizeof(response), "Order failed: Product unavailable");
                (*failed_orders)++;
                char failed_entry[20];
                snprintf(failed_entry, sizeof(failed_entry), "Client %d ", client_id);
                strncat(catalog[product_index].failed_customers, failed_entry, sizeof(catalog[product_index].failed_customers) - strlen(catalog[product_index].failed_customers) - 1);
            }
        } else {
            snprintf(response, sizeof(response), "Order failed: Invalid product");
            (*failed_orders)++;
        }

        send(client_sock, response, strlen(response) + 1, 0);
        sleep(1);
    }
}


int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    Product catalog[CATALOG_SIZE] = {
        {"Product 1", 20.00, 2, 0, 0, ""},
        {"Product 2", 17.99, 2, 0, 0, ""},
        {"Product 3", 8.50, 2, 0, 0, ""},
        {"Product 4", 12.30, 2, 0, 0, ""},
        {"Product 5", 25.00, 2, 0, 0, ""},
        {"Product 6", 5.00, 2, 0, 0, ""},
        {"Product 7", 30.00, 2, 0, 0, ""},
        {"Product 8", 45.50, 2, 0, 0, ""},
        {"Product 9", 22.75, 2, 0, 0, ""},
        {"Product 10", 18.99, 2, 0, 0, ""}
    };

    int total_requests = 0, successful_orders = 0, failed_orders = 0;
    float income = 0.0;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, NUM_CUSTOMERS);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        ProcessOrder(client_sock, catalog, &total_requests, &successful_orders, &failed_orders, &income, i + 1);
        close(client_sock);
    }

    PrintReport(catalog, total_requests, successful_orders, failed_orders, income);
    close(server_sock);
    return 0;
}
