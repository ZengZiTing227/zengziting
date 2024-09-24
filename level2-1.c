#include <stdio.h>
#include <ctype.h>

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

    // 货物摆放
    printf("请输入货物名称,货物通道标号,货物单价,货物个数(中间用空格隔开）;回车后输入四个0 (加空格)结束摆放。\n");
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%c%d%d%d", &goods[goodsCount].name, &goods[goodsCount].channel, 
        &goods[goodsCount].price, &goods[goodsCount].quantity) == 4) {
            // 检查通道内是否已存放不同货物
            int channelavaliable = 0;
            for (int i = 0; i < goodsCount; i++) {
                if (goods[i].channel == goods[goodsCount].channel && goods[i].name!= goods[goodsCount].name) {
                    channelavaliable = 1;
                    break;
                }
            }
            if (channelavaliable) {
                printf("该通道已存放其他货物，不能放置不同货物。\n");
            } else {
                goodsCount++;
                if (goods[goodsCount - 1].name == '0' ) {
                    break;
                }
            }
        } else {
            printf("输入错误，请重新输入货物信息。\n");
        }
    }

    // 显示货物
    for (int i = 0; i < goodsCount - 1; i++) {
        printf("%d:", goods[i].channel);
        for (int j = 0; j < goods[i].quantity; j++) {
            printf("%c", goods[i].name);
        }
        printf(" %d\n", goods[i].price);
    }

    // 用户购买
    struct Goods selectedGoods[10]; // 用户选择的货物
    int selectedCount = 0;
    char choice;

    printf("请输入购买货物名称，货物通道;回车后输入两个0 (加空格)结束选择。\n");
    while (1) {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%c%d", &selectedGoods[selectedCount].name, &selectedGoods[selectedCount].channel) == 2) {
            selectedCount++;
            if (selectedGoods[selectedCount - 1].name == '0' ) {
                break;
            }
        } else {
            printf("输入错误，请重新输入选择信息。\n");
        }
    }

    // 计算总价
    int totalPrice = 0;
    for (int i = 0; i < selectedCount - 1; i++) {
        for (int j = 0; j < goodsCount - 1; j++) {
            if (selectedGoods[i].name == goods[j].name && selectedGoods[i].channel == goods[j].channel) {
                totalPrice += goods[j].price;
                break;
            }
        }
    }
    printf("总价为: %d 元",totalPrice);

    // 投币阶段
    int currentPrice = 0;
    int addPrice;
    while (currentPrice < totalPrice) {
        printf("请输入投币金额(1 元、2 元、5 元): ");
        if (scanf("%d", &addPrice) == 1) {
            if (addPrice == 1 || addPrice == 2 || addPrice == 5) {
                currentPrice += addPrice;
                printf("当前已投币 %d 元，还需投币 %d 元。\n", currentPrice, totalPrice - currentPrice);
            } else {
                printf("无效的投币金额，请重新输入。\n");
            }
        } else {
            while (getchar()!= '\n');
            printf("输入错误，请重新输入。\n");
        }
    }

    int change = currentPrice - totalPrice;
    printf("找零: %d 元", change);

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

    return 0;
    
}
