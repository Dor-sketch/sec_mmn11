#pragma once

#include <string>

class Message {
 private:
  std::string text;

 public:
  Message(const std::string
              &text);  // ctor makes sure that every message has a text
  const std::string &getText() const;
};
