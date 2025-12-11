
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_BUFFER_SIZE 256
#define MAX_INPUT_SIZE 1024

// Safe string copy with bounds checking
int safe_string_copy(char *dest, size_t dest_size, const char *src) {
    if (!dest || !src || dest_size == 0) {
        return -1;
    }
    
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
    return 0;
}

// Safe buffer handling
void process_input_safely(const char *user_input) {
    char buffer[MAX_BUFFER_SIZE];
    
    if (!user_input) {
        fprintf(stderr, "Error: NULL input\n");
        return;
    }
    
    if (safe_string_copy(buffer, sizeof(buffer), user_input) != 0) {
        fprintf(stderr, "Error: Failed to copy input\n");
        return;
    }
    
    printf("Processed: %s\n", buffer);
}

// Safe memory allocation with cleanup
char* allocate_and_initialize(size_t size) {
    if (size == 0 || size > MAX_INPUT_SIZE) {
        return NULL;
    }
    
    char *ptr = (char *)malloc(size);
    if (!ptr) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    
    memset(ptr, 0, size);
    return ptr;
}

// Safe array access with bounds checking
int safe_array_write(char *array, size_t array_size, size_t index, char value) {
    if (!array || index >= array_size) {
        return -1;
    }
    
    array[index] = value;
    return 0;
}

// Safe integer arithmetic with overflow check
int safe_add(int a, int b, int *result) {
    if (!result) {
        return -1;
    }
    
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        return -1;  // Overflow would occur
    }
    
    *result = a + b;
    return 0;
}

// Resource management with proper cleanup
int process_file_safely(const char *filename) {
    FILE *file = NULL;
    char *buffer = NULL;
    int result = -1;
    
    if (!filename) {
        goto cleanup;
    }
    
    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file\n");
        goto cleanup;
    }
    
    buffer = allocate_and_initialize(MAX_BUFFER_SIZE);
    if (!buffer) {
        goto cleanup;
    }
    
    if (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        printf("Read: %s", buffer);
        result = 0;
    }
    
cleanup:
    if (buffer) {
        free(buffer);
    }
    if (file) {
        fclose(file);
    }
    
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input>\n", argv[0]);
        return 1;
    }
    
    process_input_safely(argv[1]);
    
    char *data = allocate_and_initialize(100);
    if (data) {
        safe_string_copy(data, 100, "Safe data");
        printf("Data: %s\n", data);
        free(data);
    }
    
    int sum;
    if (safe_add(100, 200, &sum) == 0) {
        printf("Sum: %d\n", sum);
    }
    
    return 0;
}