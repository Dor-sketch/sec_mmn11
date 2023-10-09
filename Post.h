#ifndef POST_H_
#define POST_H_

#include <string>
#include <memory>
#include <stdexcept>

#include "Media.h"


class Post
{
private:
    std::string text;
    std::shared_ptr<Media> media;

public:
    explicit Post(const std::string &text);
    Post(const std::string &text, std::shared_ptr<Media> media);

    const std::string getText() const;
    std::shared_ptr<Media> getMedia() const;
};

#endif /* POST_H_ */
