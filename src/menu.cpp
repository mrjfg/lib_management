#include "menu.h"
#include "book.h"
#include "iostream"
#include "myDB.h"
#include "sstream"
#include "iomanip"
#include "stdio.h"


#include<mysql/mysql.h>
using namespace std;
Blist borrlist;                             //定义借书记录结构体，用来插入链表

struct addList{
    string author;
    string title;
    string isbn;
    string bclass;
    int    inlabif;
};
addList addlist;
static MAIN_MENU       mode_main;
static LIST_MENU       mode_list;
static ADD_MENU        mode_add;
static LOGIN_MENU      mode_login;
static BORR_MENU       mode_borr;
static FIRST_MENU      mode_first;
static ADMIN_LODIN     mode_adminlogin;
static LIST_RECORD     mode_lisrecord;
static ADMIN_MENU      mode_admin;
static MODE*           pMode = &mode_first;           //设置第一个界面


BookList list;                                        //新建链表类    同时初始化链表（在book.h中Booklist类写的是，创建同时初始化)

MODE::User globalusr;                                 //定义本地个人信息结构体，用来存储从数据库中读取出来的个人信息

MODE* MODE::returnMode(){
    if(mode_return)
        return mode_return;
    return this;
}

void get_operate (int* operate){
    cin>> *operate;
    while(cin.fail()){
        cin.clear();
        cin.ignore();
        cin>>*operate;
    }
}
/************************************
 *     author   rainbow
 *     func     wait usr input to return main_menu
 *     timr     2020.09.14:2:26
***********************************/
void waitUsr(){
    int i;
    cout <<"输入任意字符并按回车返回主界面：";
    cin >>i;

}

/************************************
 *     author   rainbow
 *     func     login menu
 *     timr     2020.09.11:2:26
***********************************/
void serchBorrRecode(){
    stringstream str4sql;
    MYSQL_RES*   sresult;
    stringstream s;
    MYSQL_ROW row;         //按行返回的查询信息
    str4sql << "SELECT * FROM `lib_management`.`record` WHERE `phon` = '"<<globalusr.phone<<"' ;";        //拼接sql语句，查询ISBN对应书籍
    if(db.serchRecSQL(str4sql.str(),&sresult)){

        int  num_fields = mysql_num_fields(sresult);   //获取结果集中总共的字段数，即列数
        int  num_rows   = mysql_num_rows(sresult);       //获取结果集中总共的行数
        if(sresult){
            for (int i = 0; i < num_rows; i++) //输出每一行
            {

                //获取下一行数据
                row = mysql_fetch_row(sresult);
                if (row < 0)                                                                                //如果查询的数据为空（语句没有格式错误，但没有该数据）
                    break;                                                                                  //则跳出循环
                borrlist.isbn       = row[1];                                                               //填充借书记录结构体
                borrlist.borrowtime = row[2];
                s << row[3];                                                                                //将bit转化为字符串
                s >> borrlist.retuenif;
                list.insert(&borrlist); 
                //cout <<borrlist.isbn;
            }

        }
    }
    else {
        cout <<"error";
    }
}

/************************************
 *     author   rainbow
 *     func     first menu jump to 
 *             1  admin loginmode 
 *             2  normal login mode
 *             3 register mode
 *     timr     2020.09.11:2:26
***********************************/
MODE* FIRST_MENU::loop(){
    int operate;
    std::cout << "\x1B[2J\x1B[H";
    cout <<endl;
    //cout<<globalusr.name<<"\t\t"<<globalusr.phone<<"\t\t"<<globalusr.password<<"\t\t"<<globalusr.creattime<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t     ******This is library management******"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t     ******Please choose an operation******"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t           Administrator account login     1"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t               normal account login        2"<<endl;
    cout <<endl; 
    cout <<setw(30)<<""<<"\t                    registered             3"<<endl;
    cout <<setw(30)<<"";
    get_operate(&operate);
    switch (operate)
    {
        case 1:
            /* code */
            pMode = &mode_adminlogin;
            break;
        case 2:
            pMode = &mode_login;
            break;

        case 3:
            cout <<"现有帐号18855552222  密码123456"<<endl;
            waitUsr();
            
            break;

        default:
            break;
    }
}

