# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Reflection
1. I started out with the arbitrary values for Kp, Ki and Kd.
2.  choose 0.25, 0,25 and 0.25
3. The resulting drive simulation is here
4. [randomcoeefs](https://www.youtube.com/watch?v=Srgyr8iReeY)

The error values were
 
1. 42["steer",{"steering_angle":0.0254799999999999,"throttle":0.469480794755556}]
 perror -0.3599 derror -0.0594 ierror 22.9451
CTE: -0.3599 Steering Value: 0.16533
2. 42["steer",{"steering_angle":0.1653295,"throttle":0.454025712239764}]
 perror -0.459 derror -0.0991 ierror 22.4861
CTE: -0.459 Steering Value: 0.31944
3. 42["steer",{"steering_angle":0.3194395,"throttle":0.414443663143875}]
 perror -0.5997 derror -0.1407 ierror 21.8864
 
 
 As you can see, the iError was having a skewed influence on the steering angle, so I bumped the 
 Pi way down to 0.005, the sults were much better, see video below
 
 1. Now with Kp, Ki and Kd at 0.25, 0.005, and 0.25
 
 2. [KiReduced](https://www.youtube.com/watch?v=J6jkf0_xHb8)
 the error values were
 3. 42["steer",{"steering_angle":1.421892,"throttle":0.15}]
 perror -4.8137 derror 0.6241 ierror -36.8771
CTE: -4.8137 Steering Value: 1.23179
4. 42["steer",{"steering_angle":1.2317855,"throttle":0.15}]
 perror -3.9911 derror 0.8226 ierror -40.8682
CTE: -3.9911 Steering Value: 0.996466
5. 42["steer",{"steering_angle":0.996466,"throttle":0.15}]
 perror -2.6672 derror 1.3239 ierror -43.5354
 
 The car was oscillating a lot ,and derror is not having much influence, so i bumped the Kd value to 3.0
 1. Now with Kp, Ki and Kd at 0.25, 0.005, and 3.0
  
 2. [KiReducedAndKdBumpedwayup](https://www.youtube.com/watch?v=Gh3RGXowm4I)
 
 
 3. I also turned twiddle on after seeing that the car was staying on the road
 s4. o with Kp, Ki, Kd at 0,25, 0.005 and 3.0, I turned on twiddle and the output error was
 5. After about 4 laps the twiddled params were
 ...
 6. Kpd 0.02475 Kdd 0.243 Kid 0.000495
 Kp 0.275 Kd 3 Ki 0.0045
 Kp 0.275 Kd 3 Ki 0.0045
 perror -0.3263 derror -0.016 ierror 21.4915
 7. Kpd 0.022275 Kdd 0.243 Kid 0.000495
 Kp 0.275 Kd 3.243 Ki 0.0045
 Kp 0.275 Kd 3.243 Ki 0.0045
 perror 0.0339 derror -0.0591 ierror 10.1558
 8. Kpd 0.022275 Kdd 0.243 Kid 0.000495
 Kp 0.275 Kd 3.243 Ki 0.0045
 Kp 0.275 Kd 3.243 Ki 0.0045
 perror -0.1599 derror -0.0416 ierror 19.8111
 9. Kpd 0.022275 Kdd 0.2673 Kid 0.000495
Kp 0.275 Kd 2.99757 Ki 0.0049955

 
 
 So finally I used this fine precision params of
 10. Kp, Ki and Kd 0.275, 0.0049955
 
 I then turnd twiddle off and ran the simulator and the carran like a champ
 
 
 
 
 
 
 
 

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

I used the techniques in behavior cloning project and have adjusted the throttle based on steering angle and
speed

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

