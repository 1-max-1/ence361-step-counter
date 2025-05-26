# Step counter
# Overview
This repository contains the software for the ENCE361 step counter project. This project involved creating a pedometer device which tracks the number of steps taken by a user.

The hardware used for this project consists of an STM32 nucleo devboard (STM32C071RBT6) attached to a second PCB known as the RCAP board (Robust Collection of Assorted Peripherals). The RCAP board contains several components including buttons, potentiometer, LEDs, joystick, buzzer, and screen. These peripherals allow the user to interact with the device.

The device has several display modes which determines what is shown on the screen. The mode can be cycled by moving the joystick to the left or right. There are three main modes as follows:
1.	The number of current steps will be shown on the screen.
2.	The goal progress will be shown on the screen, either as a ratio or percentage of the current goal.
3.	The distance travelled will be shown on the screen, in units of either yards or kilometers.

The displayed unit can be toggled by moving the joystick up or down.

The user can set the goal by long pressing the joystick button when in the goal progress display mode. The device will enter a new display state, in which the goal can be set in increments of 500 by rotating the potentiometer. The new goal can be set in the range 500-15000. The new goal can be confirmed by long-pressing the joystick again, or the operation can be cancelled with a short-press.

The device will track the user’s progress towards the goal. In addition to the screen, progress is indicated with 4 LEDs. One LED will turn on for each 25% of the goal completed. When progress is below 25%, the first LED will gradually increase in brightness until the goal reaches 25%. Once the goal has been reached, the user will be notified with the buzzer and the haptic feedback motor, which will turn on for a short duration.

The device also includes a test mode where the user can manually set the number of steps. This mode can be toggled by double-tapping switch 2. While in test mode, the joystick can be moved up or down to manually increment or decrement the number of steps taken. The rate of change will depend on how far the joystick is pushed. The step count can also be manually incremented in steps of 80 by pressing switch 1. This feature is active even when not in test mode.

# Code structure
### General overview of code structure
The code is modularized as shown in the figure below (open image in new tab or visit link for full size image).

