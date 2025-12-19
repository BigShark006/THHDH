#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "my_fifo"
// BUFFER_SIZE tương đương kích thước block của pipe (PIPE_BUF)
#define BUFFER_SIZE PIPE_BUF 
// TEN_MEG là 10 MB
#define TEN_MEG (1024 * 1024 * 10)

/**
 * Hàm thực hiện logic của tiến trình Producer:
 * Kiểm tra/tạo FIFO, mở FIFO, và ghi 10MB dữ liệu.
 */
int run_producer() {
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    int bytes_sent = 0;
    char buffer[BUFFER_SIZE]; // Kích thước chính xác

    // 1. Kiểm tra và tạo FIFO nếu chưa tồn tại
    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, (S_IRUSR | S_IWUSR));
        if (res != 0) {
            fprintf(stderr, "Error: Cannot create FIFO object [%s]\n", FIFO_NAME);
            return EXIT_FAILURE;
        }
    }

    // Khởi tạo buffer với dữ liệu 'A' để đảm bảo không ghi dữ liệu rác
    memset(buffer, 'A', BUFFER_SIZE);

    printf("Producer Process %d starting to write on pipe\n", getpid());
    
    // 2. Mở FIFO ở chế độ ghi (sẽ block cho đến khi Consumer mở đọc)
    pipe_fd = open(FIFO_NAME, open_mode);
    
    if (pipe_fd == -1) {
        fprintf(stderr, "Error: Cannot open FIFO for writing\n");
        return EXIT_FAILURE;
    }

    // 3. Ghi 10MB dữ liệu
    while (bytes_sent < TEN_MEG) {
        // Ghi một block dữ liệu
        res = write(pipe_fd, buffer, BUFFER_SIZE);
        
        if (res == -1) {
            // Xảy ra lỗi khi ghi (ví dụ: Consumer đóng pipe đột ngột)
            perror("Write error on pipe");
            close(pipe_fd);
            return EXIT_FAILURE;
        }
        
        bytes_sent += res;
    }

    // 4. Đóng pipe (Điều này sẽ gửi tín hiệu EOF tới Consumer)
    (void) close(pipe_fd);
    printf("Producer Process %d finished, **%d bytes sent**\n", getpid(), bytes_sent);
    
    return EXIT_SUCCESS;
}

int main() {
    return run_producer();
}
