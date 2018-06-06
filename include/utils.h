#include "Personnel_def.h"
#include <time.h>
#include <stdlib.h>

//定义服装的种类和品牌的信息文件地址（相对main.c)
#define TYPE_PATH  "information\\type.txt"
#define BRAND_PATH "information\\brand.txt"
#define STATS_PATH "information\\sale_stats.txt"//交易信息
#define CLOTHES_PATH "information\\clothes_stats.txt"//服装信息

//获取当前日期和时间
char * now(char *datetime){
    time_t timep;
    struct tm *p;

    time(&timep);
    p = localtime(&timep);
    sprintf(datetime, "%4d-%02d-%02d %02d:%02d:%02d",
    (1900+p->tm_year),(1+p->tm_mon),p->tm_mday, 
    p->tm_hour,p->tm_min,p->tm_sec);
    return datetime;
}// printf("%s\n",now(datetime));

struct Clothes *in(char *type, char *brand, char * barcode, int size,
            float purchase_price, float presale){
    float percent_off = 0.0;
    float sale_price = 0;
    //char* sale_time;
    struct Clothes *cloptr = calloc(1,sizeof(struct Clothes));
    cloptr->type = type;
    cloptr->brand = brand;
    cloptr->barcode = barcode;
    cloptr->size = size;
    cloptr->purchase_price = purchase_price;
    cloptr->presale = presale;
    cloptr->percent_off = percent_off;
    cloptr->sale_price = sale_price;
    //cloptr->salesperson_num = salesperson_num;
    //cloptr->sale_price = sale_price;

    FILE *fpin;
    if((fpin = fopen(CLOTHES_PATH, "a+")) == NULL){
        printf("Error when opening CLOTHES_STAT file!");
    }
    else{
        fprintf(fpin,"%s\t|%s\t|%s\t\t|%d\t|%.2f\t\t|%.2f\t\t|%.2f\t\t|%.2f\t\t|%d\t\t\t|%s\n",
                type, brand, barcode, size, purchase_price, presale, percent_off, sale_price,
                cloptr->salesperson_num,cloptr->sale_time);
    }
    return cloptr;
}

void clothes_stats_init(){
    FILE *fpin;
    if((fpin = fopen(CLOTHES_PATH, "w")) == NULL){
        printf("Error when opening CLOTHES_STAT file!");
    }
    else{
        fprintf(fpin,"%s\t|%s\t|%s\t|%s\t|%s\t|%s\t\t|%s\t\t|%s\t|%s\t|%s\t|\n",
        "TYPE","BRAND","BARCODE","SIZE","PURC_PRICE","PRESALE","%OFF","SALE_PRICE",
        "SALESPERSON_NUM","SALE_TIME");
    }
}

int get(int type, int brand, int barcode){
    //获取某一件衣服对象的指针


};

int sell(struct Clothes* clo,struct salesperson* sp){
    //salesperson can sell a piece of clothes
    clo->salesperson_num = sp->id;

};