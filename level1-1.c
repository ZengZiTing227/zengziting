#include <stdio.h>

int main() {
    char item;
    int channelnumber;
    int price;
    int quantity;

    printf("请输入货物名称,货物通道标号,货物单价,货物个数(中间用空格隔开）：");
   
    scanf("%c%d%d%d", &item,&channelnumber,&price,&quantity);

    printf("%d:",channelnumber);

    for ( int i = 0; i < quantity; i++)
    { printf("%c",item);
    }
    
    printf(" %d",price);

    return 0;
}

