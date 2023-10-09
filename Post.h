#ifndef POST_H_
#define POST_H_

#include <string>
#include "Media.h"

class Post
{
private:
    std::string text;
    Media *media;

public:
    explicit Post(const std::string &text);
    Post(const std::string &text, Media *media);
    
    std::string getText() const;
    Media *getMedia() const;
};

#endif /* POST_H_ */
