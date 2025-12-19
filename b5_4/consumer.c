#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE PIPE_BUF

/**
 * Hàm thực hiện logic của tiến trình Consumer:
 * Mở FIFO, đọc dữ liệu cho đến khi EOF (Producer đóng pipe).
 */
int run_consumer() {
    int pipe_fd;
    int res;
    int open_mode = O_RDONLY;
    int bytes_read = 0;
    char buffer[BUFFER_SIZE]; // Kích thước chính xác

    printf("Consumer Process %d starting to read on pipe\n", getpid());
    
    // 1. Mở FIFO ở chế độ đọc (sẽ block cho đến khi Producer mở ghi)
    pipe_fd = open(FIFO_NAME, open_mode);
    
    if (pipe_fd == -1) {
        fprintf(stderr, "Error: Cannot open FIFO for reading\n");
        return EXIT_FAILURE;
    }

    // 2. Đọc dữ liệu cho đến khi hàm read() trả về 0 (End of File - EOF)
    do {
        res = read(pipe_fd, buffer, BUFFER_SIZE);
        
        if (res == -1) {
            // Xảy ra lỗi khi đọc
            perror("Read error on pipe");
            close(pipe_fd);
            return EXIT_FAILURE;
        }
        
        bytes_read += res;
        
    } while (res > 0); // Tiếp tục đọc khi đọc được > 0 byte

    // 3. Đóng pipe
    (void) close(pipe_fd);
    printf("Consumer Process %d finished, **%d bytes read**\n", getpid(), bytes_read);
    
    // Optional: Xóa FIFO sau khi hoàn tất
    // unlink(FIFO_NAME); 
    
    return EXIT_SUCCESS;
}

int main() {
    return run_consumer();
}