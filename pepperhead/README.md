after cross-compilation copy the file .so onto the robot.
Add the name of the module to 'autoload.ini' file used by naoqi.
From build-<toolchain-name>/sdk/lib/naoqi folder copy .so using scp onto robot.
Declare your module in the 'autoload.ini' as follows:

[user]
 /path/to/libmymodule.so

use call_pepperhead.py script to send commands to the module.
By default the script connects to the localhost (127.0.0.1). The
IP address of the robot can be specified using '-b 11.22.33.44'.

