#include <stdio.h>
int func()
{

    char string[32] = {}; 
    unsigned int a = 99; 
    int val = 39;
    //snprintf(string, 32, "%04d%02d%02d%02d%2d%2d%03lu", val+1900 ,val, val, val, val, val, a); 
    snprintf(string, 32, "%04d%02d%02d%02d%2d%03lu", val+1900 ,val, val, val, val, a); 
    printf("string: %s\n", string);
    printf("expect: 193939393939099\n");
    return 0;
}
int main()
{
    func();
    return 0;
}
