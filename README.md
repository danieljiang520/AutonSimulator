# AutonSimulator
Houses 3D simulator to test integration of Auton stack

## Building Unreal Engine 4

`TODO`

## Building LCM
Only need to do this once per system. Navigate to the lcm submodule in the lcm_plugin
and follow the build instructions therein before continuing.

Once everything is built move the lcm_export.h file generated to the lcm source folder

Unless the build failed you should be mostly setup. If you find yourself
facing issues with the lcm library not being found like I did then try this fix

`
$ sudo cp /usr/local/lib/liblcm.so.1 /usr/lib
`

If you are still experiencing issues then when you find a solution please document them here.

## Making the LCM_Plugin ( Adding a third party library to unreal)
LCM is not a part of the UE4 ecosystem so in order to use it within unreal you have to make a plugin. 
This process will be similar for adding other external libraries like boost, eigen, openCV, etc...

So from the UE4 edditor go to settings, plugin, new plugin. Scroll down to the third party template.
Once its made do this next step right away, go to the .Build.cs file for MroverSim and actually add 
the plugin as a dependency as was done for the lcm plugin.

Now strip the example library from your plugin, and add:


`PublicAdditionalLibraries.Add(<Library Path>);`

`PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
`