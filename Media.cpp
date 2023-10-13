#include "Media.hpp"

#include <iostream>

using namespace std;

void Media::display() const { cout << "Media::display()" << endl; }

void Photo::display() const {
  cout << "viewing photo of a dead cat: ___^(x.x)^" << endl;
}

void Audio::display() const {
  cout << "playing audio: La La La La..."
       << "I don't know how to use me-di-a-la la..." << endl;
}

void Video::display() const {
  cout << "playing video:\nIt is a period of civil war.\n"
       << "Rebel spaceships, struking\n"
       << "from a hidden base..." << endl;
}

string Media::getType() const { return "media"; }

string Photo::getType() const { return "photo"; }

string Audio::getType() const { return "audio"; }

string Video::getType() const { return "video"; }