MODE * ADMIN_LODIN::loop(){
    std::stringstream str4sql;
    string check;
    std::cout << "\x1B[2J\x1B[H";                                               //清屏
    cout <<endl;
    cout <<setw(40)<<""<<"\t******Enter user administrator account******"<<endl;
    cout <<endl;
    cout <<setw(40)<<"";
    cin>>usr.phone;
    str4sql << "SELECT * FROM `lib_management`.`usr` WHERE `phone` = '"<<usr.phone<<"' ;";      //拼接sql语句
    if(db.exeSQL(str4sql.str(), &usr)){                                                         //这里需要判断读出来的用户数据是否为空，查询数据时语句没错会返回真
        if(usr.password==""){
            cout <<setw(50)<<""<<"phone number error"<<endl;
            waitUsr(); 
            pMode = &mode_first;                            //不一致则提示密码错误，返回登录界面
        }
        else{
            
            cout <<setw(50)<<""<<"plase enter your password"<<endl;
            cout <<endl;
            cout <<setw(40)<<"";
            cin  >>check;
            if(check==usr.password)                         //检查输入的密码和数据库中存储的密码是否一致
            {
                 
                pMode = &mode_admin;                
                
            }
            else
            {
                cout <<"password error"<<endl;
                waitUsr();
                
                pMode = &mode_first;                        //不一致则提示密码错误，返回登录界面
            }
        }
            
    }
    else{
        cout <<"phone number error"<<endl;
        waitUsr();
        pMode = &mode_first;                                //不一致则提示密码错误，返回登录界面
    }
}

