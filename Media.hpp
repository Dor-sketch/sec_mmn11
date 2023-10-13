#pragma once

#include <string>

class Media {
 public:
  virtual ~Media() {}  // current code doesn't use dynamic memory allocation,
                       // but it's good practice to have a virtual dtor
  virtual void display() const = 0;
  virtual std::string getType() const = 0;
};

class Photo : public Media {
 public:
  void display() const override;
  std::string getType() const override;
};

class Audio : public Media {
 public:
  void display() const override;
  std::string getType() const override;
};

class Video : public Media {
 public:
  void display() const override;
  std::string getType() const override;
};

