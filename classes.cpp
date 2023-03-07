#include "classes.hpp"


User::User() {
	_login = _name = _pass = "";
}


Message::Message() {
	_receiver = _sender = _text = "";
}


std::ostream& operator << (std::ostream& output, const User& user) {
	output << "\tname: " << user._name << '\n' 
		<< "\tlogin: " << user._login << '\n'
		<< "\tpassword: " << user._pass << '\n';
	return output;
};


std::fstream& operator << (std::fstream& output, const User& user) {
	output << user._login << '\n' << user._name << '\n' << user._pass << std::endl;
	return output;
};


std::ostream& operator << (std::ostream& output, const Message& message) {
	output << "\ttext: " << message._text << '\n'
		<< "\tsender: " << message._sender << '\n'
		<< "\treceiver: " << message._receiver << '\n';
	return output;
};


std::fstream& operator << (std::fstream& output, const Message& message) {
	output << message._text << '\n' << message._sender << '\n' << message._receiver << '\n';
	return output; 
};