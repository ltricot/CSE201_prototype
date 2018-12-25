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

## Libraries

We use a number of header libraries in our code:
- ``Rapidxml`` for XML parsing
- ``Eigen`` for linear algebra
- ``Catch`` as a testing framework
