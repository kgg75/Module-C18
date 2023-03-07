#pragma once
#include <string>
#include <fstream>
#include <iostream>


class User {
    public:
        User();
        User(const std::string& name,
            const std::string& login,
            const std::string& pass) :
            _name(name),
            _login(login),
            _pass(pass)
        {};
        friend std::ostream& operator << (std::ostream& output, const User& user);
        friend std::fstream& operator << (std::fstream& output, const User& user);
    private:
        std::string _name;
        std::string _login;
        std::string _pass;
};


class Message {
    public:
        Message();
        Message(const std::string& text,
            const std::string& sender,
            const std::string& receiver) :
            _text(text),
            _sender(sender),
            _receiver(receiver)
        {};
        friend std::ostream& operator << (std::ostream& output, const Message& message);
        friend std::fstream& operator << (std::fstream& output, const Message& message);
    private:
        std::string _text;
        std::string _sender;
        std::string _receiver;
};
