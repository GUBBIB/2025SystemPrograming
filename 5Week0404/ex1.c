#include <stdio.h>

void print_binary(unsigned char n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
}

int count_ones(unsigned char n) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if ((n >> i) & 1) {
            count++;
        }
    }
    return count;
}

void print_upper_4bits(unsigned char n) {
    // 상위 4비트를 오른쪽으로 4비트 시프트하면 하위 4비트에 옮겨짐
    unsigned char upper = n >> 4;
    for (int i = 3; i >= 0; i--) {
        printf("%d", (upper >> i) & 1);
    }
}

int main() {
    int input;

    printf("0부터 255 사이의 숫자를 입력하세요: ");
    scanf("%d", &input);

    if (input < 0 || input > 255) {
        printf("입력값이 범위를 벗어났습니다.\n");
        return 1;
    }

    unsigned char value = (unsigned char)input;

    printf("입력값의 8비트 2진수: ");
    print_binary(value);
    printf("\n");

    printf("상위 4비트: ");
    print_upper_4bits(value);
    printf("\n");

    int ones = count_ones(value);
    printf("1의 개수: %d\n", ones);

    return 0;
}
