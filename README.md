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