PPCC -appleext on -d MAC {betalib}basiclib:v1.5:private:external:basicio.c -o ¶
		 {betalib}basiclib:v1.5:private:ppc:basicio.o
PPCC -appleext on -d MAC {betalib}basiclib:v1.5:private:external:betaenv_ppcbody.c -o ¶
		 {betalib}basiclib:v1.5:private:ppc:betaenv_ppcbody.c.o
PPCC -appleext on -d MAC -appleext on {betalib}basiclib:v1.5:private:external:fileInt.c -o ¶
		 {betalib}basiclib:v1.5:private:ppc:fileInt.c.o
PPCC -appleext on -d MAC {betalib}basiclib:v1.5:private:external:assignRef.c -o ¶
		 {betalib}basiclib:v1.5:private:ppc:assignRef.o
PPCC -appleext on -d MAC {betalib}basiclib:v1.5:private:external:uniq.c -o ¶
		 {betalib}basiclib:v1.5:private:ppc:uniq.o
PPCC -appleext on -d MAC {betalib}basiclib:v1.5:private:external:timetick.c -o ¶
		 {betalib}basiclib:v1.5:private:ppc:timetick.o
PPCC -appleext on -d MAC {betalib}basiclib:v1.5:private:external:regexpr.c -o ¶
		 {betalib}basiclib:v1.5:private:ppc:regexpr.o
PPCC -sym on -opt off -d qAppleEvents=1 -d qInline=1 -appleext on ¶
		 :TextWindow:InlineInputSample.c -o {betalib}basiclib:v1.5:private:ppc:InlineInputSample.o