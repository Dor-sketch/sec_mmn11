# USocial - A Basic Social Media System in C++

## Introduction

USocial is a basic social media system simulation written in C++. The system supports various functionalities, such as registering users, posting text and media, adding and removing friends, sending and receiving messages, etc. This project was originally developed as an assignment for the Open University of Israel course "Defensive System-Programming (20937)" and has now been shared as part of a portfolio for student job applications.

## Technologies Used
- C++ (with C++14 features)
- Smart pointers (`std::shared_ptr`, `std::weak_ptr`) for resource management and avoiding memory leaks
- Standard Library containers (`std::map`, `std::list`)
- Exception handling for error scenarios
- Object-oriented principles, inheritance, and polymorphism

## Features

### USocial
- Central system for managing users.
- Register users with or without business status.
- Remove users.
- Retrieve users by ID.
- Display all users (for debugging purposes).

### User
- Post text or media.
- Add or remove friends.
- View friend's posts.
- Send and receive messages.
- Business users have an added ability to send messages to multiple users at once.

### Media
- Abstract class that serves as a base for various media types.
- Supports Photo, Audio, and Video as media types.
- Each media type has a method to display its content.

### Post
- Represents user posts that may contain text and/or media.

### Message
- Represents the messages exchanged between users.

## Compilation and Usage

The project is bundled with a `Makefile` that simplifies the build process. To compile and run the system, simply follow the steps below:

```bash
$ make
$ ./usocial_app
```

To clean up the build artifacts:

```bash
$ make clean
```

## Sample Execution

The provided main function demonstrates various functionalities of the USocial system, such as registering users, posting content, adding friends, sending messages, and handling errors (e.g., trying to add an already existing friend or sending a message to a non-friend). 

## Contributing

If you'd like to contribute, feel free to fork the project, make your changes, and submit a pull request. All contributions are welcome.

## License

This project is available under the MIT License. See LICENSE file for details.

## Contact

For any inquiries, suggestions, or feedback, please reach out via [email](mailto:dor.pascal@gmail.com).
