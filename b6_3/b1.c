/* client2.c */

/* 1. Tạo các #include cần thiết để gọi hàm socket */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;             /* số mô tả socket - socket handle */
    int len;
    struct sockaddr_in address;  /* structure sockaddr_in, chứa
                             các thông tin về server AF_INET */
    int result;
    char ch = 'A';

    /* 2. Tạo socket cho trình khách. Tương tự như với trình chủ */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* 3. Đặt tên và gán địa chỉ cần thiết cho socket theo giao thức
       Internet */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);

    /* 4. Thực hiện kết nối */
    result = connect(sockfd, (struct sockaddr*)&address, len);
    if (result == -1) {
        perror("Oops: client problems");
        return 0;
    }

    /* 5. Sau khi socket kết thúc, chúng ta có thể đọc ghi dữ liệu cho
       socket tương tự đọc ghi tiệp file */
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server: %c\n", ch);
    close(sockfd);
    
    return 1;
}
