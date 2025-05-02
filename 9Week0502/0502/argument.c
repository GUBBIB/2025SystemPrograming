#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("총 %d개의 인자가 전달되었습니다.\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