MODE* ADMIN_MENU::loop(){
    int operate;

    std::cout << "\x1B[2J\x1B[H";                                               //清屏
        cout <<endl;
    cout <<setw(30)<<""<<"\t******This is library management******"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t******Please choose an operation******"<<endl;
    cout <<endl;  
    cout <<setw(30)<<""<<"\t           add  book(s)           1"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t   View all borrowing records     2"<<endl;
    cout <<endl; 
    get_operate(&operate);
    switch (operate)
    {
        case 1:
            /* code */
            pMode = &mode_add;                              //跳转到添加书籍模式

            break;
        case 2:
            pMode = &mode_lisrecord;
            break;
        default:
            break;
    }
}
/************************************
 *     author   rainbow
 *     func     login menu
 *     timr     2020.09.11:2:26
***********************************/
MODE* LOGIN_MENU::loop(){
    int c;
    std::stringstream str4sql;
    string check;
    std::cout << "\x1B[2J\x1B[H";                                               //清屏
    cout <<endl;
    cout <<setw(40)<<""<<"\t******Enter user phone number******"<<endl;
    cout <<endl;
    cout <<setw(40)<<"";
    cin.clear();
    cin.ignore();
    cin>>usr.phone;
    str4sql << "SELECT * FROM `lib_management`.`usr` WHERE `phone` = '"<<usr.phone<<"' ;";      //拼接sql语句
    if(db.exeSQL(str4sql.str(), &usr)){                                                         //这里需要判断读出来的用户数据是否为空，查询数据时语句没错会返回真
        if(usr.password==""){
            cout <<setw(50)<<""<<"phone number error"<<endl;
            waitUsr(); 
            pMode = &mode_login;                            //不一致则提示密码错误，返回登录界面
            return pMode;
        }
        else{
            
            cout <<setw(50)<<""<<"plase enter your password"<<endl;
            cout <<endl;
            cout <<setw(40)<<"";
            cin  >>check;
            if(check==usr.password)                         //检查输入的密码和数据库中存储的密码是否一致
            {
                cout <<endl;
                globalusr =usr; 
                serchBorrRecode();                          //填充借书链表                       
                pMode = &mode_main;                         //一致则进入主界面，并将个人数据保存到本地的结构体中
            }
            else
            {
                cout <<"password error"<<endl;
                waitUsr();
                pMode = &mode_login;                        //不一致则提示密码错误，返回登录界面
            }
        }
            
    }
    else{
        cout <<"phone number error"<<endl;
        waitUsr();
        pMode = &mode_login;                                //不一致则提示密码错误，返回登录界面
    }

}
/************************************
 *     author   rainbow
 *     func     main menu
 *     timr     2020.09.10
***********************************/
MODE* MAIN_MENU::loop(){
    std::cout << "\x1B[2J\x1B[H";
    cout <<endl;
    //cout<<globalusr.name<<"\t\t"<<globalusr.phone<<"\t\t"<<globalusr.password<<"\t\t"<<globalusr.creattime<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t******This is library management******"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t******Please choose an operation******"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t           return  book(s)     1"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t            Search by name     2"<<endl;
    cout <<endl; 
    cout <<setw(30)<<""<<"\t            Search by isbn     3"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t             List    all       4"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t           borrow   book(s)    5"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t          Search by category   6"<<endl;
    cout <<endl;
    cout <<setw(30)<<""<<"\t------------------------------------------"<<endl;
    cout <<setw(30)<<""<<"\t        $$ Personal center $$  7"<<endl;
    cout <<endl;
    cout <<setw(40)<<""<<"plase enter your operate :";
    get_operate(&operate);

    switch (operate)
    {
        case 1:
            returnBookSQL();                                //跳转到还书界面
            break;
        case 2:
            cout <<setw(50)<<""<<"该功能尚未开发"<<endl;
            waitUsr();
            pMode = &mode_main;
            
            break;
        case 3:
            cout <<setw(50)<<""<<"该功能尚未开发"<<endl;
            waitUsr();
            pMode = &mode_main;
            break;
        case 4:
            pMode = &mode_list;                              //跳转到列表模式
            break;
        case 5:
            pMode = &mode_borr;                              //跳转到借书模式
            break;
        case 6:
            cout <<setw(50)<<""<<"该功能尚未开发"<<endl;
            waitUsr();
            pMode = &mode_main;
            break;
        case 7:
            //serchBorrRecode();
            list.print();                                                                               //将查询到的数据循环插入到链表之中
            cout << endl;                                                                               //打印链表的内容（也就是一个人所借的所有书）
            cout <<"以上是所借的书籍信息"<<endl;
            waitUsr();
            
            break;
        default:
            break;
    }
    
}
/************************************
 *     author   rainbow
 *     func     list borrow book record
 *     timr     2020.09.10
***********************************/
MODE* LIST_RECORD::loop(){
    std::cout << "\x1B[2J\x1B[H";
    //将所有用户信息按页读出，并打印。
    std::stringstream str4sql;

    cout << setw(30) <<"Author"<< setw(20) <<"Isbn"<< setw(20) <<"Class"<< setw(20) <<"Statue"<< setw(20) <<"Title\n";

    str4sql << "SELECT * from record limit "<<page*10<<","<<page*10+9<<" ;";
    db.exeSQL(str4sql.str());
    
    cout <<endl;
    cout <<endl;
    cout<<"\t\t------------- plase enter operate -----------------";
    cout <<endl;
    cout<<"\t\t              page up                    1         ";
    cout <<endl;
    cout<<"\t\t              page down                  2         ";
    cout <<endl;
    cout<<"\t\t              Back to main page          3         ";
    cout <<endl;
    cout <<"plase enter your operate :";
    get_operate(&operate);
    switch (operate)
    {
    case 1:
        /* code */
        page++;
        break;
    case 2:
        page--;
        page = page<0?0:page;
        break;
    case 3:
        pMode = &mode_admin;
        break;
    default:
        break;
    }
}
/************************************
 *     author   rainbow
 *     func     list menu
 *     timr     2020.09.10
***********************************/
MODE* LIST_MENU::loop(){
    std::cout << "\x1B[2J\x1B[H";
    //将所有用户信息按页读出，并打印。
    std::stringstream str4sql;

    cout << setw(30) <<"Author"<< setw(20) <<"Isbn"<< setw(20) <<"Class"<< setw(20) <<"Statue"<< setw(20) <<"Title\n";

    str4sql << "SELECT * from book limit "<<page*10<<","<<page*10+9<<" ;";
    db.exeSQL(str4sql.str());
    
    cout <<endl;
    cout <<endl;
    cout<<"\t\t------------- plase enter operate -----------------";
    cout <<endl;
    cout<<"\t\t              page up                    1         ";
    cout <<endl;
    cout<<"\t\t              page down                  2         ";
    cout <<endl;
    cout<<"\t\t              Back to main page          3         ";
    cout <<endl;
    cout <<"plase enter your operate :";
    cin>>operate;
    switch (operate)
    {
    case 1:
        /* code */
        page++;
        break;
    case 2:
        page--;
        page = page<0?0:page;
        break;
    case 3:
        pMode = &mode_main;
        break;
    default:
        break;
    }
}


