#define _CRT_SECURE_NO_WARNINGS  // 禁用VS安全函数警告
#pragma warning(disable:4996)   // 禁用deprecated函数警告（兼容localtime等）
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <conio.h>  // VS2022兼容_getch()

// -------------------------- 宏定义 --------------------------
#define MAX_USER 10          
#define MAX_GOODS 100        
#define MAX_SALE 1000        
#define MIN_STOCK 10         
#define FILE_USER "user.dat" 
#define FILE_GOODS "goods.dat"
#define FILE_SALE "sale.dat" 

// -------------------------- 枚举类型 --------------------------
typedef enum {
    FRUIT,
    DAILY_USE,
    CIGARETTE,
    WINE,
    SEAFOOD,
    MEAT,
    CATEGORY_MAX
} GoodsCategory;

// -------------------------- 结构体定义 --------------------------
typedef struct {
    char username[20];
    char password[20];
    int isAdmin;
} User;

typedef struct {
    char id[20];
    char name[50];
    GoodsCategory cate;
    float buyPrice;
    float sellPrice;
    int stock;
    int minStock;
} Goods;

typedef struct {
    char saleId[30];
    char goodsId[20];
    char goodsName[50];
    int saleNum;
    float totalPrice;
    char saleTime[20];
} SaleRecord;

// -------------------------- 全局变量 --------------------------
User g_users[MAX_USER];
Goods g_goods[MAX_GOODS];
SaleRecord g_sales[MAX_SALE];
int g_userCount = 0;
int g_goodsCount = 0;
int g_saleCount = 0;

// -------------------------- 辅助函数 --------------------------
const char* categoryToStr(GoodsCategory cate)
{
    switch (cate) {
    case FRUIT: return "水果";
    case DAILY_USE: return "日用品";
    case CIGARETTE: return "烟类";
    case WINE: return "酒类";
    case SEAFOOD: return "水产";
    case MEAT: return "肉类";
    default: return "未知分类";
    }
}

void getCurrentTime(char* timeStr) {
    time_t now = time(NULL);
    struct tm* tmNow = localtime(&now); // VS2022需禁用4996警告
    sprintf(timeStr, "%04d-%02d-%02d %02d:%02d:%02d",
        tmNow->tm_year + 1900, tmNow->tm_mon + 1, tmNow->tm_mday,
        tmNow->tm_hour, tmNow->tm_min, tmNow->tm_sec);
}

void generateSaleId(char* saleId) {
    char timeStr[20];
    getCurrentTime(timeStr);
    for (int i = 0; i < strlen(timeStr); i++) {
        if (timeStr[i] == '-' || timeStr[i] == ' ' || timeStr[i] == ':') {
            timeStr[i] = '_';
        }
    }
    int randNum = rand() % 1000;
    sprintf(saleId, "SALE_%s_%03d", timeStr, randNum);
}

int isPositiveNum(float num) {
    if (num <= 0) {
        printf("❌ 输入错误！请输入正数（当前输入：%.2f）\n", num);
        return 0;
    }
    return 1;
}

// -------------------------- 文件读写模块 --------------------------
void loadAllData()
{
    // 加载用户数据
    FILE* fpUser = fopen(FILE_USER, "rb");
    if (fpUser != NULL) {
        fread(&g_userCount, sizeof(int), 1, fpUser);
        fread(g_users, sizeof(User), g_userCount, fpUser);
        fclose(fpUser);
        printf("✅ 用户数据加载成功（共%d位用户）\n", g_userCount);
    }
    else {
        strcpy(g_users[0].username, "admin");
        strcpy(g_users[0].password, "123456");
        g_users[0].isAdmin = 1;
        g_userCount = 1;
        printf("✅ 首次运行，已初始化默认管理员（admin/123456）\n");
    }

    // 加载商品数据
    FILE* fpGoods = fopen(FILE_GOODS, "rb");
    if (fpGoods != NULL) {
        fread(&g_goodsCount, sizeof(int), 1, fpGoods);
        fread(g_goods, sizeof(Goods), g_goodsCount, fpGoods);
        fclose(fpGoods);
        printf("✅ 商品数据加载成功（共%d种商品）\n", g_goodsCount);
    }
    else {
        printf("✅ 暂无商品数据，可进入商品管理模块添加\n");
    }

    // 加载销售记录数据
    FILE* fpSale = fopen(FILE_SALE, "rb");
    if (fpSale != NULL) {
        fread(&g_saleCount, sizeof(int), 1, fpSale);
        fread(g_sales, sizeof(SaleRecord), g_saleCount, fpSale);
        fclose(fpSale);
        printf("✅ 销售记录加载成功（共%d条记录）\n", g_saleCount);
    }
    else {
        printf("✅ 暂无销售记录，可进入销售模块生成\n");
    }
    printf("-----------------------------------------\n");
    system("pause");
    system("cls");
}

