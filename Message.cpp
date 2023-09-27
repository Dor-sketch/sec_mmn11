/*
* Message.cpp
*/

#include "Message.h"

Message::Message(string text) {
    this->text = text;
}

string Message::getText() {
    return text;
}

