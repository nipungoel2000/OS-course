#define PORT 5500

#define START 0
#define INVALID -1
#define SIGNUP 1
#define SIGNIN 2

#define SIGN_UP_AS_USER 3
#define SIGN_UP_AS_JOINT 4
#define SIGN_UP_AS_ADMIN 5
#define SIGN_IN_AS_USER 6
#define SIGN_IN_AS_JOINT 7
#define SIGN_IN_AS_ADMIN 8
#define USER 9
#define ADMIN 10
#define DEPOSIT 11
#define WITHDRAW 12
#define BALANCE_CHECK 13
#define PWD_CHANGE 14
#define VIEW_DETAILS 15
#define EXIT 16
#define ADD_USER 17
#define MOD_USER 18
#define DEL_USER 19
#define GET_USER_DETAILS 20

struct user
{
    char type[32];
    char username[128];
    char password[128];
};

struct account
{
    int balance;
};