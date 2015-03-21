# Introduction #

This page explains the steps needed in order to get Ubuntu running on a virtual machine on your home computer. Our virtual machine of choice will be Oracle VirtualBox, a very stable and well-supported virtual machine program.

In order to do this you will first need to download three things:

  * Oracle VirtualBox  http://www.virtualbox.org/wiki/Downloads
  * Ubuntu Linux       http://www.ubuntu.com/desktop/get-ubuntu/download
  * DAEMON Tools Lite  http://www.daemon-tools.cc/eng/products/dtLite  (Not necessary if you are willing to burn the Ubuntu image to a DVD)

Once you have these downloaded you are ready to begin. Please note that I assumed you are running some version of Microsoft Windows on your home computer when I wrote these instructions. It would be a bit pointless for our purposes for me to write instructions on installing an Ubuntu virtual machine if you are already running some version of Linux.


# Details #

  1. Install Oracle VirtualBox. This should be a relatively straightforward installation. Just double click the installer you downloaded from Oracle's website and follow the directions.
  1. Run VirtualBox.
  1. Click the **New** Icon on the left side of the window. A _Create New Virtual Machine_ window should open up. <img src='https://lh5.googleusercontent.com/_OYJ8fj3PJrU/TU59Eny4EhI/AAAAAAAAABQ/gf8mnuqi7M0/s400/Create%20Ubuntu%20VM.png' alt='Create New Virtual Machine Window' title='Create New Virtual Machine Window' />
  1. Click the **Next** button.
  1. Give your virtual machine a name. Something like "Ubuntu" or "My Super Crazy Awesome Robotics Team Virtual Machine" should be fine. Make sure that the OS Type is set to Ubuntu Linux. Click the **Next** button.
  1. Set the amount of RAM your virtual machine will use when running. The base setting of 512 MB should be OK, but you can increase it if you wish. I would recommend that this be set to 1024 MB, depending on your computer's total RAM size. Regardless of your choice, you can always change this later if you find that your virtual machine runs too slowly. Click the **Next** button.
  1. You will need to reserve disk space for the virtual machine hard disk. Make sure that _Boot Hard Disk_ is checked and the _Create new hard disk_ option is selected. Click the **Next** button. A _Create New Virtual Disk_ window should open up. <img src='https://lh4.googleusercontent.com/_OYJ8fj3PJrU/TU59FP-xnwI/AAAAAAAAABc/MShsgqVvjRQ/s400/VirtualBox%20Hard%20Disk.png' alt='Create New Virtual Machine' title='Create New Virtual Machine' />
  1. Click the **Next** button.
  1. Select _Dynamically expanding storage_ for the Storage Type. Click the **Next** button.
  1. Select a location on your hard drive to store the virtual hard disk file (the standard location should be fine). Select the size of the virtual disk (8 GB is the standard option. I would recommend increasing this slightly based upon how much disk space you have on your real hard disk). Click the **Next** button.
  1. Review your choices and click the **Next** button to create the new virtual disk.
  1. Click the **Finish** button. You should now have a virtual machine listed on the left hand side of the VirtualBox window. <img src='https://lh5.googleusercontent.com/_OYJ8fj3PJrU/TU59Ez5r9FI/AAAAAAAAABY/cfYRDpouswg/s400/VirtualBox%20Hard%20Disk%20Completed.png' alt='Create New Virtual Disk' title='Create New Virtual Disk' />
  1. Double click the newly created virtual machine. A _First Run Wizard_ window should pop up. Before continuing, you must either insert a DVD containing the Ubuntu image or mount the image using DAEMON Tools Lite. Install DAEMON Tools by double clicking its installer if you want to go this route. Then ensure that DAEMON Tools is running by selecting it from the Start menu. You should see a lightning bolt symbol in the bottom right corner of the task bar. Right click this icon, select Virtual Devices, then Device 0, then Mount Image. Navigate to the .iso Ubuntu image that you downloaded and select it. You should now have Ubuntu mounted and ready to go. <img src='https://lh3.googleusercontent.com/_OYJ8fj3PJrU/TU59E-0hchI/AAAAAAAAABU/H3uLuCOhfV8/s400/First%20Run%20Wizard.png' alt='First Run Wizard' title='First Run Wizard' />
  1. Continue with the VirtualBox installation. You should see Ubuntu loading. Eventually the Ubuntu installer should appear. Follow the directions for installing Ubuntu as if you were installing it directly on a new computer. <img src='http://www.ubuntu.com/sites/default/files/active/maverick/U2.1_start_fast_medium.jpg' alt='Ubuntu Loading Screen' title='Ubuntu Loading Screen' />
  1. You will eventually be asked to remove the installation media. Please eject the CD from the tray or unmount the .iso image from DAEMON Tools and then press **Enter**. The virtual machine should restart and you will be brought to the login screen. At this point you have completed your installation of Ubuntu onto your virtual machine. However, for maximum benefit you should now install the VirtualBox "Guest Additions" to allow for automatic resizing of your virtual machine window and better mouse integration.
  1. Login using your username and password. Then, under the _Devices_ menu of the VirtualBox window, select _Install Guest Additions..._.
  1. Under the _Places_ menu of Ubuntu, select the VBOXADDITIONS CD. The contents of the virtual CD should be displayed. Double click autorun.sh and select _Run in Terminal_. Type in your password and let the script run. Hit **Return** when the installations is complete. Note that you may have to restart the virtual machine in order for the changes to take effect.

Congratulations! You now have a fully functioning Ubuntu virtual machine installed on your computer!