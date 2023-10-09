#include "Message.h"

Message::Message(const std::string &text)
{
    this->text = text;
}

std::string Message::getText() const
{
    return text;
}