void saveAllData()
{
    // 保存用户数据
    FILE* fpUser = fopen(FILE_USER, "wb");
    fwrite(&g_userCount, sizeof(int), 1, fpUser);
    fwrite(g_users, sizeof(User), g_userCount, fpUser);
    fclose(fpUser);

    // 保存商品数据
    FILE* fpGoods = fopen(FILE_GOODS, "wb");
    fwrite(&g_goodsCount, sizeof(int), 1, fpGoods);
    fwrite(g_goods, sizeof(Goods), g_goodsCount, fpGoods);
    fclose(fpGoods);

    // 保存销售记录数据
    FILE* fpSale = fopen(FILE_SALE, "wb");
    fwrite(&g_saleCount, sizeof(int), 1, fpSale);
    fwrite(g_sales, sizeof(SaleRecord), g_saleCount, fpSale);
    fclose(fpSale);

    printf("✅ 所有数据已自动保存到文件，安全退出！\n");
}

// -------------------------- 登录模块 --------------------------
int adminLogin() {
    char username[20], password[20];
    int loginCount = 3;

    while (loginCount > 0) {
        system("cls");
        printf("=========================================\n");
        printf("          超市收银系统 - 管理员登录        \n");
        printf("=========================================\n");
        printf("请输入用户名：");
        scanf("%s", username);
        printf("请输入密码：");
        int i = 0;
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            }
            else {
                password[i++] = ch;
                printf("*");
            }
        }
        password[i] = '\0';
        printf("\n-----------------------------------------\n");

        // 验证用户名和密码
        for (int j = 0; j < g_userCount; j++) {
            if (strcmp(username, g_users[j].username) == 0 &&
                strcmp(password, g_users[j].password) == 0 &&
                g_users[j].isAdmin == 1) {
                printf("✅ 登录成功！欢迎您，%s管理员\n", username);
                system("pause");
                system("cls");
                return 1;
            }
        }

        loginCount--;
        printf("❌ 用户名或密码错误！剩余尝试次数：%d\n", loginCount);
        system("pause");
    }

    printf("❌ 登录失败次数过多，程序即将退出！\n");
    system("pause");
    return 0;
}

