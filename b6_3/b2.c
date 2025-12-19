/* serverr.c */

/* 1. Tạo các #include cần thiết */
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#include <stdlib.h> /* đã thêm để dùng exit() */

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    /* Dòng này dùng cho việc khởi tạo và xử lý khi socket kết thúc */
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof(server_address);
    
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    /* Lắng nghe: SIGNAL(SIGCHLD, SIG_IGN) để tránh zombie process */
    listen(server_sockfd, 5);
    signal(SIGCHLD, SIG_IGN);

    /* Vòng lặp để chờ và xử lý kết nối của trình khách */
    while (1)
    {
        char ch;

        printf("server waiting...\n");

        /* Chờ và chấp nhận kết nối */
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

        /* Hàm fork() tạo tiến trình con để xử lý kết nối, kiểm tra xem
           hiện tại đang là tiến trình cha hay tiến trình con */
        if (fork() == 0)
        {
            /* Tiến trình con: Xử lý kết nối */
            
            read(client_sockfd, &ch, 1);
            sleep(3);
            ch++;
            write(client_sockfd, &ch, 1);
            close(client_sockfd);
            exit(0);
        }
        else
        {
            /* Tiến trình cha: Đóng socket dành cho client, tiếp tục chờ
               kết nối mới */
            close(client_sockfd);
        }
    }
}
