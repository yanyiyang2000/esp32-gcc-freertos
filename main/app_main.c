/* Standard library API */
#include <string.h>         // memset()
#include <errno.h>          // errno
#include <lwip/netdb.h>     // addrinfo struct, getaddrinfo()
#include <lwip/sockets.h>   // AF_, SOCK_, SHUT_ defines, socket(), connect(), shutdown(), recv()

/* ESP-IDF API */
#include "esp_log.h"

/*****************************************************************************/
/* Description:                                                              */
/*   A simple echo client.                                                   */
/*                                                                           */
/* Author:                                                                   */
/*   Yiyang Yan                                                              */
/*                                                                           */
/* Date:                                                                     */
/*   2024/06/27                                                              */
/*****************************************************************************/

#define BUFFER_SIZE 256

static const char *TAG = "Client";

void app_main(void) {
    struct addrinfo hints;
    struct addrinfo *result;
    const char      *host = "192.168.1.123";
    const char      *port = "12345";
    int             status;
    int             sockfd;
    ssize_t         recv_len;
    ssize_t         send_len;
    char            buffer[BUFFER_SIZE] = {0};

    /* Establish TCP connection with the server */
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    status = lwip_getaddrinfo(host, port, &hints, &result);
    if (status != 0) {
        ESP_LOGE(TAG, "getaddrinfo error: %d", errno);
    }

    sockfd = lwip_socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sockfd < 0) {
        ESP_LOGE(TAG, "socket error: %d", errno);
    }

    status = lwip_connect(sockfd, result->ai_addr, result->ai_addrlen);
    if (status != 0) {
        ESP_LOGE(TAG, "connect error: %d", errno);
        lwip_shutdown(sockfd, SHUT_RDWR);
        return;
    } else {
        ESP_LOGI(TAG, "Connected to server.");
    }

    lwip_freeaddrinfo(result);

    /* Communicate with the server */
    while (1) {
        // receive message from server
        recv_len = lwip_recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
        if (recv_len < 0) {
            if (errno == ENOTCONN) {
                ESP_LOGE(TAG, "Server disconnected.");
            } else {
                ESP_LOGE(TAG, "recv error: %d", errno);
            }
            
            lwip_shutdown(sockfd, SHUT_RDWR);
            return;
        }

        // add a null byte to the end of the received message
        buffer[recv_len] = '\0';

        // echo message back to the server
        send_len = lwip_send(sockfd, buffer, BUFFER_SIZE, 0);
        if (send_len < 0) {
            ESP_LOGE(TAG, "send error: %d", errno);
            lwip_shutdown(sockfd, SHUT_RDWR);
            return;
        }
    }
}
