#pragma once

#include <list>
#include <memory>
#include <string>

#include "Media.hpp"
#include "Message.hpp"
#include "Post.hpp"

// Forward declaration to avoid circular dependency
class USocial;

class User {
 private:
  friend class USocial;
  User();  // private ctor should not be called

 protected:
  std::weak_ptr<USocial> us;  // weak_ptr to avoid circular dependency
  unsigned long id;
  std::string name;
  std::list<unsigned long> friends;
  std::list<std::shared_ptr<Post>> posts;
  std::list<std::shared_ptr<Message>> receivedMsgs;

 public:
  explicit User(std::shared_ptr<USocial>
                    us);  // Ensures every user has a pointer to USocial
  virtual ~User();

  unsigned long getId() const;
  std::string getName() const;
  std::list<std::shared_ptr<Post>> getPosts() const;
  void viewFriendsPosts() const;

  void setId(unsigned long id);
  void setName(const std::string &name);

  void addFriend(std::shared_ptr<User> u);
  void removeFriend(std::shared_ptr<User> u);
  void post(const std::string &text);
  void post(const std::string &text, std::shared_ptr<Media> media);
  void receiveMessage(std::shared_ptr<Message> m);
  virtual void sendMessage(std::shared_ptr<User> u, std::shared_ptr<Message> m);
  void viewReceivedMessages();
};

class BusinessUser : public User {
 public:
  explicit BusinessUser(std::shared_ptr<USocial> us);
  void sendMessage(std::shared_ptr<User> u, std::shared_ptr<Message> m)
      override;  // business user can send messages to multiple users
};
