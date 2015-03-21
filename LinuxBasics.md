# Introduction #

You are going to need a non-essential computer.  That, or either **back up all your important information** before you choose to install Linux.  Usually it goes fairly smoothly, but bad things can happen and I don't want to be blamed for it.

You may question why I want you to just go ahead an install Linux, instead of trying out something like Cygwin in windows.  Being able to use Linux looks great on your resume' and can probably get you a job.

**Alternative to installing directly to your computer**

If you have a fast enough computer (i.e. NOT a netbook) then you can install Oracle Virtualbox. This is a virtual machine which will allow you to install another operating system in a sandbox without messing up your current system. The new operating system will run in a window like any other program on your computer.

http://www.virtualbox.org/

<img src='http://www.virtualbox.org/attachment/wiki/Screenshots/FreeBSD_win.png?format=raw' alt='VirtualBox Screenshot' title='VirtualBox Screenshot' width='600' height='450' />

If you want to go this route, then follow the instructions on this [page](http://code.google.com/p/ieee-lsu-robotics/wiki/VirtualBoxInstallation).


# Installation #

The easiest way to do this is to just install Ubuntu.  There are millions of Linux distributions out there, and I encourage you guys to check them out.  But for now, just install Ubuntu.
  * http://www.ubuntu.com/desktop/get-ubuntu/download
10.10 works, 10.04 does, too.  If you don't know if you are 64-bit or 32-bit, go with 32.

Make a USB boot stick (read the directions) and install it to the drive.  You can also make a CD, but I find that is A) faster and B) cheaper and more reliable to go the USB route.

Either way, when you reboot you're going to need to go into your BIOS.  This usually entails hitting DEL, F2, F8, F10, or F12 as fast as you can after your computer reboots.  Go find your boot devices and boot drive ordering.  In your boot drive ordering, just move your USB to the top position in the list.  If you have multiple drives remember which one was previously at the top.  Now if you are using a CD (or if you can't boot from USB, now you need to make a CD) you might want to make sure that your CD drive is above your HDD's in the device ordering.

Now it should boot into Ubuntu and you can follow the directions from there.

# Basic Linux Stuff #
All good Linux distros usually come with a package manager.  What this means is you do not search for .exe files on the internet to install, you simply type into terminal what program you want and it will install it, and all the dependencies for you.
> sudo aptitude install build-essential libhighgui-dev subversion
That is all you really need to do to get working with OpenCV and our repository.

If you have issues with random linux related stuff, you can most often find the solution on the Ubuntu Forums.
http://ubuntuforums.org/

Basic terminal operation, googling "linux terminal beginners guide":
http://www.freesoftwaremagazine.com/articles/command_line_intro?page=0,0

Actually working with the code, open up a terminal and type:
> svn checkout https://ieee-lsu-robotics.googlecode.com/svn/trunk/ ieee-lsu-robotics --username your@email.com
Wait a second while it downloads all the information, then type:
> cd ieee-lsu-robotics<p>
<blockquote>ls<br>
This should display everything in the directory.  As of now that is cameratest.cpp and compile.sh.  Try executing the script, by typing:<br>
make<br>
./bin/cameratest<br>
This should run the program, however you actually need a camera plugged up for it to work.  You can get around this by giving it a sample image:<br>
./bin/cameratest (something.png)<br>
Press escape to get the windows to close.</blockquote>

If you want to edit the code, type:<br>
<blockquote>gedit cameratest.cpp &<br>
This will start gedit, a text editor, and fork to the background which allows you to continue using that terminal.  Using a text editor and a terminal you can pretty much do everything you need to do on this project.  If you're a pro, you can use the text editor in the terminal.</blockquote>

Familiarize yourself with <a href='SVNCommands.md'>SVNCommands</a>.<br>
<br>
When you make a change to the SVN repository, you can commit that change by typing:<br>
<blockquote>svn commit<br>
It'll ask you to edit the log, but that isn't mandatory.  The real deal is that it will ask you for your login and password, because this repository is encrypted.</blockquote>

<a href='SVNPassword.md'>SVNPassword</a>
Read that, then commit your stuff.<br>
<br>
But if you break the code or commit something stupid, it will be in the change logs.  I will find it, and I will <b>hunt you down</b>.<br>
<br>
<img src='http://www.seattlepartybusrentals.com/wp-content/uploads/2010/09/dog-the-bounty-hunter.jpg' alt='Del the Bounty Hunter' title='Del the Bounty Hunter' />

<i>"Del the Bounty Hunter"</i>