// -------------------------- 商品管理模块 --------------------------
void addGoods() {
    if (g_goodsCount >= MAX_GOODS) {
        printf("❌ 商品数量已达上限（%d种），无法添加！\n", MAX_GOODS);
        system("pause");
        return;
    }

    Goods newGoods;
    system("cls");
    printf("=========================================\n");
    printf("          商品管理 - 添加新商品          \n");
    printf("=========================================\n");
    printf("请输入商品编号（唯一）：");
    scanf("%s", newGoods.id);
    for (int i = 0; i < g_goodsCount; i++) {
        if (strcmp(newGoods.id, g_goods[i].id) == 0) {
            printf("❌ 该商品编号已存在！请重新输入\n");
            system("pause");
            return;
        }
    }

    printf("请输入商品名称：");
    getchar();
    fgets(newGoods.name, 50, stdin);
    newGoods.name[strcspn(newGoods.name, "\n")] = '\0'; // 替代原换行符处理（VS更稳定）

    printf("请选择商品分类（0-水果 1-日用品 2-烟类 3-酒类 4-水产 5-肉类）：");
    int cateIdx;
    scanf("%d", &cateIdx);
    while (cateIdx < 0 || cateIdx >= CATEGORY_MAX) {
        printf("❌ 分类选择错误！请输入0-%d之间的数字：", CATEGORY_MAX - 1);
        scanf("%d", &cateIdx);
    }
    newGoods.cate = (GoodsCategory)cateIdx;

    printf("请输入进价单价（元）：");
    scanf("%f", &newGoods.buyPrice);
    while (!isPositiveNum(newGoods.buyPrice)) {
        printf("请重新输入进价单价：");
        scanf("%f", &newGoods.buyPrice);
    }

    printf("请输入销售单价（元）：");
    scanf("%f", &newGoods.sellPrice);
    while (!isPositiveNum(newGoods.sellPrice)) {
        printf("请重新输入销售单价：");
        scanf("%f", &newGoods.sellPrice);
    }

    printf("请输入初始库存（件）：");
    scanf("%d", &newGoods.stock);
    while (newGoods.stock < 0) {
        printf("❌ 库存不能为负数！请重新输入：");
        scanf("%d", &newGoods.stock);
    }

    printf("请输入库存预警阈值（默认%d件，输入0则使用默认值）：", MIN_STOCK);
    scanf("%d", &newGoods.minStock);
    if (newGoods.minStock <= 0) {
        newGoods.minStock = MIN_STOCK;
        printf("✅ 已自动设置预警阈值为：%d件\n", MIN_STOCK);
    }

    g_goods[g_goodsCount++] = newGoods;
    printf("✅ 商品添加成功！商品信息如下：\n");
    printf("编号：%s | 名称：%s | 分类：%s | 售价：%.2f元 | 库存：%d件\n",
        newGoods.id, newGoods.name, categoryToStr(newGoods.cate),
        newGoods.sellPrice, newGoods.stock);
    system("pause");
}

void showAllGoods() {
    system("cls");
    printf("=========================================\n");
    printf("          商品管理 - 所有商品列表        \n");
    printf("=========================================\n");
    if (g_goodsCount == 0) {
        printf("❌ 暂无商品数据，请先添加商品！\n");
        system("pause");
        return;
    }

    printf("%-10s %-20s %-8s %-10s %-10s %-8s %-8s\n",
        "商品编号", "商品名称", "分类", "进价（元）", "售价（元）", "库存（件）", "预警阈值");
    printf("-----------------------------------------\n");
    for (int i = 0; i < g_goodsCount; i++) {
        char stockTips[20] = "";
        if (g_goods[i].stock <= g_goods[i].minStock) {
            strcpy(stockTips, "⚠️ 需补货");
        }
        printf("%-10s %-20s %-8s %-10.2f %-10.2f %-8d %-8d %s\n",
            g_goods[i].id, g_goods[i].name, categoryToStr(g_goods[i].cate),
            g_goods[i].buyPrice, g_goods[i].sellPrice,
            g_goods[i].stock, g_goods[i].minStock, stockTips);
    }
    printf("-----------------------------------------\n");
    printf("📊 商品总数：%d种\n", g_goodsCount);
    system("pause");
}

