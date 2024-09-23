#include <stdio.h>
#include <ctype.h>

typedef enum {
    PUT_ITEM,
    DISPLAY_ITEM,
    SELECT_ITEM,
    CALCULATE_PRICE,
    INPUT_COIN,
    GIVE_CHANGE,
    UPDATE_STOCK,
    FINISHED
} State;

// 定义货物结构体
struct Goods {
    char name;
    int channel;
    int price;
    int quantity;
};

int main() {
    struct Goods goods[5]; // 模拟五个通道，存储货物
    int goodsCount = 0;
    char input[10];
    struct Goods selectedGoods[10]; 
    int selectedCount = 0;
    int totalPrice = 0;
    int currentPrice = 0;
    int addPrice;
    int change;

    State state = PUT_ITEM;

    while (state!= FINISHED) {
        switch (state) {
            case PUT_ITEM:
                // 货物摆放
                printf("请输入货物名称,货物通道标号,货物单价,货物个数(中间用空格隔开）;回车后输入四个0 (加空格)结束摆放。\n");
                if (fgets(input, sizeof(input), stdin) && sscanf(input, "%c%d%d%d", &goods[goodsCount].name, &goods[goodsCount].channel, &goods[goodsCount].price, &goods[goodsCount].quantity) == 4) {
                    goodsCount++;
                    if (goods[goodsCount - 1].name == '0') {
                        state = DISPLAY_ITEM;
                    }
                } else {
                    printf("输入错误，请重新输入货物信息。\n");
                }
                break;
            case DISPLAY_ITEM:
                // 显示货物
                for (int i = 0; i < goodsCount - 1; i++) {
                    printf("%d:", goods[i].channel);
                    for (int j = 0; j < goods[i].quantity; j++) {
                        printf("%c", goods[i].name);
                    }
                    printf(" %d\n", goods[i].price);
                }
                state = SELECT_ITEM;
                break;
            case SELECT_ITEM:
                // 用户购买选择
                printf("请输入购买货物名称，货物通道;回车后输入两个0 (加空格)结束选择。\n");
                if (fgets(input, sizeof(input), stdin) && sscanf(input, "%c%d", &selectedGoods[selectedCount].name, &selectedGoods[selectedCount].channel) == 2) {
                    selectedCount++;
                    if (selectedGoods[selectedCount - 1].name == '0') {
                        state = CALCULATE_PRICE;
                    }
                } else {
                    printf("输入错误，请重新输入选择信息。\n");
                }
                break;
            case CALCULATE_PRICE:
                // 计算总价
                totalPrice = 0;
                for (int i = 0; i < selectedCount - 1; i++) {
                    for (int j = 0; j < goodsCount - 1; j++) {
                        if (selectedGoods[i].name == goods[j].name && selectedGoods[i].channel == goods[j].channel) {
                            totalPrice += goods[j].price;
                            break;
                        }
                    }
                }
                printf("总价为: %d 元。/n", totalPrice);
                state = INPUT_COIN;
                break;
            case INPUT_COIN:
                // 投币阶段
                printf("请输入投币金额(1 元、2 元、5 元): ");
                if (scanf("%d", &addPrice) == 1) {
                    if (addPrice == 1 || addPrice == 2 || addPrice == 5) {
                        currentPrice += addPrice;
                        if (currentPrice < totalPrice) {
                            printf("当前已投币 %d 元，还需投币 %d 元。\n", currentPrice, totalPrice - currentPrice);
                        } else {
                            state = GIVE_CHANGE;
                        }
                    } else {
                        printf("无效的投币金额，请重新输入。\n");
                    }
                } else {
                    while (getchar()!= '\n');
                    printf("输入错误，请重新输入。\n");
                }
                break;
            case GIVE_CHANGE:
                // 找零
                change = currentPrice - totalPrice;
                printf("找零: %d 元", change);
                state = UPDATE_STOCK;
                break;
            case UPDATE_STOCK:
                // 更新货物库存并检查是否售罄
                for (int i = 0; i < selectedCount - 1; i++) {
                    for (int j = 0; j < goodsCount - 1; j++) {
                        if (selectedGoods[i].name == goods[j].name && selectedGoods[i].channel == goods[j].channel) {
                            goods[j].quantity--;
                            if (goods[j].quantity == 0) {
                                printf("货物已售罄。\n");
                            } else if (goods[j].quantity < 0) {
                                printf("错误：库存出现负数。\n");
                            }
                            break;
                        }
                    }
                }
                state = FINISHED;
                break;
        }
    }

    return 0;
}