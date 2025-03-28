#include<stdio.h>
int main(){

    char c, out;

    while(1){
        printf("문자 입력 : ");
        scanf(" %c", &c);
        out = c;
        
        if(c == '0'){
            break;
        }

        if(c >= 65 && c <= 90){
            out += 32;
            printf("%c의 소문자는 %c\n", c, out);
        } else {
            out -= 32;
            printf("%c의 대문자는 %c\n", c, out);
        }
    }

    return 0;
}