# CPP Nano Degree: Capstone Snake Game 

![maintenance-status](https://img.shields.io/badge/Maintenance-passively--maintained-yellowgreen.svg)
![maintainer](https://img.shields.io/badge/Maintainer-Salman-blue)

## New Features

- Esc for exiting the game
- P for pausing
- Scores saved to txt file
- Scores show at the end of the run
- Multithreading input 
- Different foods

## Requirements

### Loops, Functions, I/O - meet at least 2 criteria

- The project demonstrates an understanding of C++ functions and control structures.
A variety of control structures are added to the project.

The project code is clearly organized into functions.

- The project reads data from a file and process the data, or the program writes data to a file.

The project reads data from an external file or writes data to a file as part of the necessary operation of the program.

> Scores saved to a text file

- The project accepts user input and processes the input.

In addition to controlling the snake, the game can also receive new types of input from the player.

> p to pause the game
> esc to exit the game

- The project uses data structures and immutable variables.

The project uses arrays or vectors and uses constant variables.

### Object Oriented Programming - meet at least 3 criteria

- One or more classes are added to the project with appropriate access specifiers for class members.

> Food class in food.h

- Classes are organized with attributes to hold data and methods to perform tasks.

All class data members are explicitly specified as public, protected, or private.
Member data that is subject to an invariant is hidden from the user and accessed via member methods.

> Sub food classes like frenzy have protected variables in food.h

- Class constructors utilize member initialization lists.

All class members that are set to argument values are initialized through member initialization lists.

- Classes abstract implementation details from their interfaces.

All class member functions document their effects, either through function names, comments, or formal documentation.

Member functions do not change the program state in undocumented ways.

> Sub food classes use the virtual function from food

- Overloaded functions allow the same function to operate on different parameters.

One function is overloaded with different signatures for the same function name.

> Sub food classes overloads the color for virtual class 

- Classes follow an appropriate inheritance hierarchy with virtual and override functions.

Inheritance hierarchies are logical. One member function in an inherited class overrides a virtual base class member function.

> food.h

- Templates generalize functions or classes in the project.

One function or class is declared with a template that allows it to accept a generic parameter.

> food.h

### Memory Management - meet at least 3 criteria

- The project makes use of references in function declarations.

At least two variables are defined as references, or two functions use pass-by-reference in the project code.

> food.cpp use pass by reference

- The project uses destructors appropriately.

At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.

> There is a unmanaged dynamic memory for score that is destroyed with the game destructor in game.cpp

- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.

The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.

> In game.cpp -> Game::PlaceFood(), usage of smart pointers for managing food object is obeying RAII

- The project follows the Rule of 5.

For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.

- The project uses move semantics to move data instead of copying it, where possible.

The project relies on the move semantics, instead of copying the object.

- The project uses smart pointers instead of raw pointers.

The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr.

> game.cpp uses smart unique pointers for food sub classes

### Concurrency - meet at least 2 criteria

- The project uses multithreading.

The project uses multiple threads or async tasks in the execution.

> game.cpp uses input control from controller.cpp in a separate thread

- A promise and future is used in the project.

A promise and future is used to pass data from a worker thread to a parent thread in the project code.

> game.cpp uses future to check the game state in the end

- A mutex or lock is used in the project.

A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.

- A condition variable is used in the project.

A std::condition_variable is used in the project code to synchronize thread execution.

# Basic Build Instructions

1. Clone this repo.
2. Build repo `./build.sh`
4. Run it: `./build/SnakeGame`

## Dependencies
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)