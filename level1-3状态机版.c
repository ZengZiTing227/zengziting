#include <stdio.h>
#include <ctype.h>

typedef enum {
    PUT_ITEM,
    BUY_DECISION,
    BUY,
    INPUT_COIN,
    FINISHED
} State;

int main() {
    char item;
    int channelnumber;
    int price;
    int quantity;
    int totalprice;
    int addprice;
    int currentprice;
    int change;
    int buy;
    int number;

    State state = PUT_ITEM;

    while (state!= FINISHED) {
        switch (state) {
            case PUT_ITEM:
                // 货物摆放
                printf("请输入货物名称（单个字符）,货物通道标号,货物单价,货物个数(中间用空格隔开）:");
                if (scanf(" %c%d%d%d", &item, &channelnumber, &price, &quantity) == 4) {
                    printf("%d:", channelnumber);
                    for (int i = 0; i < quantity; i++) {
                        printf("%c", item);
                    }
                    printf(" %d\n", price);
                    state = BUY_DECISION;
                } else {
                    while (getchar()!= '\n');
                    printf("输入错误，请重新输入货物信息。\n");
                }
                break;
            case BUY_DECISION:
                // 用户是否购买
                printf("是否购买货物,购买请输入 1,不购买请输入 0:");
                if (scanf("%d", &buy) == 1) {
                    if (buy == 0) {
                        state = FINISHED;
                    } else if (buy == 1) {
                        state = BUY;
                    } else {
                        while (getchar()!= '\n');
                        printf("输入错误，请重新输入。\n");
                    }
                } else {
                    while (getchar()!= '\n');
                    printf("输入错误，请重新输入。\n");
                }
                break;
            case BUY:
                // 用户购买
                printf("请输入购买货物，货物通道标号，购买数量（中间用空格隔开）：");
                if (scanf("%c%d%d", &item, &channelnumber, &number) == 3) {
                    totalprice = price * number;
                    currentprice = 0;
                    printf("总价为 %d 元。\n", totalprice);
                    state = INPUT_COIN;
                } else {
                    while (getchar()!= '\n');
                    printf("输入错误，请重新输入。\n");
                }
                break;
            case INPUT_COIN:
                // 投币
                printf("请输入投币金额(1 元、2 元、5 元): ");
                if (scanf("%d", &addprice) == 1) {
                    if (addprice!= 1 && addprice!= 2 && addprice!= 5) {
                        printf("无效的投币金额，请重新输入。\n");
                    } else {
                        currentprice += addprice;
                        if (currentprice < totalprice) {
                            printf("当前已投币 %d 元，还需投币 %d 元。\n", currentprice, totalprice - currentprice);
                        } else {
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
                            state = BUY_DECISION;
                        }
                    }
                } else {
                    while (getchar()!= '\n');
                    printf("输入错误，请重新输入。\n");
                }
                break;
        }
    }

    return 0;
}