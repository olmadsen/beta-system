// Write last modification date of html file
// By Peter Andersen <pa@mjolner.com> inspired
// from various scripts at www.javagoodies.com

var month_names = new Array("January","February","March","April","May","June","July","August","September","October","November","December");
var day_names   = new Array("Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday");
var sup_date;
var century;
var lastmod = new Date(document.lastModified);

var sup       = new Array();
sup[1]        = "1<SUP>st</SUP>";
sup[2]        = "2<SUP>nd</SUP>";
sup[3]        = "3<SUP>rd</SUP>";
sup[21]       = "21<SUP>st</SUP>";
sup[22]       = "22<SUP>nd</SUP>";
sup[23]       = "23<SUP>rd</SUP>";
sup[31]       = "31<SUP>st</SUP>";

if ((lastmod.getDate()==1)  || (lastmod.getDate()==2)  || (lastmod.getDate()==3) ||
    (lastmod.getDate()==21) || (lastmod.getDate()==22) || (lastmod.getDate()==23) ||
    (lastmod.getDate()==31)) 
        sup_date = sup[lastmod.getDate()];
else
        sup_date = lastmod.getDate()+"<SUP>th</SUP>";
  
if (lastmod.getYear() >= 98 )
    century = "19";
else
    century = "20";
     
document.writeln("[Last modified: " + day_names[lastmod.getDay()] + " " 
		 + month_names[lastmod.getMonth()] + " " + sup_date
		 + " " + century + lastmod.getYear() 
		 + " at " + lastmod.getHours() + ":" + lastmod.getMinutes()
		 + "]");
