(evaluate ("{0}" =~ /(Å)¨0:Å/)) > dev:null
set Current "{¨0}:"
export Current
If "{BetaLinkType}" =~ /APPL/
	echo 'Include $$Shell("Current")"console.rsrc";' | rez -a -o "{1}" 
End
echo 'Include $$Shell("Current")"betaenv_macbody.rsrc";' | rez -a -o "{1}"
unset Current
