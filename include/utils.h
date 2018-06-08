#include "Personnel_def.h"
#include <time.h>
#include <stdlib.h>
#include <string.h> //Func: strtok()

//定义服装的种类和品牌的信息文件地址（相对main.c)
//#define TYPE_PATH  "information\\type.txt"
//#define BRAND_PATH "information\\brand.txt"
#define STATS_PATH "information\\sale_stats.txt"//交易信息
#define CLOTHES_PATH "information\\clothes_stats.txt"//服装信息
#define HEADER_STYLE "%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|\n"//服装信息的抬头格式
#define INFO_STYLE "%s\t|%s\t|%s\t\t|%d\t|%d\t\t|%.2f\t\t|%.2f\t\t|%.2f\t\t|%.2f\t\t|\n"//服装信息的数据格式

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

// 打印header的子程序，为display函数服务
void print_header(){
    printf(HEADER_STYLE,
        "TYPE","BRAND","BARCODE","SIZE","STORAGE","PURC PRICE","PRESALE PRICE","PERCENT OFF","SALE PRICE");
}
// 打印info的子程序，为display函数服务
void print_info(struct Clothes *cloptr){
    printf(INFO_STYLE,
        cloptr->type, cloptr->brand, cloptr->barcode, cloptr->size, cloptr->storage_num,
        cloptr->purchase_price, cloptr->presale, cloptr->percent_off, cloptr->sale_price);
}

// 打印服装基本信息的子程序
void display(struct Clothes * clo){
    printf("Basic information about the clothes:\n");
    print_header();
    print_info(clo);
}

//初始化服装信息文件clothes_stats.txt
void clothes_stats_init(){
    FILE *fpin;
    if((fpin = fopen(CLOTHES_PATH, "w")) == NULL){
        printf("Error when opening CLOTHES_STAT file!");
    }
    else{
        fprintf(fpin,"%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|%s\t|\n",
        "TYPE","BRAND","BARCODE","SIZE","STORAGE","PURC PRICE","PRESALE PRICE","PERCENT OFF","SALE PRICE");
    }
    fclose(fpin);
}

//输入服装信息
struct Clothes *in(char *type, char *brand, char * barcode, int size,
                   int storage_num, float purchase_price, float presale){
    //写入进货服装的信息
    float percent_off = 0.0;
    float sale_price = presale;
    int salesperson_num = 0;
    printf("Importing clothes...\n ");
    struct Clothes *cloptr = calloc(1,sizeof(struct Clothes));
    cloptr->type = type;
    cloptr->brand = brand;
    cloptr->barcode = barcode;
    cloptr->size = size;
    cloptr->storage_num = storage_num;
    cloptr->purchase_price = purchase_price;
    cloptr->presale = presale;
    cloptr->percent_off = percent_off;
    cloptr->sale_price = sale_price;
    //cloptr->salesperson_num = salesperson_num;
    display(cloptr);
    printf("\n\n");
    FILE *fpin;
    if((fpin = fopen(CLOTHES_PATH, "a+")) == NULL){
        printf("Error when opening CLOTHES_STAT file!");
    }
    else{
        fprintf(fpin, INFO_STYLE,
                cloptr->type, cloptr->brand, cloptr->barcode, cloptr->size, cloptr->storage_num,
                cloptr->purchase_price, cloptr->presale, cloptr->percent_off, cloptr->sale_price);
    }
    fclose(fpin);
    return cloptr;
}

//从服装信息文件中获取某一件衣服对象
struct Clothes *get(char *type, char *brand, char *barcode, int size){
    printf("\nLooking for clothes with:\nTYPE:%s\nBRAND:%s\nBARCODE:%s\nSIZE:%d\nPlease wait...\n",type,brand,barcode,size);
    int foundflag = 0;//0 stands for no matches; 1 stands for there is match
    FILE *fp_clo;
    char *delim = "\t|";
    char CloLine[1024] = {0};
    char * tmp;//temp char pointer for initialize an
    if((fp_clo = fopen(CLOTHES_PATH,"r"))==NULL){
        printf("Error when opening CLOTHES_STAT file!");
        return NULL;
    }
    else{
        printf("Reading info...\n");
        while( (foundflag==0) && (!feof(fp_clo)) ){
            fgets(CloLine,1024,fp_clo);//读取一行
            puts(CloLine);
            //printf("...\n");
            struct Clothes *cloptr = calloc(1,sizeof(struct Clothes));
            tmp = strtok(CloLine, delim);
            if(tmp != NULL) cloptr->type = tmp;
            //printf("the type:%s\n",cloptr->type);

            tmp = strtok(NULL, delim);
            //printf("the second tmp:%s\n",tmp);
            if(tmp != NULL) cloptr->brand = tmp;

            tmp = strtok(NULL, delim);
            //printf("the third tmp:%s\n",tmp);
            if(tmp != NULL) cloptr->barcode = tmp;

            tmp = strtok(NULL, delim);
            if(tmp != NULL) cloptr->size = atoi(tmp);
            //printf("the fourth tmp:%d\n",cloptr->size);

            tmp = strtok(NULL, delim);
            if(tmp != NULL) cloptr->storage_num = atoi(tmp);
            //printf("the fifth tmp:%d\n",cloptr->storage_num);

            tmp = strtok(NULL, delim);
            if(tmp != NULL) cloptr->purchase_price = atof(tmp); 
            //printf("the last tmp:%f\n", cloptr->purchase_price);
            if((strcmp(cloptr->type, type) == 0) && (strcmp(cloptr->brand, brand) == 0) &&
               (strcmp(cloptr->barcode, barcode) == 0) && (cloptr->size == size)){
                foundflag = 1;
                printf("Clothes Found...\n");
                display(cloptr);
                fclose(fp_clo);
                return cloptr;
            }
        }
        if(foundflag == 0){
            printf("No match for the requested clothes!");
            return NULL;
        }
    }
}

struct Clothes * set_price(struct manager * m_ptr,struct Clothes* clo, float presale,float percent_off){
    if(m_ptr == NULL){
        printf("Sorry, you do not have the permission! Please login as the manager.\n");
    }
    else{
        clo->presale = presale;
        clo->presale = percent_off;
        clo->sale_price = presale * (1.0 - percent_off);
        printf("Price modified. Now displaying the clothes information...\n");
    } 
}

int sell(struct Clothes* clo,struct salesperson* sp){
    //salesperson can sell a piece of clothes
    clo->salesperson_num = sp->id;
};