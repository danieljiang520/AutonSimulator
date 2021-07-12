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

## Mac Set Up (May 24, 2021)
1. Install XCode (~30 GB) from the AppStore because XCode is used to compile C++ codes in Unreal Engine.
2. Go to https://www.epicgames.com/store/en-US/download and install Epic Games Launcher (~700 MB)
3. Open Epic Games Launcher
4. In the Library section, click the add button next to ENGINE VERSIONS. Install 4.26.0 or newer version of UnrealEngine (~30 GB). This version might be at the end of the selection box. It is very important that you install 4.26+ on mac.
5. While you are waiting for unreal engine to install, open terminal and locate a folder where you want to store the mrover files. (E.g. cd Documents)
6. Clone the Simulator Files: git clone https://github.com/umrover/AutonSimulator.git
7. After you have set up the AutonSimulator folder, type cd AutonSimulator 
8. Clone the lcm files: git clone https://github.com/lcm-proj/lcm.git
9. Double check if there are files in the AutonSimulator/lcm folder
10. In terminal, go to the AutonSimulator folder. Type git remote -v
11. Specify a new remote upstream repository that will be synced with the fork: git remote add upstream https://github.com/umrover/AutonSimulator.git
12. Verify the new upstream repository you've specified for your fork: git remote -v (you shold see two upstream links)
13. Fetch the branches and their respective commits from the upstream repository: git fetch upstream
14. Check out your fork's local default branch - in this case, we use main: git checkout main
15. Merge the changes from the upstream default branch - in this case, upstream/main - into your local default branch: git merge upstream/main
16. Now go back to Epic Games Launcher and launch unreal engine 4.26.0
17. Click more at the bottom of the window. Find and open the MroverSim.uproject file. 
18. If a window saying the project is built with another version of unreal engine, click skip conversion
19. Now you should be able to see the game but without the rover
20. Go to https://drive.google.com/drive/folders/1kQf7xffSPj5jT0UwyLqin40EbcV6uL1i 
21. Download Complete_Rover.uasset
22. Open finder and copy that file to AutonSimulator/Content/Vehicle/Rover
23. Click play in Unreal Engine. Use wasd to move the rover. 

## Github troubleshooting
When you use github and the terminal is displaying:
"remote: Permission to username1/repo.git denied to username2. fatal: unable to access 'https://github.com/username1/repo.git/': The requested URL returned error: 403", 

where username2 = another github account and username1 is the account you want to use to push/pull, you need to change github accounts. Use the following link to help you: 
 https://gist.github.com/richchurcher 531b0452d7d5ea983daa314d0876f60a
 
Configuring a remote for a fork: https://docs.github.com/en/github/collaborating-with-pull-requests/working-with-forks/configuring-a-remote-for-a-fork
