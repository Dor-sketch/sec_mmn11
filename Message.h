#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <string>

class Message {
private:
    std::string text;
    
public:
    Message(const std::string &text); // ctor makes sure that every message has a text
    std::string getText() const;
};

#endif /* MESSAGE_H_ */