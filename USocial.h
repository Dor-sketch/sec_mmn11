/*
* USocial.h
*/

#ifndef USOCIAL_H_
#define USOCIAL_H_

#include <map>
#include "User.h"

// declaration of USocial class
class USocial {
private:
    map<unsigned long, User*> users;    // map of users
    friend class User;                  // User class is a friend of USocial
public:
    User * registerUser(string, bool);  // register a user - the bool is for business user
    User * registerUser(string);        // a version for non-business user
    void removeUser(User*);             // remove a user from the social network along with all of his content
    User * getUserById(unsigned long) ; // get a user by id
    void showAllUsers() ;               // show all users - for debugging
};

#endif /* USOCIAL_H_ */