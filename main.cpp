/*
* MAMAN 11 - course 20937 - 2023C
*/
// Author: Dor Pascal
// special thanks to my roomates: Lev and Ligal, and my teacher Eitan


#include "USocial.h"
#include "User.h"

#include <exception>
#include <iostream>

// main function - example of how to use the USocial
int main()
{
    USocial us;
    us.showAllUsers();

    User* u1 = us.registerUser("Dor");
    User* u2 = us.registerUser("Lev");
    User* u3 = us.registerUser("Ligal");
    User* u4 = us.registerUser("Super Eitan", true);
    User* u5 = us.registerUser("Bad Guy");
    
    u1->post("Hello world!");
    u2->post("I'm having a great time here :)", new Audio());
    u3->post("This is awesome!", new Photo());
    
    u5->addFriend(u1);      // bad guy is now friends with Dor
    u5->addFriend(u2);      // bad guy is now friends with Lev
    
    cout << "Trying to add bad guy as friend of Dor again:\n";
    try {
        u1->addFriend(u5);      // Dor is already friends with bad guy - should throw exception
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    
    cout << "Trying to remove Ligal from Bad guy's friends - should fail\n";
    try {
        u5->removeFriend(u3);   // bad guy is not friends with Ligal - should throw exception
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    std::cout << "\n-----Bad guy's Feed:\n";
    u5->viewFriendsPosts();     // bad guy should see only Dor, Lev s' posts
    
    u4->sendMessage(u5, new Message("Eitan: hello bad guy! I'm a business user!"));
    
    std::cout << "\n-----Bad guy's Inbox:\n";
    u5->viewReceivedMessages();
    
    
    try {                       // check sending message to non-friend
        u3->sendMessage(u5, new Message("Ligal: Hey, bad guy! I'm not your friend!"));
    } catch (const std::exception& e) {
        std::cout << "error: " << e.what() << std::endl;
    }

    std::cout << "\n-----Bad guy's Inbox:\n";
    u5->viewReceivedMessages();
    
    u3->addFriend(u5);          // Ligal is now friends with bad guy
    u3->sendMessage(u5, new Message("Ligal: Hey, bad guy! I'm your friend now!"));

    std::cout << "\n-----Bad guy's Inbox:\n";
    u5->viewReceivedMessages();

    us.showAllUsers();

    cout << "trying to remove user: \n";
    try {                       // check removing user
    us.removeUser(u1);
    } catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    // handle the exception appropriately
    }

    us.showAllUsers();

    cout << "trying to remove user again: \n";
    try {
        us.removeUser(u1); // should throw exception
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    cout << "trying to register user with same name: \n";
    User *u6 = us.registerUser("Dor");

    std::cout << "\n-----Bad guy's Inbox:\n";
    u5->viewReceivedMessages();

    us.showAllUsers();

    return 0;
}