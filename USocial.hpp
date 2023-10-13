#pragma once

#include <map>
#include <memory>

#include "User.hpp"

class USocial : public std::enable_shared_from_this<USocial> {
 private:
  std::map<unsigned long, std::shared_ptr<User>>
      users;          // using shared_ptr to avoid memory leaks
  friend class User;  // User class is a friend of USocial

 public:
  std::shared_ptr<User> registerUser(
      const std::string &name,
      bool isBusiness);  // The 'bool' parameter indicates if the user is a
                         // business user.
  std::shared_ptr<User> registerUser(
      const std::string &name);  // ctor for non-business user
  std::shared_ptr<User> getUserById(unsigned long id);
  void removeUser(std::shared_ptr<User> user);
  void showAllUsers();  // for debugging
};
