This is an add-on to the daimi-setup system.

All the files in the directory .daimi-setup in this directory are copied to all
users if they issue a command like:

	daimi-setup --addon /usr/local/lib/beta/daimi-setup/beta

When we have to update the setup, just update the files in
/usr/local/lib/beta/daimi-setup/beta and every user will get the updates the
next time they logout.  You should probably not change the files in
/usr/local/lib/beta/daimi-setup/beta directly, but change them in the
CVS-controlled copy in ~beta/<release>/daimi-setup/beta.

--grouleff
