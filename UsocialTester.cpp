

#include "USocialTester.hpp"
std::shared_ptr<spdlog::logger> USocialTester::logger_ = nullptr;
USocialTester::USocialTester() {
  // Set up logger
  initializeLogger();
  // Initialize USocial
  us_ = std::make_shared<USocial>();
}

void USocialTester::runTests() {
  testRegisterUsers();
  testPosts();
  testFriendAddition();
  testFriendRemoval();
  testFeeds();
  testMessages();
  testUserRemoval();
}

void USocialTester::testRegisterUsers() {
  registerUserAndStoreId(USER_DOR);
  registerUserAndStoreId(USER_LEV);
  registerUserAndStoreId(USER_LIGAL);
  registerUserAndStoreId(USER_SUPER_EITAN, true);
  registerUserAndStoreId(USER_BAD_GUY);

  us_->showAllUsers();
}

std::vector<std::shared_ptr<User>> USocialTester::getAllUsers() {
  return us_->getAllUsers();
}

void USocialTester::registerUserAndStoreId(const std::string &name) {
  registerUserAndStoreId(name, false);
}

void USocialTester::registerUserAndStoreId(const std::string &name,
                                           bool isBusiness) {
  auto user =
      isBusiness ? us_->registerUser(name, true) : us_->registerUser(name);
  userIds_[name] = user->getId();
}

void USocialTester::testPosts() {
  getUserByName(USER_DOR)->post("Hello world!");
  getUserByName(USER_LEV)->post("I'm having a great time here :)",
                                std::make_shared<Audio>());
  getUserByName(USER_LIGAL)
      ->post("This is awesome!", std::make_shared<Photo>());
}

void USocialTester::testFriendAddition() {
  auto u1 = getUserByName(USER_DOR);
  auto u5 = getUserByName(USER_BAD_GUY);

  u5->addFriend(u1);
  u5->addFriend(getUserByName(USER_LEV));

  logger_->info("Trying to add Bad Guy as friend of Dor again:\n");
  try {
    u1->addFriend(u5);
  } catch (const std::exception &e) {
    logger_->error("Friend addition error: {}", e.what());
  }
}

void USocialTester::testFriendRemoval() {
  auto u3 = getUserByName(USER_LIGAL);
  auto u5 = getUserByName(USER_BAD_GUY);

  logger_->info(
      "Trying to remove Ligal from Bad Guy's friends (should fail):\n");
  try {
    u5->removeFriend(u3);
  } catch (const std::exception &e) {
    logger_->error("Friend removal error: {}", e.what());
  }
}

void USocialTester::testFeeds() {
  auto u5 = getUserByName(USER_BAD_GUY);

  logger_->info("\n-----Bad Guy's Feed:\n");
  u5->viewFriendsPosts();
}

void USocialTester::testMessages() {
  auto u3 = getUserByName(USER_LIGAL);
  auto u4 = getUserByName(USER_SUPER_EITAN);
  auto u5 = getUserByName(USER_BAD_GUY);

  u4->sendMessage(u5, std::make_shared<Message>(
                          "Eitan: hello bad guy! I'm a business user!"));

  logger_->info("\n-----Bad Guy's Inbox:\n");
  u5->viewReceivedMessages();

  // Try sending message to non-friend
  try {
    u3->sendMessage(u5, std::make_shared<Message>(
                            "Ligal: Hey, bad guy! I'm not your friend!"));
  } catch (const std::exception &e) {
    logger_->error("Message error: {}", e.what());
  }
}

void USocialTester::testUserRemoval() {
  auto u1 = getUserByName(USER_DOR);

  logger_->info("Trying to remove user Dor:\n");
  try {
    us_->removeUser(u1);
  } catch (const std::exception &e) {
    logger_->error("User removal error: {}", e.what());
  }

  logger_->info("Trying to remove user Dor again:\n");
  try {
    us_->removeUser(u1);
  } catch (const std::exception &e) {
    logger_->error("User removal error: {}", e.what());
  }

  us_->showAllUsers();
}

std::shared_ptr<User> USocialTester::getUserByName(const std::string &name) {
  try {
    return us_->getUserById(userIds_.at(name));
  } catch (const std::exception &e) {
    logger_->error("User {} not found", name);
    logger_->error("{}", e.what());
    logger_->error("Existing users:");
    for (const auto &user : us_->getAllUsers()) {
      logger_->error("{}", user->getName());
    }
    logger_->error("Returning nullptr");
    return nullptr;
  }
  return us_->getUserById(
      userIds_.at(name)); // using .at() so it throws if name not found
}
