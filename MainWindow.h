#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "USocialTester.hpp"
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QInputDialog>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0) : QWidget(parent) {
    QPushButton *button = new QPushButton("Run Tests", this);
    connect(button, &QPushButton::clicked, this, &MainWindow::runTests);

    QPushButton *updateFeedButton = new QPushButton("Update Feed", this);
    connect(updateFeedButton, &QPushButton::clicked, this, [this]() {
      bool ok;
      QString text = QInputDialog::getText(
          this, tr("Update Feed"), tr("Enter username:"), QLineEdit::Normal,
          "", &ok);
      if (ok && !text.isEmpty()) {
        std::shared_ptr<User> user = tester.getUserByName(text.toStdString());
        if (user == nullptr) {
          QMessageBox::critical(this, "Error", "User not found.");
        } else {
          updateFeed(user);
        }
      }
    });

    QPushButton *addFriendButton = new QPushButton("Add Friend", this);
    connect(addFriendButton, &QPushButton::clicked, this, [this]() {
      bool ok;
      QString text = QInputDialog::getText(
          this, tr("Add Friend"), tr("Enter username:"), QLineEdit::Normal,
          "", &ok);
      if (ok && !text.isEmpty()) {
        std::shared_ptr<User> user = tester.getUserByName(text.toStdString());
        if (user == nullptr) {
          QMessageBox::critical(this, "Error", "User not found.");
        } else {
          bool ok;
          QString text = QInputDialog::getText(
              this, tr("Add Friend"), tr("Enter friend's username:"),
              QLineEdit::Normal, "", &ok);
          if (ok && !text.isEmpty()) {
            std::shared_ptr<User> friendUser =
                tester.getUserByName(text.toStdString());
            if (friendUser == nullptr) {
              QMessageBox::critical(this, "Error", "User not found.");
            } else {
              user->addFriend(friendUser);
            }
          }
        }
      }
    });

    QPushButton *removeFriendButton = new QPushButton("Remove Friend", this);
    connect(removeFriendButton, &QPushButton::clicked, this, [this]() {
      bool ok;
      QString text = QInputDialog::getText(
          this, tr("Remove Friend"), tr("Enter username:"), QLineEdit::Normal,
          "", &ok);
      if (ok && !text.isEmpty()) {
        std::shared_ptr<User> user = tester.getUserByName(text.toStdString());
        if (user == nullptr) {
          QMessageBox::critical(this, "Error", "User not found.");
        } else {
          bool ok;
          QString text = QInputDialog::getText(
              this, tr("Remove Friend"), tr("Enter friend's username:"),
              QLineEdit::Normal, "", &ok);
          if (ok && !text.isEmpty()) {
            std::shared_ptr<User> friendUser =
                tester.getUserByName(text.toStdString());
            if (friendUser == nullptr) {
              QMessageBox::critical(this, "Error", "User not found.");
            } else {
              user->removeFriend(friendUser);
            }
          }
        }
      }
    });

    feedWidget = new QListWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(button);
    layout->addWidget(feedWidget);
    layout->addWidget(updateFeedButton);
    layout->addWidget(addFriendButton);
    layout->addWidget(removeFriendButton);
    
    setLayout(layout);
  }

public slots:
  void runTests() {
    try {
      tester.runTests();
      QMessageBox::information(this, "Success", "Tests ran successfully.");

      // Get all users and update the feed for each one
      std::vector<std::shared_ptr<User>> users = tester.getAllUsers();
      for (const auto &user : users) {
        updateFeed(user);
      }
    } catch (const std::exception &e) {
      QMessageBox::critical(this, "Error", e.what());
    }
  }

  void updateFeed(std::shared_ptr<User> user) {
    feedWidget->clear();
    std::list<std::shared_ptr<Post>> posts = user->getPosts();
    for (const auto &post : posts) {
      feedWidget->addItem(QString::fromStdString(post->getText()));
    }
  }

private:
  QListWidget *feedWidget;
    USocialTester tester;
};

#endif // MAINWINDOW_H