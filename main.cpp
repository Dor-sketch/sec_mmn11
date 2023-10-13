#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "USocial.hpp"
#include "User.hpp"

constexpr const char *USER_DOR = "Dor";
constexpr const char *USER_LEV = "Lev";
constexpr const char *USER_LIGAL = "Ligal";
constexpr const char *USER_SUPER_EITAN = "Super Eitan";
constexpr const char *USER_BAD_GUY = "Bad Guy";

class USocialTester
{
private:
  std::shared_ptr<spdlog::logger> logger_;
  std::shared_ptr<USocial> us_;
  std::map<std::string, unsigned long> userIds_; // to map usernames to their ids

public:
  USocialTester()
  {
    // Set up logger
    spdlog::set_pattern("[%H:%M:%S %z] [%^%L%$] %v");
    logger_ = spdlog::stdout_color_mt("USocialTester");

    // Initialize USocial
    us_ = std::make_shared<USocial>();
  }

  void runTests()
  {
    testRegisterUsers();
    testPosts();
    testFriendAddition();
    testFriendRemoval();
    testFeeds();
    testMessages();
    testUserRemoval();
  }

private:
  void testRegisterUsers()
  {
    registerUserAndStoreId(USER_DOR);
    registerUserAndStoreId(USER_LEV);
    registerUserAndStoreId(USER_LIGAL);
    registerUserAndStoreId(USER_SUPER_EITAN, true);
    registerUserAndStoreId(USER_BAD_GUY);

    us_->showAllUsers();
  }

  void registerUserAndStoreId(const std::string &name, bool isBusiness = false)
  {
    auto user = isBusiness ? us_->registerUser(name, true) : us_->registerUser(name);
    userIds_[name] = user->getId();
  }

  void testPosts()
  {
    getUserByName(USER_DOR)->post("Hello world!");
    getUserByName(USER_LEV)->post("I'm having a great time here :)", std::make_shared<Audio>());
    getUserByName(USER_LIGAL)->post("This is awesome!", std::make_shared<Photo>());
  }

  void testFriendAddition()
  {
    auto u1 = getUserByName(USER_DOR);
    auto u5 = getUserByName(USER_BAD_GUY);

    u5->addFriend(u1);
    u5->addFriend(getUserByName(USER_LEV));

    logger_->info( "Trying to add Bad Guy as friend of Dor again:\n");
    try
    {
      u1->addFriend(u5);
    }
    catch (const std::exception &e)
    {
      logger_->error("Friend addition error: {}", e.what());
    }
  }

  void testFriendRemoval()
  {
    auto u3 = getUserByName(USER_LIGAL);
    auto u5 = getUserByName(USER_BAD_GUY);

    logger_->info( "Trying to remove Ligal from Bad Guy's friends (should fail):\n");
    try
    {
      u5->removeFriend(u3);
    }
    catch (const std::exception &e)
    {
      logger_->error("Friend removal error: {}", e.what());
    }
  }

  void testFeeds()
  {
    auto u5 = getUserByName(USER_BAD_GUY);

    logger_->info("\n-----Bad Guy's Feed:\n");
    u5->viewFriendsPosts();
  }

  void testMessages()
  {
    auto u3 = getUserByName(USER_LIGAL);
    auto u4 = getUserByName(USER_SUPER_EITAN);
    auto u5 = getUserByName(USER_BAD_GUY);

    u4->sendMessage(u5, std::make_shared<Message>("Eitan: hello bad guy! I'm a business user!"));

    logger_->info("\n-----Bad Guy's Inbox:\n");
    u5->viewReceivedMessages();

    // Try sending message to non-friend
    try
    {
      u3->sendMessage(u5, std::make_shared<Message>("Ligal: Hey, bad guy! I'm not your friend!"));
    }
    catch (const std::exception &e)
    {
      logger_->error("Message error: {}", e.what());
    }
  }

  void testUserRemoval()
  {
    auto u1 = getUserByName(USER_DOR);

    logger_->info("Trying to remove user Dor:\n");
    try
    {
      us_->removeUser(u1);
    }
    catch (const std::exception &e)
    {
      logger_->error("User removal error: {}", e.what());
    }

    logger_->info( "Trying to remove user Dor again:\n");
    try
    {
      us_->removeUser(u1);
    }
    catch (const std::exception &e)
    {
      logger_->error("User removal error: {}", e.what());
    }

    us_->showAllUsers();
  }

  std::shared_ptr<User> getUserByName(const std::string &name)
  {
    return us_->getUserById(userIds_.at(name)); // using .at() so it throws if name not found
  }
};

int main()
{
  USocialTester tester;
  tester.runTests();
  return 0;
}
