For now type one or all of these in a terminal:
> man svn <p>
<blockquote>svn help <p>
svn <b>command</b> help <p></blockquote>

Important commands are<br>
<ul><li>checkout <p>
</li><li>update <p>
</li><li>add <p>
</li><li>remove <p>
</li><li>commit <p></li></ul>


<h2>Explanation</h2>

<blockquote>svn checkout url directory <p>
You should only do this once, as it will create a directory and fill it with the svn repository.</blockquote>

<blockquote>svn update <p>
This is used whenever you need to update your directory.  Do this whenever you are getting ready to write code, or if you need to be sure you have the latest revision.</blockquote>

<blockquote>svn add file<br>
This adds a new file into the version control system.  <b>Putting a file in the svn directory does not put it in version control</b>.  You must svn add it first.</blockquote>

<blockquote>svn remove file<br>
Kind of like add. But it removes things.</blockquote>

<blockquote>svn commit<br>
This is used whenever you have made changes to your local directory that need to be committed to the repository.  Commit often, but if you break something make sure to fix it soon.  Before you start working, svn update.  When you finish, svn commit. <p>
The first time you commit you might require a password. <a href='SVNPassword.md'>SVNPassword</a></blockquote>

<blockquote>svn revert<br>
This is for when you screw stuff up, and you want to change your directory back to a previous version.