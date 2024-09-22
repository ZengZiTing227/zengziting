#include <stdio.h>

int main() {
    int totalprice;
    int addprice;
    int currentprice;
    int change;
   
    printf("请输入总价：");
    scanf("%d",&totalprice);

    currentprice==0;
    
    while (currentprice < totalprice) {
        printf("请输入投币金额(1元、2元、5元): ");
        scanf("%d", &addprice);
        if (addprice != 1 && addprice != 2 && addprice != 5) {
            printf("无效的投币金额，请重新输入。\n");
            continue;
        }
        currentprice += addprice;
    }

    change = currentprice - totalprice;
    printf("找零: %d元", change);

    return 0;
}




   




