#include "USocial.h"
#include <iostream>

User *USocial::registerUser(const std::string& name, bool isBusiness)
{
    User *u;
    if (isBusiness)
    {
        u = new BusinessUser(this);
    }
    else
    {
        u = new User(this);
    }
    u->name = name; // set the name
    unsigned long newId = 0;
    while (users.find(newId) != users.end())
    { 
        if (users[newId] == nullptr)
            break;
        newId++;
    }
    u->id = newId;
    users[newId] = u; // add the user to the map of users
    return u;
}

User *USocial::registerUser(const std::string &name)
{
    return registerUser(name, false); // in case of non-business user
}

void USocial::removeUser(User *u)
{
    if (users.find(u->id) == users.end())
    {
        // User not in the map, can't proceed
        throw std::runtime_error("Remove User Failed. User not found");
    }

    // At this point, we know the user exists in the map.
    // Now, remove the user from his friends' lists.
    for (std::list<unsigned long>::iterator it = u->friends.begin();
         it != u->friends.end(); ++it)
    {
        User *friendUser = getUserById(*it);
        if (friendUser != nullptr)
        {
            friendUser->friends.remove(u->getId());
        }
    }

    users.erase(u->id); // remove user from the map
    delete u;
    u = nullptr;
}

void USocial::showAllUsers()
{
    std::cout << "USocial Users:" << std::endl;
    std::map<unsigned long, User *> usersCopy;
    for (std::map<unsigned long, User *>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if (it->second != nullptr)
        { // check if the user exists
            usersCopy.insert(std::pair<unsigned long, User *>(it->first, it->second));
        }
    }
    for (std::map<unsigned long, User *>::iterator it = usersCopy.begin(); it != usersCopy.end(); ++it)
    {
        std::cout << it->first << " => " << it->second->getName() << std::endl;
    }
}

User *USocial::getUserById(unsigned long id)
{
    return users[id];
}

