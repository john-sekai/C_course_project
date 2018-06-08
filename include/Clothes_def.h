// definition of clothes and people type

struct Clothes{
// 服装类别的基本属性
    char *type;//服装类别,0为unknown
    char *brand;//服装品牌,0为unknown
    char *barcode;//条形码
    int size;//对应身高（单位cm）
    int storage_num;//库存量
    //int sale_num;//已售出量
    float purchase_price;//进货价
    float presale;//预售价
    float percent_off;//折扣，在0-1之间
    float sale_price;//服装实售价
    int salesperson_num;//售出该服装的员工编号,0为未售出
    char sale_time[6];//服装的售出时间，格式YYYYMMDD
};