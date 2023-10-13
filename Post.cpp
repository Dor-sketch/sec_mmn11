#include "Post.hpp"

Post::Post(const std::string& text) {
  this->text = text;
  this->media = nullptr;
}

// post must include text, and optionally one media of type photo, audio, or
// video
Post::Post(const std::string& text, std::shared_ptr<Media> media) {
  if (text == "") {
    throw std::invalid_argument("Post error: Text cannot be empty");
  }
  this->text = text;
  if (media == nullptr) {
    this->media = nullptr;
  } else if (media->getType() == "audio" || media->getType() == "video" ||
             media->getType() == "photo") {
    this->media = media;
  } else {
    throw std::invalid_argument("Media error: Invalid media type");
  }
}

std::shared_ptr<Media> Post::getMedia() const { return this->media; }

const std::string Post::getText() const { return text; }
