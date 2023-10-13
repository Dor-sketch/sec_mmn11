#include "User.hpp"

#include <iostream>

#include "USocial.hpp"

User::User() {
  throw std::runtime_error(
      "User constructor should not be called without a USocial pointer");
}

User::User(std::shared_ptr<USocial> us) { this->us = us; }

User::~User() {
  for (std::list<std::shared_ptr<Post>>::iterator it = this->posts.begin();
       it != this->posts.end(); ++it) {
    // it will be deleted by the shared_ptr in the list
  }
  for (std::list<std::shared_ptr<Message>>::iterator it =
           this->receivedMsgs.begin();
       it != this->receivedMsgs.end(); ++it) {
    // same here
  }
}

unsigned long User::getId() const { return this->id; }

std::string User::getName() const { return this->name; }

void User::addFriend(std::shared_ptr<User> u) {
  // check if the user is already a friend
  // if one user is a friend of the other, the other is also a friend of the one
  for (std::list<unsigned long>::iterator it = this->friends.begin();
       it != this->friends.end(); ++it) {
    if (*it == u->getId()) {
      throw std::runtime_error("Adding friend failed: " + u->getName() +
                               " is already a friend of " + this->getName());
    }
  }
  this->friends.push_back(u->getId());
  u->friends.push_back(this->getId());
}

void User::removeFriend(std::shared_ptr<User> u) {
  // check if the user is indeed a friend before removing him from the friends
  // list
  bool found = false;
  for (std::list<unsigned long>::iterator it = this->friends.begin();
       it != this->friends.end(); ++it) {
    if (*it == u->getId()) {
      found = true;
      break;
    }
  }
  if (!found) {
    throw std::runtime_error("Removing friend failed: " + u->getName() +
                             " is not a friend of " + this->getName());
  }
  this->friends.remove(u->getId());
  u->friends.remove(this->getId());
}

// post without media
void User::post(const std::string &text) {
  this->posts.push_back(std::make_shared<Post>(text));
}

// post with media
void User::post(const std::string &text, std::shared_ptr<Media> media) {
  this->posts.push_back(std::make_shared<Post>(text, media));
}

// each user has a list of posts, this function returns the list
std::list<std::shared_ptr<Post>> User::getPosts() const { return this->posts; }

// the function loops over the friends list, for each friend it loops again and
// prints thie posts
void User::viewFriendsPosts() const {
  std::shared_ptr<USocial> usocial = us.lock();  // Lock the weak_ptr
  if (!usocial) {  // Check if the resulting shared_ptr is valid
    throw std::runtime_error(
        "Associated USocial object is no longer available.");
  }

  for (std::list<unsigned long>::const_iterator it = this->friends.begin();
       it != this->friends.end(); ++it) {
    std::shared_ptr<User> u =
        usocial->getUserById(*it);  // Use the locked shared_ptr
    std::list<std::shared_ptr<Post>> posts = u->getPosts();
    for (std::list<std::shared_ptr<Post>>::const_iterator it2 = posts.begin();
         it2 != posts.end(); ++it2) {
      std::cout << u->getName() << ": " << (*it2)->getText() << std::endl;
      if ((*it2)->getMedia()) (*it2)->getMedia()->display();
    }
  }
}

void User::receiveMessage(std::shared_ptr<Message> m) {
  this->receivedMsgs.push_back(m);
}

// messeger must be a friend of the user he is sending the message to
// or a business user (which can send messages to any user)
void User::sendMessage(std::shared_ptr<User> u, std::shared_ptr<Message> m) {
  std::shared_ptr<USocial> usocial = us.lock();  // Lock the weak_ptr
  if (!usocial) {  // Check if the resulting shared_ptr is valid
    throw std::runtime_error(
        "Associated USocial object is no longer available.");
  }

  if (m->getText().empty())
    throw std::runtime_error("Sending failed. Message cannot be empty.");
  if (this->friends.empty())
    throw std::runtime_error("Sending failed. " + this->getName() +
                             " has no friends to send messages to.");

  for (std::list<unsigned long>::const_iterator it = this->friends.begin();
       it != this->friends.end(); ++it) {
    if (usocial->getUserById(*it) ==
        usocial->getUserById(u->getId())) {  // Use the locked shared_ptr
      u->receiveMessage(m);
      return;
    }
  }
  throw std::runtime_error(u->getName() + " is not a friend of " +
                           this->getName() +
                           ". Regular user can only message his friends.");
}

// business user can send messages to any existing user
void BusinessUser::sendMessage(std::shared_ptr<User> u,
                               std::shared_ptr<Message> m) {
  std::shared_ptr<USocial> usocial = us.lock();  // Lock the weak_ptr
  if (!usocial) {  // Check if the resulting shared_ptr is valid
    throw std::runtime_error(
        "Associated USocial object is no longer available.");
  }

  if (usocial->getUserById(u->getId()) == NULL) {  // Use the locked shared_ptr
    throw std::runtime_error("Sending failed. Recipient " + u->getName() +
                             " does not exist.");
  }
  u->receiveMessage(m);
}

// a constructor was added to initialize with the USocial pointer
BusinessUser::BusinessUser(std::shared_ptr<USocial> us) : User(us) {
  this->us = us;
}

// a function to view the received messages of a user
void User::viewReceivedMessages() {
  try {
    for (std::list<std::shared_ptr<Message>>::iterator it =
             this->receivedMsgs.begin();
         it != this->receivedMsgs.end(); ++it) {
      if ((*it)->getText().empty())
        throw std::runtime_error(
            "viewing message failed: Message cannot be empty.");
      std::cout << (*it)->getText() << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
