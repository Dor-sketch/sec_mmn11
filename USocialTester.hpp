#pragma once

#include "USocial.hpp"
#include "User.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <map>
#include <memory>

constexpr const char *USER_DOR = "Dor";
constexpr const char *USER_LEV = "Lev";
constexpr const char *USER_LIGAL = "Ligal";
constexpr const char *USER_SUPER_EITAN = "Super Eitan";
constexpr const char *USER_BAD_GUY = "Bad Guy";

class USocialTester {

public:
  USocialTester();
  void runTests();
  std::shared_ptr<User> getUserByName(const std::string &name);
  std::vector<std::shared_ptr<User>> getAllUsers();
  static void initializeLogger() {
    if (!logger_) {
      logger_ = spdlog::stdout_color_mt("USocialTester");
    }
  }

private:
  static std::shared_ptr<spdlog::logger> logger_;
  std::shared_ptr<USocial> us_;
  std::map<std::string, unsigned long>
      userIds_; // to map usernames to their ids

  void testRegisterUsers();
  void registerUserAndStoreId(const std::string &name);
  void registerUserAndStoreId(const std::string &name, bool isBusiness);
  void testPosts();
  void testFriendAddition();
  void testFriendRemoval();
  void testFeeds();
  void testMessages();
  void testUserRemoval();
};
