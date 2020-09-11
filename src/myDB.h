/*************************************************************************
    > File Name: mydb.h
    > The class for Mysql
    > 
 ************************************************************************/

#ifndef _MYDB_H
#define _MYDB_H
#include<iostream>
#include<string>
#include<mysql/mysql.h>
#include "menu.h"
using namespace std;
 
class MyDB
{
    public:
        MyDB();
        ~MyDB();
        bool initDB(string host,string user,string pwd,string db_name); //连接mysql
        bool exeSQL(string sql);                                        //执行sql语句
        bool exeSQL(string sql ,MODE::User *user);                      //查询个人信息
        bool serchRecSQL(string sql , MYSQL_RES **bresult);             //查询借书记录
        int  serch4borrowSQL(string sql);                               //借书时查询书籍是否在图书馆，在返回1 不在返回2  没有这本书返回3
    private:
        MYSQL *mysql;          //连接mysql句柄指针
        MYSQL_RES *result;     //指向查询结果的指针
        MYSQL_ROW row;         //按行返回的查询信息
};
extern MyDB db;

#endif