![Image](https://github.com/user-attachments/assets/383d42eb-6b94-4c44-9bed-f2fa1b314b11)
 
Modules are one of several types:
- Hardware – these modules expose high-level functions for interacting with hardware components on the nucleo and RCAP boards. Low-level hardware details are hidden.
- Task modules – these modules represent the tasks which the scheduler executes. They expose only init() and execute()/update() functions which run the logic for the task. 
- State logic modules – these modules run the logic for each of the display states (e.g. current steps or distance travelled). They are at a lower level than the task modules.
- Other modules – these modules provide utility functions such as noise filtering, or act as data storage for user and step data.

### Entry point
At the highest level is the `main.c` file and the `app` module. This is the entry point of the program. The `app` module initializes all tasks and hardware modules and then registers the tasks with the scheduler. The scheduler module will then execute each task at the required frequency. The scheduler is a time-triggered scheduler, using `HAL_GetTick()` (systick interrupts) to keep track of time.

### State and data modules
The step data module stores user data. For example, the number of steps taken or the currently selected display units. The state machine module tracks the program display state and provides methods for switching between states.

These modules provide controlled access to global data through specific functions rather than exposing the variables directly. Although global data is sometimes at risk of causing confusing program flow, this was decided to be the best solution, as it still provides some degree of encapsulation while still being one of the simplest methods. Other methods such as passing down all data through the chain of functions would have been overkill for this project.

### Task modules
These modules each expose one function that runs the logic for a task. These task logic functions are called by the scheduler module at specific intervals. The functions are logic only; any hardware access is achieved using the hardware modules. The description of each task is as follows:
- `blinkyTask` – this task blinks the onboard LED to indicate the program and scheduler are running correctly.
- `usartPrintingTask` – this task was only used during debugging. It will print values to the serial port.
- `goalProgressIndicationTask` – this task tracks the user’s goal progress and will indicate progress using LED’s, the buzzer and haptic feedback.
- `stepTrackTask` – this task contains the step detection algorithm and will update the number of steps the user has taken.
- `displayTask` – this task decides which display function to run, as this is dependent on the program display state. The display functions are defined elsewhere in the `uiDisplay` module (see section below). `displayTask` does not interact with the screen; all graphics are handled in the `uiDisplay` module. This was done to decouple the graphics code from the current state decision making code.
- `stateLogicTask` – this task will run different logic functions depending on which display state the program is in. The display state logic functions are defined in separate modules (see section below).

### State logic modules
These modules run the logic for the program display states. They are at a lower level than the task logic modules described previously. The task logics will always run, whereas the state logics are specific to each display state and will only run when that display state is active. The state logic modules are logic only (user input, math etc.) and do not contain any graphics code, all graphics are handled in `uiDisplay`. Some state logics require variables, so each state logic function was implemented in a separate file to encapsulate and hide these variables. The state logic functions are executed by the stateLogicTask. There are several state logic modules:
- `currentSteps` – this state displays the number of steps taken.
- `goalProgress` – this state displays the progress towards the goal. This will also listen for long presses on the joystick, which will switch the program into the `goalChange` state.
- `goalChange` – this state allows the user to set the current goal with the potentiometer. The user can also exit out of this state with the joystick.
- `distanceTravelled` – this state displays the distance travelled.
- `testMode` – this function handles the logic for switching in and out of test mode, as well as incrementing the steps while in test mode.

The state logic modules use the hardware modules to interact with the hardware components.

### Hardware modules
These modules expose functions to control the hardware components on the nucleo and RCAP boards. They hide the low-level implementation so that changing the way hardware is accessed does not break any of the tasks or other modules. The hardware modules mostly use the stm32 HAL functions. Hardware modules exist for the following components:
- ADC (`adcTask`)
- Joystick (`joystick`)
- Push buttons (`buttons`)
- Potentiometer (`rotPot`)
- OLED Screen (`ssd1306`)
- Haptic feedback motor (`hapticFeedback`)
- Piezo buzzer (`buzzer`)
- RGB LED’s (`rgb`)
- IMU (`imu_lsm64ds`)


The buttons, joystick and ADC require continuous polling, so these modules also expose additional `update()` functions which are registered with the scheduler and are called periodically.

The joystick and potentiometer modules require access to the ADC data. However, both components are using the same ADC and DMA channel. Hence all ADC data must be read at once. This is why the ADC module is separate. The joystick and potentiometer modules can then read the ADC data from the ADC module.

The LED and buzzer modules use an additional PWM module to vary the duty cycle of the PWM generation. This results in changing the buzzer pitch or the LED brightness.

### Miscellaneous modules
The `noiseFiltering` module provides an implementation of a moving average filter. This module was designed to allow several filters to be defined and used simultaneously.  All filters share the same code so maintaining this module is simple. Each filter can use a different buffer size as well as using different filter coefficients if required. The filter is used to smooth the values from the IMU and potentiometer as these are noisy enough to cause problems.

The `uiDisplay` module handles graphics and UI layout. Each display state has a similar layout but different text. The module defines a display function for each display state. It handles building the strings from the step data and using the relevant hardware modules to write them to the screen. The `uiDisplay` module is separate from the `displayTask` module, which decides what function to call. This was done to decouple the decision making (dependent on state machine implementation) from the graphics code.

# Step tracking algorithm
The step detection algorithm operates on filtered acceleration data from the IMU. The raw x, y and z values from the IMU are passed through a moving average filter. These values are then used to calculate a squared magnitude. The square root is avoided due to it being an expensive operation.
Every time a step is taken, the magnitude peaks in both directions then settles down. Hence we define several conditions that must be met for the algorithm to decide that a step has been taken:
1.	The magnitude must cross below the average.
2.	The magnitude must have peaked to a certain threshold before crossing over. This avoids false detections when the average value does not change fast enough and noise causes smaller spikes that cross the average.
3.	The time since the last detection event must be above a threshold duration. This avoids false detections when noise causes rapid spikes.
4.	The variance of the signal must be above a threshold. This avoids false detections when the user is standing still, as the data is noisy and will still fluctuate even if the user is not walking.

The past values of magnitude are stored into a circular buffer and are used to calculate the variance and average. Two separate buffers with different lengths are used. It was found that the variance calculation needed a shorter buffer, as too many samples would cause the result to lag behind the data and the variance would not increase above the threshold fast enough to track the first step. This lag in variance is also why the algorithm checks when the data crosses below the average rather than above, as this point is at the end of the first step and so it gives time for the variance to build up.

The buffer length for the average calculation also had to be tuned. A buffer that was too short would cause the average to follow the data too closely and would result in large fluctuations. A buffer that was too long would cause too much lag in the average and it would not follow the data closely enough, resulting in missed or extra steps.

 
# Results & Analysis
To analyse the performance and accuracy of the step tracking algorithm, data was sent via serial comms to a python logging program on a lab computer. This tracked the current moving average, filtered IMU magnitude, current variance, points where the magnitude crossed the average, and detected steps. This was plotted in two graphs. The figure below shows these graphs for a single test of eight steps (open image in new tab or visit link for full size image).

![Image](https://github.com/user-attachments/assets/7f6dd4b0-bd42-4352-9869-2700fd32870e)

These graphs show the magnitude of the IMU data crosses the moving average many times, more than the actual number of steps. However, since the algorithm also checks against variance, time since last detected step, and peak magnitude, most of these crossings were filtered out, leaving only valid crossings to be detected as steps. As can be seen in the figure, the algorithm was able to successfully detect all eight steps without additional false detections.

Multiple tests were conducted to determine the robustness and accuracy of the algorithm. Results were positive, with a few outliers in edge case scenarios such as running and exceptionally light stepping. For all other walking tests such as single step tests and long-distance tests the device was able to accurately detect the number of steps taken with a precision of >95%. This level of accuracy was deemed to be adequate for this project.

While the step detection was found to perform sufficiently well, a few improvements could be made to improve accuracy in the previously mentioned edge case scenarios. This would mostly involve tuning the algorithm for running and light stepping as these cases result in unusual peak formations and caused the algorithm to struggle to detect all steps. For running, steps often occurred too quickly and would be filtered out by the step detection time threshold. Decreasing this would have allowed for a more accurate step count while running. However, since running was not within the scope of this project, this threshold was not changed to preserve the accuracy of walking step detection. For light stepping cases, the peaks were not high enough to meet the peak magnitude requirements. However, this was also deemed acceptable, as for this to be a problem the steps taken had to be unreasonably light. This was considered out of the scope of this project as it involved walking in a very unnatural manner.

Aside from the step detection algorithm, the rest of the software performed robustly meeting all requirements and specifications outlined for this project. There was one small user interface issue identified which occurred when using the joystick to set the current steps while in test mode. The joystick would not start incrementing steps until a certain percentage of displacement was reached. This would normally be fine, however this minimum displacement appeared to be related to the size of the current goal. For example, when the goal was set to 500 steps, the joystick would have to reach ~60% displacement before the value of the steps would begin to change. Whereas with a high goal such as 15000 steps, steps would begin to change with a joystick displacement of as little as ~5%. This is a minor issue and did not affect the main functionality of the device, only the user's experience of setting the steps in test mode. Aside from this, no other issues were found and the software performed as expected.

# Conclusions
Overall, the device functioned well, just slightly missing out on full marks in the demonstrations. The software was robust and contained no major issues, and the step detection algorithm was sufficiently accurate (>95% accuracy).

The software could be improved in future versions by addressing the minor joystick issue described previously. Additionally, the step detection algorithm could be improved further to detect running and extremely light steps.

The code structure was modular with high cohesion and low coupling, allowing bugs to be identified and fixed with minimal difficulty.