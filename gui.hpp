#include "USocialTester.hpp"
#include <QApplication>
#include <QMessageBox>
#include <QPushButton>

class MainWindow : public QWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0) : QWidget(parent) {
    QPushButton *button = new QPushButton("Run Tests", this);
    connect(button, &QPushButton::clicked, this, &MainWindow::runTests);
  }

public slots:
  void runTests() {
    try {
      USocialTester tester;
      tester.runTests();
      QMessageBox::information(this, "Success", "Tests ran successfully.");
    } catch (const std::exception &e) {
      QMessageBox::critical(this, "Error", e.what());
    }
  }
};

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}