void modifyGoods() {
    system("cls");
    printf("=========================================\n");
    printf("          商品管理 - 修改商品信息        \n");
    printf("=========================================\n");
    if (g_goodsCount == 0) {
        printf("❌ 暂无商品数据，请先添加商品！\n");
        system("pause");
        return;
    }

    char targetId[20];
    printf("请输入要修改的商品编号：");
    scanf("%s", targetId);

    int findIdx = -1;
    for (int i = 0; i < g_goodsCount; i++) {
        if (strcmp(targetId, g_goods[i].id) == 0) {
            findIdx = i;
            break;
        }
    }

    if (findIdx == -1) {
        printf("❌ 未找到编号为【%s】的商品！\n", targetId);
        system("pause");
        return;
    }

    printf("-----------------------------------------\n");
    printf("原商品信息：\n");
    printf("编号：%s | 名称：%s | 分类：%s | 进价：%.2f | 售价：%.2f | 库存：%d | 预警阈值：%d\n",
        g_goods[findIdx].id, g_goods[findIdx].name, categoryToStr(g_goods[findIdx].cate),
        g_goods[findIdx].buyPrice, g_goods[findIdx].sellPrice,
        g_goods[findIdx].stock, g_goods[findIdx].minStock);
    printf("-----------------------------------------\n");
    printf("请输入新的商品信息（按回车保留原值）：\n");

    char newName[50];
    printf("商品名称（原：%s）：", g_goods[findIdx].name);
    getchar();
    fgets(newName, 50, stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) {
        strcpy(g_goods[findIdx].name, newName);
    }

    printf("商品分类（原：%s，输入0-5选择，按回车保留原值）：", categoryToStr(g_goods[findIdx].cate));
    char cateStr[10];
    fgets(cateStr, 10, stdin);
    cateStr[strcspn(cateStr, "\n")] = '\0';
    if (strlen(cateStr) > 0) {
        int newCate = atoi(cateStr);
        if (newCate >= 0 && newCate < CATEGORY_MAX) {
            g_goods[findIdx].cate = (GoodsCategory)newCate;
        }
        else {
            printf("❌ 分类输入错误，保留原值！\n");
        }
    }

    printf("进价单价（原：%.2f元，按回车保留原值）：", g_goods[findIdx].buyPrice);
    char buyPriceStr[20];
    fgets(buyPriceStr, 20, stdin);
    buyPriceStr[strcspn(buyPriceStr, "\n")] = '\0';
    if (strlen(buyPriceStr) > 0) {
        float newBuyPrice = atof(buyPriceStr);
        if (isPositiveNum(newBuyPrice)) {
            g_goods[findIdx].buyPrice = newBuyPrice;
        }
        else {
            printf("❌ 进价输入错误，保留原值！\n");
        }
    }

    printf("销售单价（原：%.2f元，按回车保留原值）：", g_goods[findIdx].sellPrice);
    char sellPriceStr[20];
    fgets(sellPriceStr, 20, stdin);
    sellPriceStr[strcspn(sellPriceStr, "\n")] = '\0';
    if (strlen(sellPriceStr) > 0) {
        float newSellPrice = atof(sellPriceStr);
        if (isPositiveNum(newSellPrice)) {
            g_goods[findIdx].sellPrice = newSellPrice;
        }
        else {
            printf("❌ 售价输入错误，保留原值！\n");
        }
    }

    printf("库存数量（原：%d件，按回车保留原值）：", g_goods[findIdx].stock);
    char stockStr[20];
    fgets(stockStr, 20, stdin);
    stockStr[strcspn(stockStr, "\n")] = '\0';
    if (strlen(stockStr) > 0) {
        int newStock = atoi(stockStr);
        if (newStock >= 0) {
            g_goods[findIdx].stock = newStock;
        }
        else {
            printf("❌ 库存输入错误，保留原值！\n");
        }
    }

    printf("✅ 商品信息修改成功！\n");
    system("pause");
}

void deleteGoods() {
    system("cls");
    printf("=========================================\n");
    printf("          商品管理 - 删除商品            \n");
    printf("=========================================\n");
    if (g_goodsCount == 0) {
        printf("❌ 暂无商品数据，请先添加商品！\n");
        system("pause");
        return;
    }

    char targetId[20];
    printf("请输入要删除的商品编号：");
    scanf("%s", targetId);

    int findIdx = -1;
    for (int i = 0; i < g_goodsCount; i++) {
        if (strcmp(targetId, g_goods[i].id) == 0) {
            findIdx = i;
            break;
        }
    }

    if (findIdx == -1) {
        printf("❌ 未找到编号为【%s】的商品！\n", targetId);
        system("pause");
        return;
    }

    printf("-----------------------------------------\n");
    printf("确认删除以下商品？（y/n）\n");
    printf("编号：%s | 名称：%s | 分类：%s | 库存：%d件\n",
        g_goods[findIdx].id, g_goods[findIdx].name,
        categoryToStr(g_goods[findIdx].cate), g_goods[findIdx].stock);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("✅ 已取消删除！\n");
        system("pause");
        return;
    }

    for (int i = findIdx; i < g_goodsCount - 1; i++) {
        g_goods[i] = g_goods[i + 1];
    }
    g_goodsCount--;
    printf("✅ 商品删除成功！\n");
    system("pause");
}

