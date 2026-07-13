#include <stdio.h>

int main()
{
    int a = 8;
    int b = 11;
    int c = -8;

    if (a >= b)
    {
        return a;
    }
    else if (a <= b)
    {
        return b;
    }
    else if (a >= c)
    {
        return a;
    }
    else if (a <= c)
    {
        return c;
    }
    else if (b >= c)
    {
        return c;
    }
    else
    {
        return b;
    }
}