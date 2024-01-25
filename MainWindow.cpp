#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  QPushButton *button = new QPushButton("Run Tests", this);
  connect(button, &QPushButton::clicked, this, &MainWindow::runTests);

  QPushButton *updateFeedButton = new QPushButton("Update Feed", this);
  connect(updateFeedButton, &QPushButton::clicked, this, [this]() {
    bool ok;
    QString text =
        QInputDialog::getText(this, tr("Update Feed"), tr("Enter username:"),
                              QLineEdit::Normal, "", &ok);
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
    if (selectedUser == nullptr) {
      QMessageBox::critical(this, "Error", "Please choose a user first.");
      return;
    }

    bool ok;
    QString text = QInputDialog::getText(this, tr("Add Friend"),
                                         tr("Enter friend's username:"),
                                         QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
      std::shared_ptr<User> friendUser =
          tester.getUserByName(text.toStdString());
      if (friendUser == nullptr) {
        QMessageBox::critical(this, "Error", "User not found.");
      } else {
        selectedUser->addFriend(friendUser);
      }
    }
  });

  QPushButton *removeFriendButton = new QPushButton("Remove Friend", this);
  connect(removeFriendButton, &QPushButton::clicked, this, [this]() {
    bool ok;
    QString text =
        QInputDialog::getText(this, tr("Remove Friend"), tr("Enter username:"),
                              QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
      std::shared_ptr<User> user = tester.getUserByName(text.toStdString());
      if (user == nullptr) {
        QMessageBox::critical(this, "Error", "User not found.");
      } else {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Remove Friend"),
                                             tr("Enter friend's username:"),
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

  QPushButton *chooseUserButton = new QPushButton("Choose User", this);
  connect(chooseUserButton, &QPushButton::clicked, this,
          &MainWindow::chooseUser);
  layout->addWidget(chooseUserButton);

  QPushButton *openNewWindowButton = new QPushButton("Open New Window", this);
  // open new window to see 2 users feed side by side
    connect(openNewWindowButton, &QPushButton::clicked, this, [this]() {
        if (selectedUser == nullptr) {
        QMessageBox::critical(this, "Error", "Please choose a user first.");
        return;
        }

        MainWindow *newWindow = new MainWindow();
        newWindow->selectedUser = selectedUser;
        newWindow->updateFeed(selectedUser);
        newWindow->show();
    });
    layout->addWidget(openNewWindowButton);

    

  QPushButton *openNewWindowButton2 = new QPushButton("Exit", this);
    connect(openNewWindowButton2, &QPushButton::clicked, this, [this]() {
        this->close();
    });
    layout->addWidget(openNewWindowButton2);

    this->setWindowTitle("Current User: None");

    // Get all users and update the feed for each one
    std::vector<std::shared_ptr<User>> users = tester.getAllUsers();
    for (const auto &user : users) {
        updateFeed(user);
    }



}

void MainWindow::runTests() {
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

void MainWindow::updateFeed(std::shared_ptr<User> user) {
  feedWidget->clear();
  std::list<std::shared_ptr<Post>> posts = user->getPosts();
  for (const auto &post : posts) {
    feedWidget->addItem(QString::fromStdString(post->getText()));
  }
}

void MainWindow::chooseUser() {
  QStringList users;
  for (const auto &user : tester.getAllUsers()) {
    users << QString::fromStdString(user->getName());
  }

  bool ok;
  QString selected = QInputDialog::getItem(
      this, tr("Choose User"), tr("Select a user:"), users, 0, false, &ok);
  if (ok && !selected.isEmpty()) {
    selectedUser = tester.getUserByName(selected.toStdString());
    if (selectedUser == nullptr) {
      QMessageBox::critical(this, "Error", "User not found.");
    } else {
      updateFeed(selectedUser);
      this->setWindowTitle("Current User: " + selected);
    }
  }
}
