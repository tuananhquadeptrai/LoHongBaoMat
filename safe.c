#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void safe_copy(const char *input) {
    char buffer[64];
    size_t len = strlen(input);
    
    // Kiểm tra kích thước trước khi sao chép
    if (len < sizeof(buffer)) {
        strncpy(buffer, input, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';  // Đảm bảo null-terminated
        printf("%s\n", buffer);  // Format string an toàn
    } else {
        printf("Input too long\n");
    }
}

void safe_memory(int size) {
    // Kiểm tra giá trị hợp lệ
    if (size <= 0 || size > 1024) {
        return;
    }
    
    char *ptr = (char *)malloc(size);
    
    // Kiểm tra NULL trước khi sử dụng
    if (ptr != NULL) {
        memset(ptr, 0, size);
        printf("Allocated %d bytes\n", size);
        free(ptr);       // Giải phóng đúng cách
        ptr = NULL;      // Đặt NULL sau khi free
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        safe_copy(argv[1]);
    }
    safe_memory(128);
    return 0;
}