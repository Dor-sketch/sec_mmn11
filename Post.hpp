#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "Media.hpp"

class Post {
 private:
  std::string text;
  std::shared_ptr<Media> media;

 public:
  explicit Post(const std::string &text);
  Post(const std::string &text, std::shared_ptr<Media> media);

  const std::string getText() const;
  std::shared_ptr<Media> getMedia() const;
};
