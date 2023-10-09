#include "USocial.h"
#include <iostream>

void User::setId(unsigned long newId)
{
    if (newId <= 0) // ID can't be zero or negative
    {
        throw std::invalid_argument("Invalid ID");
    }
    id = newId;
}


void User::setName(const std::string &newName)
{
    if (newName.empty()) // Using empty() to check for empty string
    {
        throw std::invalid_argument("Name cannot be empty");
    }
    name = newName;
}


std::shared_ptr<User> USocial::registerUser
    (const std::string &name, bool isBusiness)
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


    try
    {
        u->setName(name);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        u->setName("DefaultUser_" + std::to_string(users.size() + 1));
    }


    unsigned long newId = 1;
    while (users.find(newId) != users.end())
    {
        if (users[newId] == nullptr)
        {
            break;
        }
        newId++;
    }

    try
    {
        u->setId(newId);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Register User Failed: " << e.what() << std::endl;
        return nullptr;
    }

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
}

void USocial::showAllUsers()
{
    std::cout << "Getting USocial Registered Users... ";
    std::map<unsigned long, std::shared_ptr<User>> usersCopy;
    if (users.empty())
    {
        std::cout << "No users found" << std::endl;
        return;
    }
    else
    {
        std::cout << "Found " << users.size() << " users:" << std::endl;
    }
    for (const auto &pair : users)
    {
        unsigned long id = pair.first;
        std::shared_ptr<User> userPtr = pair.second;
        if (userPtr)
        {
            std::cout << "ID " << id << " => " << userPtr->getName() << std::endl;
        }
    }
}

std::shared_ptr<User> USocial::getUserById(unsigned long id)
{
    auto it = users.find(id);
    if (it == users.end())
    {
        // User not in the map, can't proceed
        throw std::runtime_error("Get User Failed. User not found");
    }
    return it->second;
}
