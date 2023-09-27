/*
* USocial.cpp
*/

#include "USocial.h"
#include <iostream>

// only way to create a user is through USocial
User * USocial::registerUser(string name, bool isBusiness) {
    User* u;
    if (isBusiness) {
        u = new BusinessUser(this);
    } else {
        u = new User(this);
    }
    u->name = name; // set the name
    unsigned long newId = 0;
    while (users.find(newId) != users.end()) { // loop until we find an available ID
        if (users[newId] == nullptr)
            break;
        newId++;
    }
    u->id = newId;
    users[newId] = u; // add the user to the map of users
    return u;
}

User *USocial::registerUser(string name) {
    return registerUser(name, false); // in case of non-business user
}

void USocial::removeUser(User* u) {
    User* user = getUserById(u->id);
    if(user == NULL) { // check if the user exists
        throw std::runtime_error("Remove User Failed. User not found");
    }

    // remove the user from his friends' lists
    for (list<unsigned long>::iterator it = u->friends.begin(); it != u->friends.end(); ++it) {
        User* friendUser = getUserById(*it);
        if (friendUser != nullptr) {
            friendUser->friends.remove(u->getId());
        }
    }
    users.erase(u->id); // remove the user from the map of users
    delete u;           // free the memory allocated for the user object
}

// show all users currently in the social network - for debugging
void USocial::showAllUsers() {
    cout << "USocial Users:" << endl;
    map<unsigned long, User*> usersCopy;
    for (map<unsigned long, User*>::iterator it = users.begin(); it != users.end(); ++it) {
        if (it->second != nullptr) { // check if the user exists
            usersCopy.insert(pair<unsigned long, User*>(it->first, it->second));
        }
    }
    for (map<unsigned long, User*>::iterator it = usersCopy.begin(); it != usersCopy.end(); ++it) {
        std::cout << it->first << " => " << it->second->getName() << endl;
    }
}

User *USocial::getUserById(unsigned long id) {
    return users[id];
}

