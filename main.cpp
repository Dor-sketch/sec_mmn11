#include "USocial.h"
#include "User.h"

#include <exception>
#include <iostream>


// main function to demonstrate of how to use the USocial
int main()
{
    std::shared_ptr<USocial> us = std::make_shared<USocial>();
    us->showAllUsers();

    std::shared_ptr<User> u1 = us->registerUser("Dor");
    std::shared_ptr<User> u2 = us->registerUser("Lev");
    std::shared_ptr<User> u3 = us->registerUser("Ligal");
    std::shared_ptr<User> u4 = us->registerUser("Super Eitan", true);
    std::shared_ptr<User> u5 = us->registerUser("Bad Guy");
    
    u1->post("Hello world!");
    u2->post("I'm having a great time here :)", std::make_shared<Audio>());
    u3->post("This is awesome!", std::make_shared<Photo>());

    u5->addFriend(u1);      // bad guy is now friends with Dor
    u5->addFriend(u2);      // bad guy is now friends with Lev

    std::cout << "Trying to add bad guy as friend of Dor again:\n";
    try {
        // Dor is already friends with bad guy - should throw exception
        u1->addFriend(u5);
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    std::cout << "Trying to remove Ligal from Bad guy's friends - should fail\n";
    try {
        // bad guy is not friends with Ligal - should throw exception
        u5->removeFriend(u3);   
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    std::cout << "\n-----Bad guy's Feed:\n";
    // bad guy should see only Dor, Lev s' posts
    u5->viewFriendsPosts();    
    
    u4->sendMessage(u5, std::make_shared<Message>("Eitan: hello bad guy! I'm a business user!"));
    
    std::cout << "\n-----Bad guy's Inbox:\n";
    u5->viewReceivedMessages();

    // check sending message to non-friend
    try {
        u3->sendMessage(u5, std::make_shared<Message>("Ligal: Hey, bad guy! I'm not your friend!"));
    } catch (const std::exception& e) {
        std::cout << "error: " << e.what() << std::endl;
    }

    std::cout << "\n-----Bad guy's Inbox:\n";
    u5->viewReceivedMessages();
    
    u3->addFriend(u5);
    // Ligal is now friends with bad guy
    u3->sendMessage(u5, std::make_shared<Message>("Ligal: Hey, bad guy! I'm your friend now!"));

    std::cout << "\n-----Bad guy's Inbox:\n";
    u5->viewReceivedMessages();

    us->showAllUsers();

    std::cout << "trying to remove user: \n";
    // check removing user
    if (u1 != nullptr)
    {
        try {
            us->removeUser(u1);
        } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    us->showAllUsers();

    std::cout << "trying to remove user again: \n";
    if (u1 != nullptr)
    {
        try
        {
            us->removeUser(u1);
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "trying to register user with same name: \n";
    std::shared_ptr<User>u6 = us->registerUser("Dor");

    std::cout << "\n-----Bad guy's Inbox:\n";
    u5->viewReceivedMessages();

    us->showAllUsers();

    return 0;
}