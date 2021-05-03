# C++ topics 
This repo contains some of my advanced learning concepts in c++. You can find each of them on its related folder as a project, so as to build them separetely. 

## Topic list
* Templates
* Copies
* Overloading operators
* Timing
* std::async *C++17*

## Build a test
Go to the example folder and do the following
```
mkdir build
cd build/
cmake ..
make
./<name_of_the_program>
```
## Debug or Release
* If want to compile in debugging mode use  *cmake -DCMAKE_BUILD_TYPE=Debug ..* instead of only *cmake ..*
* If want to compile in release mode use  *cmake -DCMAKE_BUILD_TYPE=Release ..* instead of only *cmake ..*
