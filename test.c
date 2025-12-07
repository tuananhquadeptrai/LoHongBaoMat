/* CWE-122: Heap Buffer Overflow */
#include <stdlib.h>
#include <string.h>

void bad()
{
    char *data;
    data = (char *)malloc(50 * sizeof(char));
    
    memset(data, 'A', 50-1);
    data[50-1] = '\0';
    
    char source[100];
    memset(source, 'B', 100-1);
    source[100-1] = '\0';
    
    /* FLAW: copies 100 bytes into 50 byte buffer */
    strcpy(data, source);
    
    free(data);
}

int main()
{
    bad();
    return 0;
}