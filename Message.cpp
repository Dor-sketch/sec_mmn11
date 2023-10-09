#include "Message.h"

Message::Message(const std::string &text)
{
    this->text = text;
}

const std::string& Message::getText() const 
{
    return text;
}
