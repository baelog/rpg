// #include <stdio.h>

#define CHECK_BIT(v, p) (v & (1 << p))
#define MOD8(n) ((n & 0b111))
#define REV_VALUE(n) (7 - MOD8(i))

int crcCreate(void *bytes, int size, int key, char keySize)
{
    char *ptr = (char*)bytes;
    int bitsNumber = size << 3;
    int res = 0;
    int i = 0;

    while (i < bitsNumber) {
        while (!CHECK_BIT(res, keySize - 1) && i < bitsNumber) {
            res <<= 1;
            res |= (ptr[i >> 3] & (1 << REV_VALUE(i))) >> REV_VALUE(i);
            i++;
        }
        if (CHECK_BIT(res, keySize - 1))
           res ^= key;
    }
    return res;
}

// int main(void)
// {
//     char test[] = {0b1011, 0b00110000};
//     int res = crcCreate(test, sizeof(test), 0b10011, 5);

//     printf("\n");
//     for (int i = 0; i < 4; i++) {
//         printf("%c\n", ((res & (1 << i)) >> i) + '0');
//     }
//     printf("\n");
//     printf("\n");
    
//     char test2[] = {0b1011, 0b00110100};
//     int res2 = crcCreate(test2, sizeof(test2), 0b10011, 5);

//     printf("\n");
//     for (int i = 0; i < 4; i++) {
//         printf("%c\n", ((res2 & (1 << i)) >> i) + '0');
//     }
    
// }