void goodsManageMenu() {
    int choice;
    while (1) {
        system("cls");
        printf("=========================================\n");
        printf("          超市收银系统 - 商品管理        \n");
        printf("=========================================\n");
        printf("1. 添加商品\n");
        printf("2. 查看所有商品\n");
        printf("3. 修改商品信息\n");
        printf("4. 删除商品\n");
        printf("5. 返回主菜单\n");
        printf("-----------------------------------------\n");
        printf("请输入选择（1-5）：");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addGoods(); break;
        case 2: showAllGoods(); break;
        case 3: modifyGoods(); break;
        case 4: deleteGoods(); break;
        case 5: return;
        default:
            printf("❌ 输入错误！请输入1-5之间的数字\n");
            system("pause");
        }
    }
}

// -------------------------- 销售模块 --------------------------
void sellGoods() {
    system("cls");
    printf("=========================================\n");
    printf("          销售模块 - 商品结算            \n");
    printf("=========================================\n");
    if (g_goodsCount == 0) {
        printf("❌ 暂无商品数据，无法销售！\n");
        system("pause");
        return;
    }

    char targetId[20];
    printf("请输入要销售的商品编号：");
    scanf("%s", targetId);

    int findIdx = -1;
    for (int i = 0; i < g_goodsCount; i++) {
        if (strcmp(targetId, g_goods[i].id) == 0) {
            findIdx = i;
            break;
        }
    }

    if (findIdx == -1) {
        printf("❌ 未找到编号为【%s】的商品！\n", targetId);
        system("pause");
        return;
    }

    if (g_goods[findIdx].stock <= 0) {
        printf("❌ 商品【%s】库存不足，无法销售！\n", g_goods[findIdx].name);
        system("pause");
        return;
    }

    int saleNum;
    printf("-----------------------------------------\n");
    printf("商品信息：%s（%s） | 售价：%.2f元 | 当前库存：%d件\n",
        g_goods[findIdx].name, categoryToStr(g_goods[findIdx].cate),
        g_goods[findIdx].sellPrice, g_goods[findIdx].stock);
    printf("请输入销售数量（件）：");
    scanf("%d", &saleNum);
    while (saleNum <= 0 || saleNum > g_goods[findIdx].stock) {
        if (saleNum <= 0) {
            printf("❌ 销售数量不能为负数！请重新输入：");
        }
        else {
            printf("❌ 销售数量超过库存（当前库存：%d件）！请重新输入：", g_goods[findIdx].stock);
        }
        scanf("%d", &saleNum);
    }

    float totalPrice = saleNum * g_goods[findIdx].sellPrice;

    SaleRecord newSale;
    generateSaleId(newSale.saleId);
    strcpy(newSale.goodsId, g_goods[findIdx].id);
    strcpy(newSale.goodsName, g_goods[findIdx].name);
    newSale.saleNum = saleNum;
    newSale.totalPrice = totalPrice;
    getCurrentTime(newSale.saleTime);

    if (g_saleCount < MAX_SALE) {
        g_sales[g_saleCount++] = newSale;
    }
    else {
        printf("❌ 销售记录已达上限（%d条），无法保存记录！\n", MAX_SALE);
        system("pause");
        return;
    }

    g_goods[findIdx].stock -= saleNum;

    printf("-----------------------------------------\n");
    printf("                销售收据                  \n");
    printf("=========================================\n");
    printf("销售单号：%s\n", newSale.saleId);
    printf("销售时间：%s\n", newSale.saleTime);
    printf("-----------------------------------------\n");
    printf("%-20s %-8s %-10s %-10s\n", "商品名称", "数量（件）", "单价（元）", "总价（元）");
    printf("-----------------------------------------\n");
    printf("%-20s %-8d %-10.2f %-10.2f\n",
        newSale.goodsName, newSale.saleNum,
        g_goods[findIdx].sellPrice, newSale.totalPrice);
    printf("-----------------------------------------\n");
    printf("应付金额：%.2f 元\n", newSale.totalPrice);
    printf("收款方式：□ 现金 □ 微信 □ 支付宝 □ 刷卡（手动勾选）\n");
    printf("=========================================\n");
    printf("          感谢惠顾，欢迎下次光临！        \n");
    printf("-----------------------------------------\n");

    if (g_goods[findIdx].stock <= g_goods[findIdx].minStock) {
        printf("⚠️ 警告：商品【%s】库存不足（当前：%d件），请及时补货！\n",
            g_goods[findIdx].name, g_goods[findIdx].stock);
    }

    system("pause");
}

