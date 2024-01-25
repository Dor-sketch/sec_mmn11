
#include "USocial.hpp"
#include "User.hpp"
#include "MainWindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QPushButton>


int main(int argc, char **argv) {
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}