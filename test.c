#include <stdio.h>

int main(void)
{
    int a = 42;
    void *p = &a;

    printf("=== Test %%p Flags ===\n");
    printf("1. Normal       : [%p]\n", p);
    
    // Width & Minus (มีผลแน่นอน)
    printf("2. Width (20)   : [%20p]\n", p);
    printf("3. Minus (-20)  : [%-20p]\n", p);
    
    // Zero & Precision (ต้องสังเกตผลลัพธ์ว่าเครื่องคุณทำยังไง)
    printf("4. Zero (020)   :  [%.30p]\n", p);
    printf("5. Precision(.20): [%030.30p]\n", p);

    printf("6. NULL Pointer : [%p]\n", NULL);

    printf("%10.5p", 0);
    
    return (0);
}