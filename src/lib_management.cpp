#include "iostream"
#include "book.h"
#include "myDB.h"
#include "menu.h"
using namespace std;

int main(){
    //连接数据库
    db.initDB("localhost","root","1","lib_management");
    while(1){
        loop();
    }
    return 1;
}


