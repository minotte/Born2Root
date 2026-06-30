#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <stdint.h>

int    letter_to_index(char letter)
{
    char *array;
    
    array = strdup("isrveawhobpnutfg");
    
    for (int i = 0; i < 16; i++)
    {
        if (array[i] == letter)
        return i;
    }
    return -1;
}

    
char build_char(int index)
{
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;

    if (index > -1)
    {
        while (alphabet[i])
        {
            if ((alphabet[i] & 0xf) == index)
                return alphabet[i];
            i++;
        }
        return '?';
    }
}

int main(void)
{
    char target[] = "giants";
    char result [7];
    
    for (int i = 0; i < 6; i++)
    {
        int index = letter_to_index(target[i]);
        result[i] = build_char(index);
    }
    result[6] = '\n';
    printf("%s\n", result);
    return 0;
}