#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>  // Thêm cho SIZE_MAX

// Sử dụng size_t thay vì int
int safe_memory(size_t size) {
    // Giới hạn hợp lý, tránh cấp phát quá lớn
    const size_t MAX_ALLOC = 1024;
    
    if (size == 0 || size > MAX_ALLOC) {
        fprintf(stderr, "Invalid size: %zu\n", size);
        return -1;  // Trả về mã lỗi
    }
    
    // Không cần cast trong C (bắt buộc trong C++)
    char *ptr = malloc(size);
    
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;  // Xử lý lỗi rõ ràng
    }
    
    memset(ptr, 0, size);
    printf("Allocated %zu bytes\n", size);
    
    free(ptr);
    // ptr = NULL; // Không cần vì là biến cục bộ
    
    return 0;  // Thành công
}