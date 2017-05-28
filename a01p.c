#include <stdio.h>
#include <stdlib.h>

static char *studentName = "Casey Benson";

// report whether machine is big or small endian
void bigOrSmallEndian()
{
    int test = 0x44000048;
    char *tst = (char *) &test;

    printf("byte order: ");

    if (0x48 == *tst)
        printf("little-endian\n\n");
    else if (0x44 == *tst)
        printf("big-endian\n\n");

    tst = NULL;
}

// get next int (entered in hex) using scanf()
// returns 1 (success) or 0 (failure)
// if call succeeded, return int value via i pointer
int getNextHexInt(int *i)
{
    // replace this code with the call to scanf()
    return scanf("%x", i);
}

// print requested data for the given number
void printNumberData(int i)
{
    int signBit     = i & 0x80000000;
    int expBits     = i & 0x7f800000;
    int significand = i & 0x007fffff;

    expBits = expBits >> 23;

    if(signBit != 0)
        signBit = 1;

    printf("signBit %i, ", signBit);
    printf("expBits %3i, ", expBits);
    printf("FractBits 0x%08X\n", significand);

    if(expBits == 0 && significand == 0)
    {
        if(signBit == 0)
            printf("+zero\n");
        else
            printf("-zero\n");
    }

    else if(expBits == 0 && significand != 0)
        printf("denormalized: exp = %ei\n", (1-127));

    else if(expBits != 0 && expBits != 255)
        printf("normalized: exp = %3i\n", (expBits - 127));

    else if(expBits == 255 && significand == 0)
    {
        if (signBit == 0)
            printf("+infinity\n");
        else
            printf("-infinity\n");
    }

    else if(expBits == 255 && significand >= 0x00400000)
        printf("QNaN\n");

    else if(expBits == 255 && significand >= 0x00200000)
        printf("SNaN\n");

    printf("\n");
}

int main(int argc, char **argv)
{
    int     i;                              // number currently being analyzed
    int     nValues;                        // number of values successfully parsed by scanf

    printf("CS201 - A01p - %s\n\n", studentName);
    bigOrSmallEndian();
    for (;;) {
        if (argc == 1)                      // allow grading script to control ...
            printf("> ");                   // ... whether prompt character is printed
        nValues = getNextHexInt(&i);
        printf("0x%08X\n", i);
        if (! nValues) {                    // encountered bad input
            printf("bad input\n");
            while (getchar() != '\n') ;     // flush bad line from input buffer
            continue;
            }
        printNumberData(i);
        if (i == 0)
            break;
        }
    printf("\n");
    return 0;
}
