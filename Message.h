/*
* Message.h
*/

#include <string>
#ifndef MESSAGE_H_
#define MESSAGE_H_

using namespace std;

// message must include a text
class Message {
private:
    string text;
public:
    string getText();       // getter
    Message(string text);   // constructor
};

#endif /* MESSAGE_H_ */