void showAllSaleRecords() {
    system("cls");
    printf("=========================================\n");
    printf("          销售模块 - 所有销售记录        \n");
    printf("=========================================\n");
    if (g_saleCount == 0) {
        printf("❌ 暂无销售记录，请先进行销售操作！\n");
        system("pause");
        return;
    }

    printf("%-25s %-20s %-8s %-10s %-20s\n",
        "销售单号", "商品名称", "数量（件）", "总价（元）", "销售时间");
    printf("-----------------------------------------\n");
    for (int i = 0; i < g_saleCount; i++) {
        printf("%-25s %-20s %-8d %-10.2f %-20s\n",
            g_sales[i].saleId, g_sales[i].goodsName,
            g_sales[i].saleNum, g_sales[i].totalPrice,
            g_sales[i].saleTime);
    }
    printf("-----------------------------------------\n");
    printf("📊 销售记录总数：%d条\n", g_saleCount);
    system("pause");
}

void saleMenu() {
    int choice;
    while (1) {
        system("cls");
        printf("=========================================\n");
        printf("          超市收银系统 - 销售模块        \n");
        printf("=========================================\n");
        printf("1. 商品销售（生成收据）\n");
        printf("2. 查看所有销售记录\n");
        printf("3. 返回主菜单\n");
        printf("-----------------------------------------\n");
        printf("请输入选择（1-3）：");
        scanf("%d", &choice);

        switch (choice) {
        case 1: sellGoods(); break;
        case 2: showAllSaleRecords(); break;
        case 3: return;
        default:
            printf("❌ 输入错误！请输入1-3之间的数字\n");
            system("pause");
        }
    }
}

// -------------------------- 库存管理模块 --------------------------
void stockManage() {
    system("cls");
    printf("=========================================\n");
    printf("          超市收银系统 - 库存管理        \n");
    printf("=========================================\n");
    if (g_goodsCount == 0) {
        printf("❌ 暂无商品数据，无法管理库存！\n");
        system("pause");
        return;
    }

    printf("⚠️  库存预警商品（低于阈值）：\n");
    printf("-----------------------------------------\n");
    int warnCount = 0;
    for (int i = 0; i < g_goodsCount; i++) {
        if (g_goods[i].stock <= g_goods[i].minStock) {
            printf("编号：%s | 名称：%s | 分类：%s | 当前库存：%d件 | 预警阈值：%d件\n",
                g_goods[i].id, g_goods[i].name, categoryToStr(g_goods[i].cate),
                g_goods[i].stock, g_goods[i].minStock);
            warnCount++;
        }
    }
    if (warnCount == 0) {
        printf("✅ 暂无库存预警商品，库存状态良好！\n");
    }

    printf("\n-----------------------------------------\n");
    printf("📊 所有商品库存统计：\n");
    printf("-----------------------------------------\n");
    printf("%-10s %-20s %-8s %-8s %-8s\n",
        "商品编号", "商品名称", "分类", "当前库存", "预警阈值");
    printf("-----------------------------------------\n");
    for (int i = 0; i < g_goodsCount; i++) {
        printf("%-10s %-20s %-8s %-8d %-8d\n",
            g_goods[i].id, g_goods[i].name, categoryToStr(g_goods[i].cate),
            g_goods[i].stock, g_goods[i].minStock);
    }

    printf("-----------------------------------------\n");
    printf("📊 统计信息：商品总数=%d种 | 预警商品数=%d种\n", g_goodsCount, warnCount);
    system("pause");
}

