dir /s /b *.bet private\*.bet ..\gpp\*.bet ..\gpp\private\*.bet \*.bet | find ".bet" | find /v ".bet~" | etags -o .\TAGS -
echo "(Ignore above error!)"
echo "Done!"

