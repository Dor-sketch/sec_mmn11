#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "USocialTester.hpp"
#include <QInputDialog>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
public slots:
  void runTests();
  void updateFeed(std::shared_ptr<User> user);
  void chooseUser();

private:
  QListWidget *feedWidget;
  USocialTester tester;
  std::shared_ptr<User> selectedUser;
};

#endif // MAINWINDOW_H