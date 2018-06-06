// definition of clothes and people type
#include<stdio.h>
#include "Clothes_def.h"

struct salesperson{
    int id;//销售人员编号，0为nobody
    char name[]; 
};
struct manager{
    int password;//店长身份需要密码登录
};