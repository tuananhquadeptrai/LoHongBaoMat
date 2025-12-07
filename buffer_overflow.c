#include <stdio.h>
#include <string.h>

void vulnerable_function() {
    char buffer[16];
    char large_input[64];
    
    memset(large_input, 'A', 63);
    large_input[63] = '\0';
    
    /* FLAW: copies 64 bytes into 16 byte buffer - stack buffer overflow */
    strcpy(buffer, large_input);
    
    printf("Buffer: %s\n", buffer);
}

int main() {
    vulnerable_function();
    return 0;
}
