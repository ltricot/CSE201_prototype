# Tinder for researchers (god knows they need it)

## Source code structure

Inside the ``src`` folder you will find the 4 main divisions of our project. The data gathering team works with ``fetching``, the data engineering, algorithms and GUI teams work respectively with ``database``, ``engine`` and ``GUI``. The ``tests`` folder contains tests for each division above.

## Building

We use ``cmake`` to build our project. As of now we wish to build 4 executables:
- The crawler which will upload data to our database
- The engine responsible for the training of the recommender system
- The recommender capable of answering recommendation requests
- The GUI

Build commands:
```
git clone https://github.com/ltricot/CSE201_prototype
cd CSE201_prototype
mkdir build
cd build
cmake ..
make
```

## Running the tests

Once the build is over, inside the ``build`` folder, run
```
cd build
ctest
```

or run the test executable itself for a more detailed output. An example:
```
cd build/tests/fetching
./testcrawler
```

## Adding an executable

``cmake`` uses ``CmakeLists.txt`` files inside each directory containing files relevant to the build process (most often source code files). Suppose you have worked on some ``work.cpp`` file which contains a ``main`` function. Suppose ``work.cpp`` includes ``oldwork.hpp``. You may append the following code to the ``CMakeLists.txt`` file in ``work.cpp``'s folder:
```
add_executable (work work.cpp oldwork.cpp)
```

to create an executable ``cmake`` will refer to as ``work``. If your work does not contain a ``main`` function, it is called a library and added to the build in the following way:
```
add_library (worklib workwithoutmain.cpp)
```

Observe we only list the ``.cpp`` files instead of the headers. If you use an external library such as ``curl``, you should manage this in the top-level ``CMakeLists.txt`` file (or the lowest level folder such that all ``.cpp`` files using the library). How cmake includes such libraries depends on its nature. You may study the ``CMakeLists.txt`` files of the project to observe how we manage external libraries. In any case, once the library is available, suppose it is store in some variable ``curl``, adding it as a dependency is as simple as:
```
target_link_libraries (work curl)
```

where ``work`` is a target (executable or even another library).

## Libraries

We use a number of header libraries in our code:
- ``Rapidxml`` for XML parsing
- ``Eigen`` for linear algebra
- ``Catch`` as a testing framework
