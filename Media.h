/*
* Media.h
*/

#ifndef MEDIA_H_
#define MEDIA_H_

#include <string>

using namespace std;

// abstract class
class Media {
public:
    virtual void display() const;
    virtual string getType() const; // to identify the type of media during runtime
};

// photo, audio, video inherit from Media
class Photo : public Media {
public:
    void display() const override;
    string getType() const override;
};

class Audio : public Media {
public:
    void display() const override;
    string getType() const override;
};

class Video : public Media {
public:
    void display() const override;
    string getType() const override;
};

#endif /* MEDIA_H_ */