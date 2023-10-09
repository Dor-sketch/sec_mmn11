#ifndef USER_H_
#define USER_H_

#include <list>
#include <string>
#include "Media.h"
#include "Post.h"
#include "Message.h"

// Forward declaration to avoid circular dependency
class USocial;

class User
{
private:
    friend class USocial;
    User();  // private ctor should not be called
protected:
    USocial* us;
    unsigned long id;
    std::string name;
    std::list<unsigned long> friends;
    std::list<Post*> posts;
    std::list<Message*> receivedMsgs;
public:
    explicit User(USocial *us); // Ensures every user has a pointer to USocial
    virtual ~User();

    unsigned long getId() const;
    std::string getName() const;
    std::list<Post*> getPosts() const;
    void viewFriendsPosts() const;

    void addFriend(User* u);
    void removeFriend(User* u);
    void post(const std::string &text);
    void post(const std::string &text, Media *media);
    void receiveMessage(Message* m);
    virtual void sendMessage(User* u,  Message* m);
    void viewReceivedMessages();
};

class BusinessUser : public User {
public:
    explicit BusinessUser(USocial *us);
    void sendMessage(User *u, Message *m) override;  // business user can send messages to multiple users
};

#endif /* USER_H_ */