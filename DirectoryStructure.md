<p>Everything that is currently running on the robot, and our main development line goes in the <b>trunk</b> folder.<br>
<br>
<p>Anything that is not related to the project directly, but is still pretty cool or just good example code can be put in a folder inside the <b>misc</b> directory.<br>
<br>
<p>If you are working on a side project that would interfere with development on the current trunk directory and is related to our project can be added into the <b>branch</b> directory.<br>
<br>
<p>Within the trunk, we have several different folders each with a specific type of data inside it.<br>
<br>
<h1>trunk/</h1>
<code>*</code> <b>NetbeansProject</b> is where all the Netbeans related svn changes go.<br>
<br>
<code>*</code> <b>bin</b> is where all the compiled binary files (executables) will be stored.<br>
<br>
<code>*</code> <b>include</b> is where all h-files are copied once a build happens.  No svn files will be placed here.<br>
<br>
<code>*</code> <b>lib</b> is where all compiled libraries are built once a build happens.  No svn files will be placed here.<br>
<br>
<code>*</code> <b>src</b> is where all the source code will be placed.  For each class will have its own directory, in which its h,cpp and any related files will be stored.  Any test programs you write for the class should be stored here as well.<br>
<br>
<h2>trunk/src</h2>

<code>*</code> <b>mci</b> This is the motor controller interface class.  This class should take all the MC functions and data and bind it into an easily usable and decently abstracted class.<br>
<br>
<code>*</code> <b>nav</b> This is the navigation class.  This class should handle our navigation algorithms, hold our position data, etc.<br>
<br>
<code>*</code> <b>serial</b> This class manages the serial communication.  You only need to open up a specific port and read/write your data.  This will be used by the mci and sensors classes.<br>
<br>
<code>*</code> <b>sensors</b>  These are the additional sensors we might add to our robot.  All data should be decently abstracted, so we can get the data we need easily.<br>
<br>
<code>*</code> <b>vision</b> This class deals with grabbing frames from the camera and extracting the data we need out of it.  We should consider merging this with the navigation class.