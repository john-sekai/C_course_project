// definition of clothes and people type
#include<stdio.h>
#include "Clothes_def.h"

struct salesperson{
    int id;//销售人员编号，0为nobody
    char *name;//销售人员名字 
    int sales[12];//销售业绩，当月的销售额
};
struct manager{
    int password;//店长身份需要密码登录
};