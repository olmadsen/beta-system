# Usage:
#  (g)make beta(.windows)
#       test beta user
#  (g)make unix
#       test on unix
#  (g)make windows
#       test on windows
#  (g)make dump
#       dump Bclass2.class to Bclass2.J and display this
#  (g)make clean
#       delete generated files

beta: Bclass2User
	./Bclass2User

beta.windows: Bclass2User.bat
	./Bclass2User.bat

Bclass2User Bclass2User.bat: Bclass2User.bet
	jbeta Bclass2User.bet

unix: jvm/Bclass2.jar jvm/betauser/Bclass2User.class
	java -classpath "jvm/Bclass2.jar:jvm" betauser.Bclass2User

windows: jvm/Bclass2.jar jvm/betauser/Bclass2User.class
	java -classpath "jvm/Bclass2.jar;jvm" betauser.Bclass2User

jvm/Bclass2.jar jvm/beta/Bclass2.class: Bclass2.bet
	jbeta Bclass2

jvm/betauser/Bclass2User.class: Bclass2User.java
	javac -d jvm -classpath jvm/Bclass2.jar Bclass2User.java

dump: jvm/beta/Bclass2.class
	jcf-dump -c jvm/beta/Bclass2.class > Bclass2.J
	less Bclass2.J

clean:
	/bin/rm -rf *~ jvm *.J *.ast *.astL *.a2s Bclass2User *.bat *-jdb*