/************************************
 *     author   rainbow
 *     func     add book menu
 *     timr     2020.09.10
***********************************/
MODE* ADD_MENU::loop(){
    std::cout << "\x1B[2J\x1B[H";
    cout <<endl;
    cout <<"\t\t 添加完成之后会自动退出，如需批量添加请使用电子表格导入"<<endl;
    cout<<"\t\t              plase input   title       : ";                     //获取所需添加书籍的信息
    cin >>addlist.title;
    cout <<endl;
    cout<<"\t\t              plase input   author      : ";
    cin >>addlist.author;
    cout <<endl;
    cout<<"\t\t              plase input   isbn        : ";
    cin >>addlist.isbn;
    cout <<endl;
    cout<<"\t\t              plase input   class       : ";
    cin >>addlist.bclass;
    cout <<endl;
    addlist.inlabif = 1;
    string sqlstr ="INSERT INTO book (author,isbn,class,inlabif,name) values('"+addlist.author+"',  \
                    '"+addlist.isbn+"','"+addlist.bclass+"',"+"1"+",'"+addlist.title+"');";
    db.exeSQL(sqlstr);
    pMode = &mode_admin;
}
/************************************
 *     author   rainbow
 *     func     borrow menu
 *     timr     2020.09.10
***********************************/
MODE* BORR_MENU::loop(){
    string isbn;
    std::stringstream str4sql;
    int   operate;
    std::cout << "\x1B[2J\x1B[H";
    cout <<endl;
    if(globalusr.borrnum >=10){                                                                                 //首先判断个人信息中是否借书超过10本
        cout << "you have borrowde 10 books"<<endl;
        cout <<endl;
        cout <<"enter any key to return "<<endl;
        system("pause");
        pMode = &mode_main;                                                                                     //超过10本，则提示并返回主界面
    }
    else {
        cout <<setw(50)<<"you have borrowed "<<globalusr.borrnum<<" book(s)"<<endl;                             //提示借过几本书
        cout <<setw(50)<<"plase enter ISBN "<<endl;                                                             //接收ISBN
        cin >>isbn;


        str4sql << "SELECT * FROM `lib_management`.`book` WHERE `isbn` = '"<<isbn<<"' ;";                       //拼接sql语句，查询ISBN对应书籍
        switch (db.serch4borrowSQL(str4sql.str()))
        {
            case 1:
                /* code */
                cout << setw(30) <<"Author"<< setw(20) <<"Isbn"<< setw(20) <<"Class"<< setw(20) <<"Statue"<< setw(20) <<"Title\n";

                cout << endl<< endl;                                                            //查询成功，显示书籍信息，提示用户检查信息是否正确，提示继续借书或者返回
                cout << setw(60) << "place chack information for book" << endl;
                cout << setw(50) << "enter 1 to borrow" << endl;
                cout << setw(50) << "enter 2 to cancel" << endl;
                get_operate(&operate);
                switch (operate)
                {
                    case 1:
                        /* code */
                        updateSQL(isbn);  
                        
                        break;
                    case 2:
                        pMode = &mode_main;
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                cout << setw(30) <<"Author"<< setw(20) <<"Isbn"<< setw(20) <<"Class"<< setw(20) <<"Statue"<< setw(20) <<"Title\n";
                cout << endl<< endl;                                                            
                
                cout <<setw(50) <<"this book is borrowed by others!"<<endl;                                      //查询成功，但图书被借走
                waitUsr();
                pMode = &mode_main;
                break;
            case 3:
                cout <<setw(50) <<"There is no library or this book"<<endl;                                      //查询失败，图书馆没有这本书
                waitUsr();
                pMode = &mode_main;
                break;
            default:
                cout << "error"<<endl;
                waitUsr();
                break;
        }
    }
}
/************************************
 *     author   rainbow
 *     func     int to string
 *     timr     2020.09.10
***********************************/
string inttostring(int in)
{
	stringstream ss;
	string str;
	ss << in;
	ss >> str;
	return str;
}
/************************************
 *     author   rainbow
 *     func     get time
 *     timr     2020.09.10
***********************************/
int getTime( char *gtime) {

    time_t tt;
    time( &tt );
    tt = tt + 8*3600;  // transform the time zone
    tm* t= gmtime( &tt );

    sprintf(gtime, "%d-%02d-%02d %02d:%02d:%02d\n",
           t->tm_year + 1900,
           t->tm_mon + 1,
           t->tm_mday,
           t->tm_hour,
           t->tm_min,
           t->tm_sec);

    return 0;
}
/************************************
 *     author   rainbow
 *     func     updata database while borrowed book(s)
 *     timr     2020.09.10
***********************************/
void BORR_MENU::updateSQL(string bisbn){
    stringstream s;
    char gtime ;
    string sqlstr ="UPDATE book SET inlabif='0' WHERE isbn ='"+bisbn+"';";
    db.exeSQL(sqlstr);

   
    sqlstr = "INSERT INTO record (phon,isbn,returnif) values('"+globalusr.phone+"',  \
                    '"+bisbn+"',"+"0"+");";
    db.exeSQL(sqlstr);

    sqlstr = "UPDATE  record SET time = NOW() WHERE isbn = '"+bisbn+"'";
    db.exeSQL(sqlstr);

    s<<globalusr.borrnum+1;
    s>>globalusr.borrnum_str;
    sqlstr ="UPDATE usr SET borrnum = '"+globalusr.borrnum_str+"' WHERE phone \
                    ='"+globalusr.phone+"';";
    db.exeSQL(sqlstr);
    // getTime(&gtime);
    // s<<gtime;
    borrlist.isbn       = bisbn;                                                               //填充借书记录结构体
    //borrlist.borrowtime = s.str();
    borrlist.retuenif = 0;
    list.insert(&borrlist); 
    cout<<setw(50)<<"" <<"借书成功"<<endl;
    waitUsr();
    pMode = &mode_main;  
}
/************************************
 *     author   rainbow
 *     func     updata database while return book(s)
 *     timr     2020.09.10
***********************************/
void returnBookSQL(){
    stringstream s;
    string bisbn;
    cout<<setw(50)<<"" <<"plase enter ISBN"<<endl;
    cin >> bisbn;
    borrlist.isbn       = bisbn;                                                               //填充借书记录结构体
    borrlist.retuenif = 0;
    if(!list.exsit_if(&borrlist)){
        cout<<setw(50)<<"" <<"请输入正确的ISBN"<<endl;
        waitUsr();
        pMode = &mode_main;
        return;
    }
    list.erase(&borrlist); 
    string sqlstr ="UPDATE book SET inlabif='1' WHERE isbn ='"+bisbn+"';";
    db.exeSQL(sqlstr);

   
    sqlstr = "DELETE FROM record WHERE isbn='"+bisbn+"';";
    db.exeSQL(sqlstr);

    sqlstr = "UPDATE  record SET time = NOW() WHERE isbn = '"+bisbn+"'";
    db.exeSQL(sqlstr);

    s<<globalusr.borrnum-1;
    s>>globalusr.borrnum_str;
    sqlstr ="UPDATE usr SET borrnum = '"+globalusr.borrnum_str+"' WHERE phone \
                    ='"+globalusr.phone+"';";
    db.exeSQL(sqlstr);
    
    cout<<setw(50)<<"" <<"还书成功";
    waitUsr();
    pMode = &mode_main;
}

/************************************
 *     author   rainbow
 *     func     main menu
 *     timr     2020.09.10
***********************************/
void loop(void) {
    pMode->loop();
}