// -------------------------- 数据统计模块 --------------------------
void statSaleByTime() {
    system("cls");
    printf("=========================================\n");
    printf("          统计模块 - 销售总额统计        \n");
    printf("=========================================\n");
    if (g_saleCount == 0) {
        printf("❌ 暂无销售记录，无法统计！\n");
        system("pause");
        return;
    }

    int choice;
    printf("请选择统计维度：\n");
    printf("1. 今日销售总额\n");
    printf("2. 本周销售总额\n");
    printf("3. 本月销售总额\n");
    printf("-----------------------------------------\n");
    printf("请输入选择（1-3）：");
    scanf("%d", &choice);

    char currentTime[20];
    getCurrentTime(currentTime);
    char currentDate[11];
    strncpy(currentDate, currentTime, 10);
    currentDate[10] = '\0';

    int currentYear, currentMonth, currentDay;
    sscanf(currentDate, "%d-%d-%d", &currentYear, &currentMonth, &currentDay);
    time_t now = time(NULL);
    struct tm* tmNow = localtime(&now);
    int currentWeek = tmNow->tm_wday + 1;

    float total = 0.0;
    char saleDate[11];
    int saleYear, saleMonth, saleDay, saleWeek;

    for (int i = 0; i < g_saleCount; i++) {
        strncpy(saleDate, g_sales[i].saleTime, 10);
        saleDate[10] = '\0';
        sscanf(saleDate, "%d-%d-%d", &saleYear, &saleMonth, &saleDay);

        struct tm saleTm = { 0 };
        saleTm.tm_year = saleYear - 1900;
        saleTm.tm_mon = saleMonth - 1;
        saleTm.tm_mday = saleDay;
        mktime(&saleTm);
        saleWeek = saleTm.tm_yday / 7 + 1;

        switch (choice) {
        case 1:
            if (strcmp(saleDate, currentDate) == 0) {
                total += g_sales[i].totalPrice;
            }
            break;
        case 2:
            if (saleYear == currentYear && saleWeek == (tmNow->tm_yday / 7 + 1)) {
                total += g_sales[i].totalPrice;
            }
            break;
        case 3:
            if (saleYear == currentYear && saleMonth == currentMonth) {
                total += g_sales[i].totalPrice;
            }
            break;
        }
    }

    printf("-----------------------------------------\n");
    printf("📊 统计结果：\n");
    switch (choice) {
    case 1: printf("今日（%s）销售总额：%.2f 元\n", currentDate, total); break;
    case 2: printf("本周（第%d周）销售总额：%.2f 元\n", saleWeek, total); break;
    case 3: printf("本月（%d年%d月）销售总额：%.2f 元\n", currentYear, currentMonth, total); break;
    }
    system("pause");
}

void statSaleByGoods() {
    system("cls");
    printf("=========================================\n");
    printf("          统计模块 - 商品销量统计        \n");
    printf("=========================================\n");
    if (g_saleCount == 0) {
        printf("❌ 暂无销售记录，无法统计！\n");
        system("pause");
        return;
    }

    typedef struct {
        char goodsId[20];
        char goodsName[50];
        int totalSaleNum;
        float totalSalePrice;
    } GoodsSaleStat;

    GoodsSaleStat statArr[MAX_GOODS];
    int statCount = 0;

    for (int i = 0; i < g_saleCount; i++) {
        int findIdx = -1;
        for (int j = 0; j < statCount; j++) {
            if (strcmp(g_sales[i].goodsId, statArr[j].goodsId) == 0) {
                findIdx = j;
                break;
            }
        }

        if (findIdx != -1) {
            statArr[findIdx].totalSaleNum += g_sales[i].saleNum;
            statArr[findIdx].totalSalePrice += g_sales[i].totalPrice;
        }
        else {
            strcpy(statArr[statCount].goodsId, g_sales[i].goodsId);
            strcpy(statArr[statCount].goodsName, g_sales[i].goodsName);
            statArr[statCount].totalSaleNum = g_sales[i].saleNum;
            statArr[statCount].totalSalePrice = g_sales[i].totalPrice;
            statCount++;
        }
    }

    printf("%-10s %-20s %-10s %-10s\n",
        "商品编号", "商品名称", "总销量（件）", "总销售额（元）");
    printf("-----------------------------------------\n");
    for (int i = 0; i < statCount; i++) {
        printf("%-10s %-20s %-10d %-10.2f\n",
            statArr[i].goodsId, statArr[i].goodsName,
            statArr[i].totalSaleNum, statArr[i].totalSalePrice);
    }
    printf("-----------------------------------------\n");
    printf("📊 统计信息：参与销售商品数=%d种 | 总销售记录数=%d条\n", statCount, g_saleCount);
    system("pause");
}

