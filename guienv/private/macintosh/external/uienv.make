(evaluate ("{0}" =~ /(Å)¨0:Å/)) >> dev:null
set base_dir "{¨0}:"
set current_dir "`directory`"


rez -a -o {1} "{rincludes}"types.r "{base_dir}"uienv.r

#make -f uienv.makefile > tmp
#catenate < tmp
#tmp
#delete tmp

