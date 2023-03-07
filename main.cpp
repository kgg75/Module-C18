#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "classes.hpp"

namespace fs = std::filesystem;

const char FILE_NAME_USERS_DATA[] {"users_data.txt"};
const char FILE_NAME_MESSAGES_DATA[] {"messages_data.txt"};


void demo_perms(fs::perms p) {
    auto show = [=](char op, fs::perms perm) {
        std::cout << (fs::perms::none == (perm & p) ? '-' : op);
    };
    show('r', fs::perms::owner_read);
    show('w', fs::perms::owner_write);
    show('x', fs::perms::owner_exec);
    show('r', fs::perms::group_read);
    show('w', fs::perms::group_write);
    show('x', fs::perms::group_exec);
    show('r', fs::perms::others_read);
    show('w', fs::perms::others_write);
    show('x', fs::perms::others_exec);
    std::cout << '\n';
}


void set_permissions(const char* file_name) {
    fs::permissions(file_name,
        fs::perms::group_all | fs::perms::others_all,
        fs::perm_options::remove);

    fs::permissions(file_name,
        fs::perms::owner_all,
        fs::perm_options::add);

    demo_perms(fs::status(file_name).permissions());
}


int main() {
    std::ios_base::openmode file_access_type = std::ios::in | std::ios::out | std::ios::app;
    std::fstream file_users(FILE_NAME_USERS_DATA, file_access_type);
    std::fstream file_messages(FILE_NAME_MESSAGES_DATA, file_access_type);

    if (!file_users.is_open())
        file_users = std::fstream(FILE_NAME_USERS_DATA, file_access_type | std::ios::trunc);
  
    if (!file_messages.is_open())
        file_messages = std::fstream(FILE_NAME_MESSAGES_DATA, file_access_type | std::ios::trunc);

    if (!file_users.is_open() || !file_messages.is_open()) {
	    std::cout << "Could not open input file!\n";
        return 1;
    }
    
    set_permissions(FILE_NAME_USERS_DATA);
    set_permissions(FILE_NAME_MESSAGES_DATA);

    std::string txt1, txt2, txt3;

    User user;
    while (file_users >> txt1 && file_users >> txt2 && file_users >> txt3) {
        user = { txt1, txt2, txt3 };
	std::cout << user;
	std::cout << "-----------------------\n";
    }
    file_users.clear();


    Message message;
    while (file_messages >> txt1 && file_messages >> txt2 && file_messages >> txt3) {
        message = { txt1, txt2, txt3 };
	std::cout << message;
	std::cout << "-----------------------\n";
    }
    file_messages.clear();

    std::cout << "Input new user data:\n";
    std::cout << "name: ";
    std::cin >> txt1;
    std::cout << "login: ";
    std::cin >> txt2;
    std::cout << "pass: ";
    std::cin >> txt3;
    if (!txt1.empty() && !txt2.empty() && !txt3.empty())
        user = { txt1, txt2, txt3 };

    std::cout << "Input new message data:\n";
    std::cout << "text: ";
    std::cin >> txt1;
    std::cout << "sender: ";
    std::cin >> txt2;
    std::cout << "receiver: ";
    std::cin >> txt3;
    if (!txt1.empty() && !txt2.empty() && !txt3.empty())
        message = { txt1, txt2, txt3 };

    file_users << user;
    file_messages << message;

    file_users.close();
    file_messages.close();

    return 0;
}
