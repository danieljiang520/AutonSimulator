# AutonSimulator
Houses 3D simulator to test integration of Auton stack

## Mac Set Up (Sep 25, 2021) reference: https://mycodecentral.com/installing-unreal-engine-for-mac
1. Install XCode (~30 GB) from the AppStore because XCode is used to compile C++ codes in Unreal Engine.
2. Go to https://www.epicgames.com/store/en-US/download and install Epic Games Launcher (~700 MB)
3. Open Epic Games Launcher
4. On the sidebar, click Unreal Engine. Then, click the Library section on the top menu bar. In the Library section, click the add button next to ENGINE VERSIONS. Install 4.26.0 or newer version of UnrealEngine (~30 GB). This version might be at the end of the selection box. 
5. While you are waiting for unreal engine to install, open terminal and locate a folder where you want to store the mrover files. (E.g. cd Documents)
6. Clone the Simulator Files: git clone https://github.com/umrover/AutonSimulator.git
7. After you have set up the AutonSimulator folder, type: cd AutonSimulator 
8. Type: git remote -v
11. Specify a new remote upstream repository that will be synced with the fork: git remote add upstream https://github.com/umrover/AutonSimulator.git
12. Verify the new upstream repository you've specified for your fork: git remote -v (you shold see two upstream links)
13. Fetch the branches and their respective commits from the upstream repository: git fetch upstream
14. Check out your fork's local default branch - in this case, we use main: git checkout main
15. Merge the changes from the upstream default branch - in this case, upstream/main - into your local default branch: git merge upstream/main
16. Now go back to Epic Games Launcher and launch unreal engine 4.26.0
17. Click more at the bottom of the window. Find and open the MroverSim.uproject file. 
18. If a window saying the project is built with another version of unreal engine, click more options and skip conversion
19. Now you should be able to see the game but without the rover
20. Go to https://drive.google.com/file/d/1mwYig0TFc-aNQFcowvJtupE5AZcrNtk-/view?usp=sharing
21. Download Complete_Rover.uasset
22. Open finder and move that file to AutonSimulator/Content/Vehicle/Rover
23. Click Compile in Unreal Engine
24. Click play in Unreal Engine. Click on the gameplay window once to engage keyboard recognition. Use wasd to move the rover. 

## Windows Set up (Sep 25, 2021) reference: https://www.worldofleveldesign.com/categories/ue4/ue4-download-install-unreal-engine-4.php
1. Install Visual Studio
2. Refer to Mac Set Up from step 2 to the end.

## Github troubleshooting
- When you use github and the terminal is displaying:
"remote: Permission to username1/repo.git denied to username2. fatal: unable to access 'https://github.com/username1/repo.git/': The requested URL returned error: 403", 
- where username2 = another github account and username1 is the account you want to use to push/pull, you need to change github accounts. Use the following link to help you: 
 https://gist.github.com/richchurcher 531b0452d7d5ea983daa314d0876f60a
- Configuring a remote for a fork: https://docs.github.com/en/github/collaborating-with-pull-requests/working-with-forks/configuring-a-remote-for-a-fork
- Checking out to a remote branch: git checkout -t upstream/branchName
https://stackoverflow.com/questions/1783405/how-do-i-check-out-a-remote-git-branch
- Renaming remote branch: https://stackoverflow.com/questions/30590083/how-do-i-rename-both-a-git-local-and-remote-branch-name

## Controls
- WASD or arrow keys or external controllers = move the rover
- C = switch cameras
- F = activate goForward function
- R = activate goRight function

## Building LCM
Only need to do this once per system. Navigate to the lcm submodule
and follow the build instructions therein before continuing.

Unless the build failed you should be mostly setup. If you find yourself
facing issues with the lcm library not being found like I did then try this fix

`
$ sudo cp /usr/local/lib/liblcm.so.1 /usr/lib
`

If you are still experiencing issues then when you find a solution please document them here.
