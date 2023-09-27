/*
* User.h
*/

#ifndef USER_H_
#define USER_H_

#include <list>
#include <string>
class USocial; // forward declaration - used to avoid circular dependency
#include "Media.h"
#include "Post.h"
#include "Message.h"
using namespace std;

class User {
private:
    friend class USocial;
protected:
    USocial* us;
    unsigned long id;   // according to the UML the user is not asked to enter an id number
                        // upon registration, so  instead - a unique id is automatically assigned to him.
                        // when removing a user all the content related to him is removed,
                        // and the id assigned to him is free and can be reused to register new users.
    string name;
    list<unsigned long> friends;
    list<Post*> posts;
    list<Message*> receivedMsgs;
    User();             // private constructor - should not be called
    User(USocial* us);  // to make sure that every user has a pointer to USocial
    ~User();
public:
    unsigned long getId() const;
    string getName() const;
    void addFriend(User* u);
    void removeFriend(User* u);
    void post(string text);
    void post(string, Media*);
    list<Post*> getPosts() const;
    void viewFriendsPosts() const;
    void receiveMessage(Message* m);
    virtual void sendMessage(User* u,  Message* m);
    void viewReceivedMessages();
};

// business user inherits from user
class BusinessUser : public User {
public:
    BusinessUser(USocial* us);
    void sendMessage(User* u, Message* m) override; // business user can send messages to multiple users
};

#endif /* USER_H_ */