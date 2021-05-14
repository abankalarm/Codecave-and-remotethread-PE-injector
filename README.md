#### update: all code has finally been uploaded, as the project is complete.

# this project allows a gui framework in windows to inject shell / asm in both x64 and x32 architecture on windows platform

![ui](res/ui.png)

### The ui allows configuring as well as has a debug panel

![ui](res/debug.png)

## The project incorporates 2 techniques -

### 1. codecave

![ui](res/codecave.png)

Below is the proof code cave allows to inject code without changing the file size at all
![ui](res/codecave_poc.png)

### 2. remote thread injection

![ui](res/thread.png)

Analysis of remote thread injection in IDA
![ui](res/thread_analysis.png)

POC for remote thread injection
![ui](res/thread_poc.png)


## STEPS TO USE
1. copy clean apps to working directory
2. execute the exe file and enter file name
3. save file name and click on execute!!! for the appropriate architecture

notice:
i hold zero accountablity for usage of this or similar code, this has been posted only for educational purposes and should not be used for any other purpose.
