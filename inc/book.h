#pragma once
#include "string"
#include "map"
#define max_title_len 20
#define max_class_len 20
#define max_isbn_len  30


class book{

public:
    book(/* args */){}
    book(std::string& btitle ,std::string& bisbn ,std::string& bclass,std::string& bauthor, int bprice );
    ~book(){}

public:
    int setTitle(std::string& btitle);
    std::string& getTitle();
    int saveBook();
protected:
    /* data */
    std::string title;
    std::string class_;
    int         price;
    std::string author;
    std::string isbn;
};
struct Blist                                        //此结构体用来作为链表的数据 
        {
            /* data */
            int         retuenif;
            std::string bookname;
            std::string author;
            std::string borrowtime;
            std::string isbn;
            std::string bclass;
        };
class BookList {
      
    public:
        BookList(){create_List();}                                  //在新建的时候自动初始化，建立链表
        ~BookList(){clear();}
        
        
        //创建头结点
        void create_List();
        //插入函数
        void insert(Blist* d);
        //在指定位置插入
        void insert_pos(Blist* d,Blist* d1);
        //删除指定数据的节点
        void erase(Blist* d);
        //修改指定数据
        void updata(Blist* d,Blist* d1);
        int  exsit_if(Blist* d);                                //用来还书时校验用户输入的isbn是否在借阅列表
        //打印
        void print();
    private:
        //节点结构
        Blist* init=NULL;
        struct Node{
            int         retuenif;
            std::string bookname;
            std::string author;
            std::string borrowtime;
            std::string isbn;
            std::string bclass;
            Node * next;
            Node(Blist* d):next(NULL){}//开辟空间的同时初始化
        };
        Node * head;//头节点
        //清理链表函数
        void clear(){
            Node * p = head;
            //从头节点开始循环删除
            while(p){
                Node * q = p->next;
                delete p;
                p = q;
            }
        }
        //查找数据d的上一个节点位置的函数
        //为了方便后面删除操作
        Node* find(Blist* d){
            Node * p = head;
            for(;p;p=p->next){
                if(p->next->isbn==d->isbn)
                    break;
            }
            return p;
        }
  
  };
