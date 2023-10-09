#include "USocial.h"
#include <iostream>

std::shared_ptr<User> USocial::registerUser(const std::string &name, bool isBusiness)
{
    std::shared_ptr<User> u;
    if (isBusiness)
    {
        u = std::make_shared<BusinessUser>(shared_from_this());
    }
    else
    {
        u = std::make_shared<User>(shared_from_this());
    }
    u->name = name; // set the name
    unsigned long newId = 0;
    while (users.find(newId) != users.end())
    {
        if (users[newId] == nullptr)
        {
            break;
        }
        newId++;
    }
    u->id = newId;
    users[newId] = u; // add the user to the map of users
    return u;
}

std::shared_ptr<User> USocial::registerUser(const std::string &name)
{
    return registerUser(name, false); // in case of non-business user
}

void USocial::removeUser(std::shared_ptr<User> u)
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
        std::shared_ptr<User> friendUser = getUserById(*it);
        if (friendUser != nullptr)
        {
            friendUser->friends.remove(u->getId());
        }
    }

    users.erase(u->id); // remove user from the map
    // auto ptr will delete the user object
    u = nullptr;
}

void USocial::showAllUsers()
{
    std::cout << "USocial Users:" << std::endl;
    std::map<unsigned long, std::shared_ptr<User>> usersCopy;
    for (std::map<unsigned long, std::shared_ptr<User>>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if (it->second != nullptr)
        { // check if the user exists
            usersCopy.insert(std::pair<unsigned long, std::shared_ptr<User>>(it->first, it->second));
        }
    }
    for (std::map<unsigned long, std::shared_ptr<User>>::iterator it = usersCopy.begin(); it != usersCopy.end(); ++it)
    {
        std::cout << it->first << " => " << it->second->getName() << std::endl;
    }
}

std::shared_ptr<User> USocial::getUserById(unsigned long id)
{
    return users[id];
}
