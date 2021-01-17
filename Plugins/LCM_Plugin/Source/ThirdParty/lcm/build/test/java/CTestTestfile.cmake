# CMake generated Testfile for 
# Source directory: /home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/test/java
# Build directory: /home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/test/java
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Java::client_server "/usr/bin/python" "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/test/java/../run_client_server_test.py" "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/test/c/test-c-server" "/usr/bin/java" "-cp" "/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/test/java/lcm-test.jar:/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/test/types/lcm-test-types.jar:/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/build/lcm-java/lcm.jar:/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/test/java/junit-4.11.jar:/home/david/AutonSimulator/Plugins/LCM_Plugin/Source/ThirdParty/lcm/test/java/hamcrest-core-1.3.jar" "LcmTestClient")
