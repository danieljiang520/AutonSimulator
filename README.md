# AutonSimulator
Houses 3D simulator to test integration of Auton stack

## Building Unreal Engine 4

`TODO`

## Building LCM
Only need to do this once per system. Navigate to the lcm submodule
and follow the build instructions therein before continuing.

Unless the build failed you should be mostly setup. If you find yourself
facing issues with the lcm library not being found like I did then try this fix

`
$ sudo cp /usr/local/lib/liblcm.so.1 /usr/lib
`

If you are still experiencing issues then when you find a solution please document them here.

## Mac Set Up
1. Go to https://www.epicgames.com/store/en-US/download and install Epic Games Launcher
2. Open Epic Games Launcher
3. In the Library section, click the add button next to ENGINE VERSIONS. Install 4.26.0 or newer (this version might be at the end of the selection. It is very important that you install 4.26+ on mac)
4. While you are waiting for unreal engine to install, open terminal and locate a folder where you want to store the mrover files. (E.g. cd Documents)
5. Clone the Simulator Files: git clone https://github.com/umrover/AutonSimulator.git
6. After you have set up the AutonSimulator folder, type cd AutonSimulator 
7. Clone the lcm files: git clone https://github.com/lcm-proj/lcm.git
8. Double check if there are files in the AutonSimulator/lcm folder
9. Now go back to Epic Games Launcher and launch unreal engine 4.26.0
10. Click more at the bottom of the window. Find and open the MroverSim.uproject file. 
11. If a window saying the project is built with another version of unreal engine, click make a copy
12. Now you should be able to see the game but without the rover
13. Go to https://drive.google.com/drive/folders/1kQf7xffSPj5jT0UwyLqin40EbcV6uL1i 
14. Download Complete_Rover.uasset
15. Open finder and copy that file to AutonSimulator 4.26/Content/Vehicle/Rover (Note: you must copy the asset file to the newly created AutonSimulator 4.26 folder)
16. Click play in Unreal Engine. Use wasd to move the rover. 