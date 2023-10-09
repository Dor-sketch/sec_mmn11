#ifndef USOCIAL_H_
#define USOCIAL_H_

#include "User.h"
#include <map>
#include <memory>

class USocial {
private:
    std::map<unsigned long, User *> users; 
    friend class User; // User class is a friend of USocial

public:
    User *registerUser(const std::string &name, bool isBusiness);  // The 'bool' parameter indicates if the user is a business user.
    User *registerUser(const std::string &name);  // ctor for non-business user

    User * getUserById(unsigned long id);
    void removeUser(User*);             
    void showAllUsers(); // for debugging
};

#endif /* USOCIAL_H_ */