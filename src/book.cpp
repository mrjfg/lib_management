#include "book.h"
#include "string"
#include "fstream"
#include "iomanip"
#include "iostream"
using namespace std;

book::book(std::string& btitle ,std::string& bisbn ,std::string& bclass ,std::string& bauthor, int bprice){
    title = btitle;
    isbn  = bisbn;
    class_= bclass;
    price = bprice;
    author= bauthor;
}
std::string& book::getTitle(){
    return title;
}
int book::saveBook(){
    
}

 //
//  List.cpp
//  List
   //
   //  Created by scandy_yuan on 13-1-6.
   //  Copyright (c) 2013年 Sam. All rights reserved.
   //
   


  
  //创建头结点
  void BookList::create_List()
  {
       head = new Node(init);
  }
  //从头插入一个节点
  void BookList::insert(Blist* d)
  {
      Node *p = new Node(d);
      p->next = head->next;
      head->next = p;
  }
  //打印函数
  void BookList::print()
  {
      for(Node * p = head->next;p;p=p->next){
          cout << "\t\t\t"<<p->data->isbn <<"\t\t\t\t"<<p->data->borrowtime<<"\t\t\t\t\t"<<p->data->retuenif<< endl;
      }
  }
  //在d位置之前插入d1
  void BookList::insert_pos(Blist* d,Blist* d1)
  {
      Node * p = find(d);
      Node * q = new Node(d1);
      q->next = p->next;
      p->next = q;
  }
  
  //删除
  void BookList::erase(Blist* d)
  {
      Node * p = find(d);
      //因为p是上一个节点的位置，用q来保存
      //要删除的节点的地址
      Node *q = p->next;
      //通过将上一个节点的next指针指向要删除节点的next指
      //针志向的节点实现断开要删除节点的目的
      p->next = p->next->next;
      //删除要删除的节点q
      delete q;
 }
 
 //修改指定数据
 void BookList::updata(Blist* d,Blist* d1)
 {
     Node * p = find(d);
     p->next->data = d1;
 }
 
 //得到链表长度
 
 
//  int main(int argc, const char * argv[])
//  {
 
//      // insert code here...
//      BookList list;
//      list.insert(30);
//      list.insert(20);
//      list.insert(10);
//      list.insert_pos(10, 5);
//      list.print();
//      cout << "---------------------" << endl;
//      list.erase(10);
//      list.print();
//      cout << "---------------------" << endl;
//      list.reverse();
//      list.print();
//      cout << "---------------------" << endl;
//      list.updata(5, 8);
//      list.print();
//      return 0;
 