void statMenu() {
    int choice;
    while (1) {
        system("cls");
        printf("=========================================\n");
        printf("          超市收银系统 - 数据统计        \n");
        printf("=========================================\n");
        printf("1. 按时间段统计销售总额（日/周/月）\n");
        printf("2. 按商品统计销售数量及销售额\n");
        printf("3. 返回主菜单\n");
        printf("-----------------------------------------\n");
        printf("请输入选择（1-3）：");
        scanf("%d", &choice);

        switch (choice) {
        case 1: statSaleByTime(); break;
        case 2: statSaleByGoods(); break;
        case 3: return;
        default:
            printf("❌ 输入错误！请输入1-3之间的数字\n");
            system("pause");
        }
    }
}

// -------------------------- 搜索模块 --------------------------
void searchGoods() {
    system("cls");
    printf("=========================================\n");
    printf("          超市收银系统 - 商品搜索        \n");
    printf("=========================================\n");
    if (g_goodsCount == 0) {
        printf("❌ 暂无商品数据，无法搜索！\n");
        system("pause");
        return;
    }

    int choice;
    char keyWord[50];
    printf("请选择搜索方式：\n");
    printf("1. 按商品编号搜索（精确匹配）\n");
    printf("2. 按商品名称搜索（模糊匹配）\n");
    printf("-----------------------------------------\n");
    printf("请输入选择（1-2）：");
    scanf("%d", &choice);
    printf("请输入搜索关键词：");
    getchar();
    fgets(keyWord, 50, stdin);
    keyWord[strcspn(keyWord, "\n")] = '\0';

    printf("-----------------------------------------\n");
    printf("搜索结果（关键词：%s）：\n", keyWord);
    printf("-----------------------------------------\n");
    printf("%-10s %-20s %-8s %-10s %-8s\n",
        "商品编号", "商品名称", "分类", "售价（元）", "库存（件）");
    printf("-----------------------------------------\n");
    int findCount = 0;

    for (int i = 0; i < g_goodsCount; i++) {
        int isMatch = 0;
        if (choice == 1) {
            if (strcmp(keyWord, g_goods[i].id) == 0) {
                isMatch = 1;
            }
        }
        else {
            if (strstr(g_goods[i].name, keyWord) != NULL) {
                isMatch = 1;
            }
        }

        if (isMatch) {
            printf("%-10s %-20s %-8s %-10.2f %-8d\n",
                g_goods[i].id, g_goods[i].name, categoryToStr(g_goods[i].cate),
                g_goods[i].sellPrice, g_goods[i].stock);
            findCount++;
        }
    }

    if (findCount == 0) {
        printf("❌ 未找到匹配的商品！\n");
    }
    else {
        printf("-----------------------------------------\n");
        printf("📊 找到匹配商品：%d种\n", findCount);
    }
    system("pause");
}

// -------------------------- 主菜单模块 --------------------------
void mainMenu() {
    int choice;
    while (1) {
        system("cls");
        printf("=========================================\n");
        printf("          超市收银系统（C语言版）        \n");
        printf("          报名编号：12138 | 姓名：豆包    \n");
        printf("=========================================\n");
        printf("1. 商品信息管理\n");
        printf("2. 销售记录管理\n");
        printf("3. 库存管理\n");
        printf("4. 数据统计分析\n");
        printf("5. 商品搜索\n");
        printf("6. 退出系统\n");
        printf("-----------------------------------------\n");
        printf("请输入选择（1-6）：");
        scanf("%d", &choice);

        switch (choice) {
        case 1: goodsManageMenu(); break;
        case 2: saleMenu(); break;
        case 3: stockManage(); break;
        case 4: statMenu(); break;
        case 5: searchGoods(); break;
        case 6:
            saveAllData();
            printf("=========================================\n");
            printf("          感谢使用，程序已退出！          \n");
            printf("=========================================\n");
            exit(0);
        default:
            printf("❌ 输入错误！请输入1-6之间的数字\n");
            system("pause");
        }
    }
}

// -------------------------- 程序入口 --------------------------
int main()
{
    SetConsoleOutputCP(936);  // GBK编码（VS2022默认字符集）
    SetConsoleCP(936);        // 输入编码同步GBK
    srand((unsigned int)time(NULL));
    loadAllData();
    if (adminLogin()) {
        mainMenu();
    }
    saveAllData();
    return 0;
}