#pragma once
#include "iostream"
#include "sstream"

void returnBookSQL();

class MODE
{
    private:
        /* data */
    public:
        MODE(/* args */){}
        ~MODE(){}
        virtual MODE*   loop(void)              { }
        MODE*           returnMode();
        typedef struct User
        {
            /* data */
            std::string name ;
            std::string password;
            std::string phone;
            std::string creattime;
            int         borrnum;
            std::string borrnum_str;
        }User;

        User usr;
    protected:
        MODE*           mode_return		;				
};

class FIRST_MENU : public MODE{

    private:
        /* data */
    public:
        FIRST_MENU() : MODE()					{ }
        ~FIRST_MENU ()                          { }
        virtual MODE*   loop(void);
};
class ADMIN_LODIN : public MODE{

    private:
        /* data */
    public:
        ADMIN_LODIN() : MODE()					{ }
        ~ADMIN_LODIN ()                         { }
        virtual MODE*   loop(void);
};

class ADMIN_MENU : public MODE{

    private:
        /* data */
    public:
        ADMIN_MENU() : MODE()					{ }
        ~ADMIN_MENU ()                         { }
        virtual MODE*   loop(void);
};
class LOGIN_MENU : public MODE{

    private:
        /* data */
    public:
        LOGIN_MENU() : MODE()					{ }
        ~LOGIN_MENU ()                          { }
        virtual MODE*   loop(void);
};

class MAIN_MENU : public MODE{

    private:
        /* data */
        int operate;
       
    public:
        MAIN_MENU() : MODE()					{ }
        ~MAIN_MENU ()                           { }
        virtual MODE*   loop(void);
};

class LIST_MENU : public MODE{

    private:
        /* data */
        int operate ;
        int page ;
        
    public:
        LIST_MENU() : MODE()					{ }
        ~LIST_MENU ()                           { }
        virtual MODE*   loop(void);
};

class LIST_RECORD : public MODE{

    private:
        /* data */
        int operate ;
        int page ;
        
    public:
        LIST_RECORD() : MODE()					{ }
        ~LIST_RECORD ()                           { }
        virtual MODE*   loop(void);
};

class ADD_MENU : public MODE{

    private:
        /* data */
    public:
        ADD_MENU() : MODE()					   { }
        ~ADD_MENU ()                           { }
        virtual MODE*   loop(void);
};

class BORR_MENU : public MODE{

    private:
        /* data */
        void updateSQL(std::string bisbn);
    public:
        BORR_MENU() : MODE()					{ }
        ~BORR_MENU ()                           { }
        virtual MODE*   loop(void);
};
void loop(void);

