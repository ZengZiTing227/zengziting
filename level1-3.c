#include <stdio.h>
#include <ctype.h>

int main() {
    char item;
    int channelnumber;
    int price;
    int quantity;
    int totalprice;
    int addprice;
    int currentprice;
    int change;
    int rightinput = 0;
    int buy;
    int number;

    // 货物摆放
    while (1) {
        printf("请输入货物名称（单个字符）,货物通道标号,货物单价,货物个数(中间用空格隔开）：");
        if (scanf(" %c%d%d%d", &item, &channelnumber, &price, &quantity) == 4) {
            break;
        } else {
            while (getchar()!= '\n');
            printf("输入错误，请重新输入货物信息。\n");
        }
    }

    printf("%d:", channelnumber);
    for (int i = 0; i < quantity; i++) {
        printf("%c", item);
    }
    printf(" %d\n", price);

    // 用户购买
    while (1) {
        while (1) {
            printf("是否购买货物,购买请输入1,不购买请输入0:");
            if (scanf("%d", &buy) == 1) {
                break;
            } else {
                while (getchar()!= '\n');
                printf("输入错误，请重新输入。\n");
            }
        }

        if (buy == 0) {
            break;
        } else if (buy == 1) {
            while (1) {
                printf("请输入购买货物，货物通道标号，购买数量（中间用空格隔开）：");
                if (scanf("%c%d%d", &item, &channelnumber, &number) == 3) {
                    totalprice = price * number;
                    break;
                } else {
                    while (getchar()!= '\n');
                    printf("输入错误，请重新输入。\n");
                }
            }

            currentprice = 0;
            printf("总价为 %d 元。\n", totalprice);
            while (currentprice < totalprice) {
                while (1) {
                    printf("请输入投币金额(1元、2元、5元): ");
                    if (scanf("%d", &addprice) == 1) {
                        break;
                    } else {
                        while (getchar()!= '\n');
                        printf("输入错误，请重新输入。\n");
                    }
                }
                if (addprice!= 1 && addprice!= 2 && addprice!= 5) {
                    printf("无效的投币金额，请重新输入。\n");
                    continue;
                }
                currentprice += addprice;
                printf("当前已投币 %d 元，还需投币 %d 元。\n", currentprice, totalprice - currentprice);
            }

            change = currentprice - totalprice;
            printf("找零: %d 元", change);

            quantity -= number;
            if (quantity > 0) {
                printf("还有库存。\n");
            } else if (quantity == 0) {
                printf("货物刚好售罄。\n");
            } else {
                printf("货物已售罄一段时间了，库存为负数。\n");
            }
        }
    }
    return 0;
}