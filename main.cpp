#include<iostream>
#include<string>
#include"User.hpp"

int main(void){
    User user1;
    user1.showDashboard();
// No need to delete; automatic cleanup when `user` goes out of scope


    return 0;
}