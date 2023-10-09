#include "Post.h"

Post::Post(const std::string& text) {
    this->text = text;
    this->media = nullptr;
}

// post must include text, and optionally one media of type photo, audio, or video
Post::Post(const std::string& text, Media* media) {
    if (text == "") { // if text is empty
        throw "Post error: Text cannot be empty";
    }
    this->text = text;
    if (media->getType() == "audio") {
        this->media = media;
    } else if (media->getType() == "video") {
        this->media = media;
    } else if (media->getType() == "photo") {
        this->media = media;
    } else {
        throw "Media errer: Invalid media type";
    }
}

std::string Post::getText() const{
    return this->text;
}

Media* Post::getMedia() const{
    return this->media;
}



