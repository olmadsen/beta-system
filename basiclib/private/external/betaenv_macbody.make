If "{BetaLinkType}" =~ /APPL/
	Rez -o "{1}" -a "{rincludes}"Types.r "{betalib}"basiclib:v1.2:private:external:console.r 
End
Rez -o "{1}" -a "{rincludes}"Types.r "{betalib}"basiclib:v1.2:private:external:betaenv_macbody.r
