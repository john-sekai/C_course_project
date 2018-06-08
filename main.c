#include "include/utils.h"

int main()
{
    //intialization of clothes_stats needed
    clothes_stats_init();
    struct Clothes *clo;
    clo = in("TSHIRT","UNIKLO","0X0001",175,20, 100.0, 130.0);
    
    // able to find a clothes with certain information
    clo = get("TSHIRT","UNIKLO","0X0001",175);
    
    return 0;
}
