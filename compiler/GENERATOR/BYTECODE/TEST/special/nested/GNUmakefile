# Usage:
#  (g)make unix
#       test on unix
#  (g)make windows
#       test on windows
#  (g)make dump
#       dump Bclass2.class to Bclass2.J and display this
#  (g)make clean
#       delete generated files

unix: jvm/Bclass2.jar jvm/betauser/Bclass2User.class
	java -classpath "jvm/Bclass2.jar:jvm" betauser.Bclass2User
	@$(MAKE) msg

windows: jvm/Bclass2.jar jvm/betauser/Bclass2User.class
	java -classpath "jvm/Bclass2.jar;jvm" betauser.Bclass2User
	@$(MAKE) msg

jvm/Bclass2.jar jvm/beta/Bclass2.class: Bclass2.bet
	jbeta Bclass2

jvm/betauser/Bclass2User.class: Bclass2User.java
	javac -d jvm -classpath jvm/Bclass2.jar Bclass2User.java

dump: jvm/beta/Bclass2.class
	jcf-dump -c jvm/beta/Bclass2.class > Bclass2.J
	less Bclass2.J

msg: 
	@echo ""
	@echo "*** This went OK, but check the comment in Bclass2.bet"
	@echo "*** - naive users could do this."
	@echo "*** Shouldn't __init be allowed in the nested pattern?"
	@echo ""

always:

clean:
	/bin/rm -rf *~ jvm *.J *.ast *.astL *.a2s 
