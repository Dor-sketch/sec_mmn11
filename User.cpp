/*
* User.cpp
*/

#include "User.h"
#include "USocial.h" // include USocial.h header file
#include <iostream>

using namespace std;

User::User() {
    this->us = NULL;
    throw runtime_error("User constructor should not be called without a USocial pointer");
}

User::User(USocial* us) {
    this->us = us;
}

// destructor was added to free the memory allocated for the posts and messages
User::~User() {
    for (list<Post*>::iterator it = this->posts.begin(); it != this->posts.end(); ++it) {
        delete *it;
    }
    for (list<Message*>::iterator it = this->receivedMsgs.begin(); it != this->receivedMsgs.end(); ++it) {
        delete *it;
    }
}

unsigned long User::getId() const {
    return this->id;
}

string User::getName() const{
    return this->name;
}

void User::addFriend(User* u) {
    // check if the user is already a friend
    // if one user is a friend of the other, the other is also a friend of the one
    for (list<unsigned long>::iterator it = this->friends.begin(); it != this->friends.end(); ++it) {
        if (*it == u->getId()) {
            throw runtime_error("Adding friend failed: " + 
                u->getName() + " is already a friend of " + this->getName());
        }
    }
    this->friends.push_back(u->getId());
    u->friends.push_back(this->getId());
}

void User::removeFriend(User* u) {
    // check if the user is indeed a friend before removing him from the friends list
    bool found = false;
    for (list<unsigned long>::iterator it = this->friends.begin(); it != this->friends.end(); ++it) {
        if (*it == u->getId()) {
            found = true;
            break;
        }
    }
    if (!found) {
        throw runtime_error("Removing friend failed: " + 
            u->getName() + " is not a friend of " + this->getName());
    }
    this->friends.remove(u->getId());
    u->friends.remove(this->getId());
}

// post without media
void User::post(string text) {
    this->posts.push_back(new Post(text));
}

// post with media
void User::post(string text, Media* media) {
    this->posts.push_back(new Post(text, media));
}

// each user has a list of posts, this function returns the list
list<Post*> User::getPosts() const{
    return this->posts;
}

// the function loops over the friends list, for each friend it loops again and prints thie posts
void User::viewFriendsPosts() const {
    for (list<unsigned long>::const_iterator it = this->friends.begin(); it != this->friends.end(); ++it) {
        User* u = this->us->getUserById(*it);
        list<Post*> posts = u->getPosts();
        for (list<Post*>::const_iterator it2 = posts.begin(); it2 != posts.end(); ++it2)
        {
            cout << u->getName() << ": " << (*it2)->getText() << endl;
            if ((*it2)->getMedia() != NULL)     // check if the post has media
                (*it2)->getMedia()->display();  // if it does, display it
        }
    }
}

void User::receiveMessage(Message* m) {
    this->receivedMsgs.push_back(m);
}

// messeger must be a friend of the user he is sending the message to
// or a business user (which can send messages to any user)
void User::sendMessage(User* u, Message* m) {
    if(m->getText().empty())
        throw runtime_error("Sending failed. Message cannot be empty.");
    if (this->friends.empty())
        throw runtime_error("Sending failed. " 
            + this->getName() + " has no friends to send messages to.");
    for (list<unsigned long>::const_iterator it = this->friends.begin(); it != this->friends.end(); ++it) {
        if(this->us->getUserById(*it) == this->us->getUserById(u->getId())){
            u->receiveMessage(m);
            return;
        }
    }
    throw runtime_error(u->getName() + "is not a friend of "
        + this->getName() + "\nRegular user can only message his friens.");
}

// business user can send messages to any existing user
void BusinessUser::sendMessage(User* u, Message* m)  {
    if (this->us->getUserById(u->getId()) == NULL)
        throw runtime_error("Sending failed. Recipient " + u->getName() + " does not exist.");
    u->receiveMessage(m);
}

// a constructor was added to initialize with the USocial pointer
BusinessUser::BusinessUser(USocial* us) : User(us) {
    this->us = us;
}

// a function to view the received messages of a user
void User::viewReceivedMessages() {
    for (list<Message*>::iterator it = this->receivedMsgs.begin(); it != this->receivedMsgs.end(); ++it) {
        if((*it)->getText().empty())
            throw runtime_error("viewing message failed: Message cannot be empty.");
        cout << (*it)->getText() << endl;
    }
}