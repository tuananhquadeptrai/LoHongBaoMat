#include <stdio.h>
#include <string.h>

void safe_function() {
    char buffer[16];
    char large_input[64];
    
    memset(large_input, 'A', 63);
    large_input[63] = '\0';
    
    /* FIX: use strncpy with buffer size limit */
    strncpy(buffer, large_input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    printf("Buffer: %s\n", buffer);
}

int main() {
    safe_function();
    return 0;
}
