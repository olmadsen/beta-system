(evaluate ("{0}" =~ /(Å)¨0:Å/)) > dev:null
set CurrentDir "{¨0}:"
export CurrentDir
echo 'include $$Shell("CurrentDir")"classeditordialogs.rsrc";' | rez -a -o "{1}"
