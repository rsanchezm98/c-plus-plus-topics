# Timing
In this example, there is implemented a timing smart way *timer::Timer* to measure duration of functions in C++. 

## Visual timing 
There is also implemented a *timer::InstrumentationTimer* which writes the timing and threading information in a .json to postprocess it with *chrome://tracing/*. You can create different sessions, which means different .json files. The .json will be created inside /build.

![Visual Timing](img/visual.png)

