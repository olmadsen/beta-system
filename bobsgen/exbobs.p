(*****************************************************************************
 *  B O B S - SYSTEM                  
 *  PARSER GENERATOR                  
 *                                    
 * UNIVERSITY OF AARHUS, DENMARK      
 *                                    
 * AUTHORS:                           
 *   SQREN HENRIK ERIKSEN             
 *   BENT BAEK JENSEN                 
 *   BENT BRUUN KRISTENSEN            
 *   OLE LEHRMANN MADSEN              
 *                                                                     
 * VERSION: January 1985                                               
 * This version has been heavily modified. It is not compatible with   
 * previous versions of BOBS. Contact Ole Lehrmann Madsen for further  
 * documentation. In most cases the "standard" manual may still be used:
 *      "THE B O B S - SYSTEM"                                         
 *       DAIMI PB-71. Third printing                                   
 *       DEPT. OF COMPUTER SCIENCE, UNIVERSITY OF AARHUS,              
 *       NY MUNKEGADE, DK8000 AARHUS C, DENMARK.                       
 *                                                                     
 * THIS PROGRAM WAS ORIGINALLY IMPLEMENTED IN THE FIRST VERSION OF     
 * PASCAL RELEASED FROM N.WIRTH. THIS IMPLEMENTATION WAS FULFILLED IN  
 * MARCH 1972. SINCE THEN, THE SYSTEM HAS BEEN CHANGED IN SEVERAL WAYS.
 * AMONG OTHERS, IT HAS BEEN CONVERTED INTO STANDARD PASCAL.           
 * THE SYSTEM IS INTENDED TO BE PORTABLE, HOWEVER THERE IS NO GUARANTEE
 * FOR THIS. YOU SHOULD BE AWARE OF (AT LEAST) THE FOLLOWING THINGS:   
 *  - THE TYPE CHAR, - THE TYPE ALFA, - THE MAXIMUM SIZE OF SETS.      
 *  SEE THE CONSTANTS: MINCH,MAXCH,SETMAX,ALFALENGTH IN THE PROGRAM.   
 *  THESE CONSTANTS SHOULD EASE MOVING THE SYSTEM. NOTE, IF YOU CHANGE 
 *  THE CONSTANT ALFALENGTH, YOU MAY HAVE PROBLEMS WITH STRINGS.       
 *                                                                     
 * DUE TO THE MANY CHANGES IN THE SYSTEM, THE PROGRAMMING IS NOT SO    
 * NICE AS WE WOULD LIKE IT TO BE. YOU SHOULD NOT TRY TO MAKE CHANGES  
 * YOURSELF. IF YOU FIND ERRORS OR 'OTHERS' YOU MAY WISH TO CHANGE,    
 * PLEASE WRITE TO US. WRITE IN ANY CASE AND TELL US WHAT PROBLEMS     
 * YOU HAD IN GETTING THE SYSTEM TO RUN.                               
 * NOTE: WE CANNOT GUARANTEE ANY SUPPORT OF THE SYSTEM .               
 *                                                                     
 * Changes: March-May 1993:					      
 * - to adapt to p2c program, which translates pascal into C /JLK      
 * - fix of error when 'duplicate terminals'. All duplicates were      
 *   assigned a new internal number. This gave an error when name, etc.
 *   were dublicated. /OLM              			       
 * - reserved terminals like NAME, KONST, STRING, ERROR, EMPTY have    
 *   changed into _NAME_, _KONST_, _STRING_, _ERROR_, _EMPTY_.         
 *   This has been done in order to allow, NAME, etc. as legal         
 *   terminal symbols in the grammar. /OLM                             
 * Changes: March 1994:                                                
 * - removed 'packed' from all data structures, since the gcc (GNU C)  
 *   compiler generate wrong code on SUN Solaris (SPARC). /JLK         
 * Changes September 1994:                                             
 * - removed dependency on sequential allocation of dynamic structures 
 *   in the heap from the operation stateno.  It did not work on Linux 
 *   machines.  Instead, a global variable, seqIndex is introduced.    
 *   Each time a 'pointer' is allocated (in the allocp operation), the 
 *   seqIndex is incremented, and the new value is assigned to the new 
 *   field, seq, in the record.  In stateno, this field is now used in 
 *   the binary search, instead of the actual pointer addresses. /JLK  
 * Changes August 1994, v1.3/OLM:                                      
 *  - In procedure lookahead:trans an error was corrected; see comment 
 *  - minor error in write stmt corrected in niceparser                
 * Changes August 1994, v1.4/OLM:
 *  - All terminals muts now be enclosed by metasymbol 5, default is ";
 *    This is the case for the initial list of terminals as well as
 *    terminal symbols in productions; version meta/v1.4/gen has been adapted
 *    to this version of bobs
 *  - Changes in tables format to be used by tabc.bet. A dot (.) has been
 *    inserted between label and production numnber; does not affect bobs,
 *    but only meta-gen and tabc.
 *)
{$b0}
(* to turn off output buffering insert  $b0  *)

 program exbobs(input,output(* removed by JLK to please p2c: ,parsin,parsout,tables*));

 label 999;
 const
   const1=2400;
   const2=900;
   const3=720;
   const4=80000; (* JLK: 17/6-95 was 40000 *)
   const5=63;
   const6=6000;
   const7=20000;
   const8=480; (* JLK: 17/6-95 was 240 *)
   const9=10000; (* ESS: 30/6-95 was 2000 *)
   const10=7200;
   const11=130;
   const12=840;
   const13=5;
   const14=15;
   const16=10000; (*NOTICE: CONST16>CONST2*) (* JLK: 17/6-95 was 5000 *)
   const18=75;
   const19=12000; (*MAX SIZE OF ARRAY LABELBUF/ SUM OF LENGTH *)
                  (* OF ALL PRODUCTION LABELS (OPTIONS[34])   *)
   const20=1200;  (*max length of a production label *)
 
   minch=' '; maxch='~'; (*THE FIRST/LAST CHAR IN TYPE CHAR*)
   setmax=63;            (*MAX. VALUE OF INTEGERS IN A SET *)
   alfalength=10; (* NO. OF CHARS IN TYPE ALFA *)
   alfal20=20; (* NB! this is a quick change ; length of type alfa20*)
   alf3=31;       (*MUST BE 3*ALFALENGTH+1 *)
 
   rhsnil=0; (*THE EMPTY REFERENCE OF CHAINS IN RHS*)
   blank='          '; blank20='                    ';
 
 type
   alfa= (*packed*) array[1..alfalength] of char;
   symbol= 0..const2;
   rtypeset= set of 0..setmax;
   rtype=record r: array[0..const13] of rtypeset end;
   pointer=^konfigt;
   pointer1= ^ nontelm;
   nontelm= (*packed*)
   record  word1,word2,word3: alfa;
      rlink,llink: pointer1;
      nontermvaerdi: 0..const2
   end;
   pointer2=0..const4;
   termpointer= ^ termelm;
   termelm= (*packed*)
   record niveaup,higherp: termpointer;
      intern: -1..const2;
      tegn: char;
      ok: boolean
   end;
   prodtype=(*packed*)
   record leftside: 0..const2;
      start: pointer2;
      lookbackp: pointer;
      laengde: 0..15
   end;
   entrytyp=(*packed*)
   record dummyyp, termp: termpointer;
      intern1: -1..const2;
      tegn1 :char;
      ok1: boolean
   end;
 
   bitmatrix=array[0..const2]of rtype;
   modetype=0..15;
   konfigt= (*packed*) record
                      derivp,nextp: pointer;
                      dot: modetype; (* DOT-PLACERING TIL BRUG I ADEQUAD *)
                      ifbasis: boolean;
                      seq: integer (* added by jlk to solve Linux problem *);
                      case mode: modetype of
                         1,2,3,4: (inf:0..const2; prodnr:0..const1);
                         5: (lookbp: pointer)
                      end;
   erastype=(firsttim,finish);
   dayfilemsg=(*packed*) array[1..40] of char;
   alfa20=(*packed*) array[1..alfal20] of char;
 
 var
   seqIndex: integer (* line added by jlk to solve Linux problem *);
   entry: array[char] of entrytyp;
   rhs: array[pointer2] of (*packed*)
   record  symbol: 0..const2;
      parserp: pointer;
      link: pointer2;
      basisl: 1..const5;
      basis: boolean;
      first:0..const19; length:0..const20;
         (*ADDRESS OF PRODUCTION LABEL IN LABELBUF (OPTIONS[34])*)
      seqno: integer; (* input seqNo of this production *)
   end;
   lefthelp :array[0..const2] of pointer2;
   prod:       array[0..const1] of prodtype;
   help:       array[0..const2] of (*packed*)
   record afledt,overgang: boolean;
      prodindex: 0..const1;
      rightp: pointer2;
      status: erastype;
      term: boolean
   end;
   tilstand:   array[0..const10] of (*packed*)
   record
      errorno: 0..const10;
      oldstart: pointer;  newstart: 0..const7
   end;
   internrep:  array[-1..const2] of alfa20;
   husk:       array[1..const2] of integer;
   husknonterm:array[0..const2] of (*packed*)
   record nontermp: pointer1;
      leftboo,rightboo: boolean
   end;
 
   prodcount,
   emptyvalue,errorval,nameval,cstval,stringval : integer;
   stringch: char;
 
   last,first,dynp,statp:  pointer1;
   point,huskp,helpp,top: pointer2;
   termtop,gl,gn,gc,gs,go: termpointer;
 
   ch,s: char;
 
   internv: 0..const2;
   antalprod,antaltilst,tilstnr,lbbegin,lbend,trmax,
   nontslut,nontstart,mstime,
   k,j,i,tal,count,goalhusk,empty,
   termantal,termrep,symb,termg,optno,dummy: integer;
   error,nontermboo,goaltest,emptyboo,goalboo,errorboo,venstreboo,
   first37,nboo1,nboo2,noword,firstboo,error1,error2,error3: boolean;
 
   rodp,begintilst,lqbep,classtop,gemp,oldp,freeptr: pointer;
 
   blst,parsin,parsout,tables: text;
 
   fcq: array[1..const3] of
   (*packed*) record
             udgang: pointer;
             frekvens : 0..const6
          end;
   fcqi :integer;
   (* FCQ AND FCQI ARE USED IN PROCEDURE
      REMEMBER AND OPTIMIZE, *)
   options: array[1..const18] of boolean;
 
 
   combegin,comlength : integer ;
   comend : (*packed*) array[1..alfalength] of char ;
 
   (*VARIABLES TO STORE AND READ PRODUCTION LABELS (OPTIONS[33,34])*)
   labelbuf: (*packed*) array[0..const19] of char;
   linx: 0..const19;
   prodseqno: integer;
   nolook: array [0..const1] of integer;
   nolooki: integer; (* INIT=0 *)
   allnolook: boolean; (* IS ALL PRODUCTIONS TO BE ATTEMPTED? *)
   (* used by procedure initempty and lookahead procedures  *)
   (* emptya[symb]=true if symb may produce the empty string*)
   emptya: array [0..const2] of boolean;
 
   (* variables used in order to parse sentential forms *)
   nontl, nontr: integer;
    (* lookBackEntry: array[0..const2] of pointer; *)
 
   cstmax: array[1..20] of integer;
 
(*$L-*)
(***************** grammar to ROSE    *********************************)
 
   prodspl: array[0..const1] of (*packed*) record splstart,spllen: 0..60000 end;
   symbspl: array[0..const2] of (*packed*) record splstart,spllen: 0..60000 end;
   splstart, spllen: integer;
   spltab: text;
   f1,f2,f3,f4,f5: text;
 
   procedure initspl;
   begin rewrite(spltab,'spltab   ');splstart:=1;spllen:=0 end;
   procedure splch(ch: char); begin spllen:=spllen+1; write(spltab,ch) end;
   procedure syspl(sy: integer);
   begin symbspl[sy].splstart:=splstart;
         symbspl[sy].spllen:=spllen;
         splstart:=splstart+spllen; spllen:=0;
   end;
   procedure prspl(p:integer);
   begin prodspl[p].splstart:=splstart;
         prodspl[p].spllen:=spllen;
         splstart:=splstart+spllen; spllen:=0;
   end;
   procedure spl(a:alfa);
   var i: integer;
   begin
     for i:=1 to alfalength do
         if a[i]<>' ' then splch(a[i])
   end;
   procedure spl20(a:alfa20);
   var i: integer;
   begin
     for i:=1 to alfal20 do
         if a[i]<>' ' then splch(a[i])
   end;
   procedure tv(p:pointer1);
   begin
     if p<>nil then
     begin tv(p^.llink); tv(p^.rlink);
        with p^ do
        begin spl(word1); spl(word2); spl(word3);
              syspl(nontermvaerdi)
   end end end;
 
  procedure rosegram;
  var l,p,i,c,abrhslen,corhslen,rhsinx:integer;
  begin
 
    (* spelling tables *)
    initspl;
    (*terminal symbols*)
    for c:=0 to termg do
    begin spl20(internrep[c]); syspl(c) end;
    (* nonterminal symbols*)
    tv(first);
    (* production labels*)
    for p:=0 to antalprod do
    with rhs[prod[p].start] do
    begin
       for i:=first to first+length-1 do splch(labelbuf[i]);
       prspl(p);
    end;
 
     abrhslen:=0; corhslen:=0;
     for p:=0 to antalprod do
         with prod[p] do
         for i:=start+1 to start+laengde do
         begin corhslen:=corhslen+1;
               if rhs[i].symbol > termg then abrhslen:=abrhslen+1;
     end;
 
     rewrite(f1,'f1       ');
     rewrite(f2,'f2       ');
     rewrite(f3,'f3       ');
     rewrite(f4,'f4       ');
     rewrite(f5,'f5       ');
     write(f1,antalprod); write(f2,nontslut-nontstart+1); write(f3,abrhslen);
     write(f4,antalprod); write(f5,corhslen);
 
    l:=1; rhsinx:=1;
    for p:=0 to antalprod do
    with prod[p],prodspl[p] do
    begin
       write(f4,leftside,rhsinx,laengde,splstart,spllen);
       c:=0;
       for i:=start+1 to start+laengde do
       begin rhsinx:=rhsinx+1;
(***********************************************
          with SymbSpl[rhs[i].symbol] do
           if rhs[i].symbol <= termg then
              write(f5,0,SplStart,SplLen)
           else begin c:=c+1;
             write(f5,1,c);
             write(f3,rhs[i].symbol)
           end;
***************************************************)
       end;
       write(f1,leftside,l,c); l:=l+c;
    end;
 
    for i:=nontstart to nontslut do
    with symbspl[i] do write(f2,splstart,spllen);
 
 end;
 
 
(******************** end ROSE *************************************)
(*$L-*)
 
   procedure initmax;
   var i:integer;
   begin for i:=1 to 20 do cstmax[i]:=0 end;
   procedure updatemax(cst,val:integer);
   begin
      if cstmax[cst] < val then cstmax[cst]:=val;
   end;
   procedure printmax;
   var i: integer;
   begin  writeln(blst); writeln(blst,' statistics :');
      for i:=1 to 20 do
      begin
         write(blst,' const',i:1,' used ',cstmax[i],' of ');
         case i of
          1: writeln(blst,const1:1);
          2: writeln(blst,const2:1);
          3: writeln(blst,const3:1);
          4: writeln(blst,const4:1);
          5: writeln(blst,const5:1);
          6: writeln(blst,const6:1);
          7: writeln(blst,const7:1);
          8: writeln(blst,const8:1);
          9: writeln(blst,const9:1);
         10: writeln(blst,const10:1);
         11: writeln(blst,const11:1);
         12: writeln(blst,const12:1);
         13: writeln(blst,const13:1);
         14: writeln(blst,const14:1);
         15: writeln(blst,' not used ');
         16: writeln(blst,const16:1);
         17: writeln(blst,' not used ');
         18: writeln(blst,const18:1);
         19: writeln(blst,const19:1);
         20: writeln(blst,' not used ');
        end;
     end;
   end;
 
   function clock:integer; begin clock:=0 end;
 
   procedure msg(m: dayfilemsg);
     (* WRITES A MESSAGE IN THE KRONOS DAYFILE *)
     (* THIS PROCEDURE MAY BEE REMOVED         *)
   begin
     writeln(blst,m)
   end;

   procedure writech(ch:char;no:integer);
   var i:integer;
   begin
     for i:=1 to no do write(blst,ch)
   end;
 
   function lf:char;
   begin
     writeln(blst); lf:=' ';
   end; (*LF*)
 
   procedure allocate(var p:pointer2);
   forward;
 
   procedure outalf(a:alfa; var t: integer);
   var i: integer;
   begin
     if a<>blank then
      begin i:=alfalength;
        while a[i]=' ' do i:=i-1;
        write(blst,a:i); t:=t+i;
      end;
   end;
 
   procedure outalf20(a:alfa20; var t: integer);
   var i: integer;
   begin
     if a<>blank20 then
      begin i:=alfal20;
        while a[i]=' ' do i:=i-1;
        write(blst,a:i); t:=t+i;
      end;
   end;
 
   procedure nontwrit(i: integer;var  t: integer);
   begin
     write(blst,'<'); t:=t+1;
     if i=0 then outalf('BOBSGO    ',t) else
      if const2<i then writeln(blst,'index error in nontwrit')
      else
        if husknonterm[i].nontermp=nil then 
           begin if i=nontstart then write(blst,'GoalSymbol')
                 else write(blst,'NIL pointer in nontwrit')
           end
        else
         with husknonterm[i].nontermp^ do
         begin
            outalf(word1,t); outalf(word2,t); outalf(word3,t);
         end;
     write(blst,'>'); t:=t+1;
   end;
 
   procedure symbwrite(i: integer; var t:integer);
   begin
      if i <= termg then outalf20(internrep[i],t)
                    else nontwrit(i,t)
   end;
 
(**********)
 
procedure outgrammar;
   const pagew=85; labelpos=70;
   var altpos,lhs,bobsno,oldlhs,pos,symb,p,seqno,k,i : integer;
       rhsp,rhsp1: pointer2;

   procedure lfcheck(i: integer; var pos : integer; max,indpos: integer);
   var j: integer;
   begin
      if (i+pos) > max then
      begin writeln(blst); for j:=1 to indpos do write(blst,' ');
            pos:=i+indpos
      end else pos:=pos+i;
   end;

   procedure writenont(n: integer; var pos: integer);
   var i,j: integer; c: (*packed*) array[1..alf3] of char;
   begin
      if n=0 then
        begin write(blst,'BOBS-GO'); pos:=pos+7;
        end 
      else if n=nontstart then
        begin write(blst,'GoalSymbol'); pos:=pos+10
        end
      else with husknonterm[n].nontermp^ do
      begin
         for i:=1 to alfalength do c[i]:=word1[i];
         for i:=1 to alfalength do c[i+10]:=word2[i];
         for i:=1 to alfalength do c[i+20]:=word3[i];
         i:=3*alfalength;
         while c[i]=' ' do i:=i-1;
         lfcheck(i+2,pos,labelpos,altpos+3); write(blst,'<');
         for j:=1 to i do write(blst,c[j]); write(blst,'>');
   end;end;

   procedure writeterm(t:alfa20; var pos: integer);
   var i,j: integer;
   begin i:=alfal20;
      while t[i]=' ' do i:=i-1;
      lfcheck(i,pos,labelpos,altpos+3);
      for j:=1 to i do write(blst,t[j]);
   end;

   procedure nextprod(var lhs: integer; var rhsp: pointer2;
                      var bobsno,seqno: integer);
   label 10;
   var lhsi,k: integer;
   begin bobsno:=0;
      while true do
      begin
         for lhsi:=nontstart+1 to nontslut do
         begin lhs:=lhsi; rhsp:=help[lhs].rightp;
               if rhsp<>rhsnil then
               repeat bobsno:=bobsno+1;
                      if rhs[rhsp].seqno=seqno then goto 10;
                      for k:=1 to rhs[rhsp].basisl do allocate(rhsp);
                      rhsp:=rhs[rhsp].link;
               until rhsp=rhsnil
        end;
        seqno:=seqno+1;
      end;
10:
end;
 
   begin  writeln(blst); page(blst);
   for k:= 1 to  45 do write(blst,'*');
   write(blst,'  The Grammar  ');
   for k:=k+15 to pagew do write(blst,'*'); writeln(blst);
   writeln(blst,'     BOBS');
   oldlhs:=0;  seqno:=0;
   for p:=1 to antalprod do
   begin seqno:=seqno+1;
       nextprod(lhs,rhsp,bobsno,seqno);
       if lhs<>oldlhs then writeln(blst);
       write(blst,seqno:4,bobsno:4, '   '); pos:=11;
       if lhs<>oldlhs then
       begin writenont(lhs,pos); write(blst,' ::= ');
             altpos:=pos+2; pos:=pos+5; oldlhs:=lhs;
       end else begin pos:=altpos+3;
           (* altPos is no.of chars before | *)
           for i:=1 to altpos-11 do write(blst,' '); write(blst,'|  ');
       end;
       rhsp1:=rhsp;
       for k:= 1 to rhs[rhsp].basisl do
       begin allocate(rhsp1); symb:=rhs[rhsp1].symbol;
             if symb <= termg then writeterm(internrep[symb],pos)
             else writenont(symb,pos);
             write(blst,' '); pos:=pos+1;
       end;
       if options[33] or options[34] then
       with rhs[rhsp] do
       begin for pos:=pos to labelpos do write(blst,' '); write(blst,':');
             for k:=first to first+length-1 do
              begin pos:=pos+1; lfcheck(1,pos,pagew,labelpos+2); 
                    write(blst,labelbuf[k]);end;
       end;
       writeln(blst);
   end;
   writeln(blst);
   for k:=1 to pagew do write(blst,'*'); writeln(blst);
end;
 
 
 
   procedure stop(n:integer);
     (* ALL ABNORMAL TERMINATION IS THROUGH THIS PROCEDURE*)
   begin
      writeln(blst); writeln('!!!!! ABNORMAL TERMINATION OF BOBS!');
     case n of
        0 : (*MISCELLANEOUS*);
        1: (*CONSTERROR*);
       2: begin writeln('!!!!! ERROR(S) IN INPUT! See lst-file for details');
	  end;
        3: (*ERROR(S) IN GRAMMAR*)
           begin outgrammar;
             writeln(blst,'***** ERROR(S) IN GRAMMAR ');
             writeln('!!!!! ERROR(S) IN GRAMMAR! See lst-file for details');
           end;
        4: (*NOT SLR/LALR(1) *);
        5: (*ERRONEOUS PARSIN FILE*);
       6: begin writeln(blst,'INFINITE STACK-GROWTH POSSIBLE IN LALRK');
	     writeln('INFINITE STACK-GROWTH POSSIBLE IN LALRK');
           end;
       7: begin writeln(blst,'CIRCULARITY IN LALRK');
	     writeln('CIRCULARITY IN LALRK');
           end;
     end;
     goto 999;
   end;(*STOP*)
 
   procedure constval(c:integer; var r:alfa);
   var
     gem:array[0..20] of char;
     a,b,i,j:integer;
   begin
     if c<1000000 then
      begin
        a:=c;  gem[11]:=')';
        for j:=12 to 20 do gem[j]:=' ';
        j:=10;
        repeat
          b:=a mod 10;
          a:=a div 10;
          gem[j]:=chr(ord('0')+b);
          j:=j-1;
        until a=0;
        gem[j]:='(';
	for i:=1 to alfalength do r[i]:=gem[j+i-1];
      end else r:='(********)';
   end;
 
   procedure consterror(s1,s2:alfa; cc:integer);
   var aa:alfa;
     m: array[1..4] of alfa;
     ms: dayfilemsg;
     i,j: integer;
   begin
      writeln('!!!!! ERROR IN ',s1,': ',s2,'TO SMALL (',cc:1,')');
      writeln(blst); writeln(blst);
      write(blst,'***** ERROR IN ',s1,': ',s2,'TO SMALL (',cc:1,')');
(*     constval(cc,aa);
     m[1]:=s2; m[3]:=aa;
     m[2]:=' TO SMALL '; m[4]:='          ';
     for i:=1 to 4 do
     for j:=1 to 10 do ms[(i-1)*10+j]:=m[i,j];
      writeln(ms); writeln(blst,ms);
 *)
     stop(0)
   end;
   procedure allocate; (* VAR P:POINTER2 *)
   begin
     if p >= const4 then consterror('ALLOCATE  ','CONST4    ',const4);
     p:=p+1;
   end; (*ALLOCATE*)
 
   procedure initprod;
   var
     p: pointer2;
     k,i,l: integer;
   begin
     k:=-1;
     for i:=nontstart to nontslut do
     begin
       p:=help[i].rightp;
       while p<>rhsnil do
       begin k:=k+1;
         if k>const1 then consterror('INITPROD  ','CONST1    ',const1);
         with prod[k] do
         begin
           leftside:=i; start:=p; laengde:=rhs[p].basisl;
           for l:=1 to laengde do allocate(p);
           if (laengde=1) and (rhs[start+1].symbol=emptyvalue) (*EMPTY RIGHT HAN
D SIDE*)
            then laengde:=0;
         end;
         p:=rhs[p].link;
       end;
     end;
     prod[k+1].leftside:=0; antalprod:=k;
   end;
 
   procedure dump1;
   var
      i	: integer; sorted: boolean; seq1: integer;
   begin
      write(blst,lf,lf,lf,' TILSTAND'); seq1:=-1; sorted:=true;
     for i:=0 to antaltilst do
     with tilstand[i]  do
	begin
	   write(blst,lf,i:5,ord(oldstart),oldstart^.seq,newstart,ord(newstart));
	   if seq1>oldstart^.seq then
	   begin sorted:=false; write(blst,'<<< this state NOT sorted'); end;
	   seq1:=oldstart^.seq;
	end;
      if sorted then writeln(blst,lf,'tilstand sorted')
      else writeln(blst,lf,'ERROR: tilstand not sorted');
   end;
 
   procedure dump2;
   var
     lqb: pointer2;
   begin
     lqb:=top;
     write(blst,lf,lf);
     write(blst,' RIGTHSIDE ');
     write(blst,lf);
     write(blst,'              SYMBOL     LINK     BASISL   PARSERP');
     repeat
       write(blst,lf);
       with rhs[lqb] do write(blst,ord(lqb),symbol,ord(link),basisl,ord(parserp));
       allocate(lqb);
     until lqb=point;
   end;
 
 
   procedure dump3;
   var
     i: integer;
   begin
     write(blst,lf,lf);
     write(blst,' HUSKNONTERM '); write(blst,lf);
     write(blst,'  NONTERMP  LEFTBOO  RIGHTBOO');
     for i:=nontstart to nontslut do
     with husknonterm[i] do
     write(blst,lf,ord(nontermp),ord(leftboo),ord(rightboo));
   end;
 
 
   procedure dump4;
   var i: integer;
   begin
     write(blst,lf,lf);
     write(blst,' HELP'); write(blst,lf);
     for i:=nontstart to nontslut do write(blst,' ',ord(help[i].rightp),lf);
   end;
 
   procedure dump5;   (* OPTION 16 *)
   var
     i,t: integer;
   begin
     page(blst);
     write(blst,'A DUMP OF THE PROD-ARRAY');
     write(blst,lf);
     write(blst,'  START      LOOKBACKP   LAENGDE    LEFTSIDE');
     write(blst,lf);
     for i:=0 to antalprod do
     with prod[i] do
     begin
       write(blst,start:6);
       if lookbackp=nil then write(blst,'NIL':14)
       else write(blst,ord(lookbackp):14);
       write(blst,laengde:8);
       write(blst,'        ');
       if i<>0 then nontwrit(leftside,t);
       write(blst,lf);
     end;
     write(blst,lf,lf);
   end;
 
   procedure outterminal;
     (* OUTPUT THE INTERN VALUES OF TERMINALS *)
   var
     i: integer;
   begin
     write(blst,lf,lf,lf);
     write(blst,' TERMINAL        INTERN VAERDI');
     write(blst,lf,lf);
     for i:= 0 to termantal  do write(blst,' ',internrep[i],blank,i,lf);
     write(blst,lf,lf,' ');
   end; (*OUTTERMINAL*)
 
   procedure newelm(var top:pointer2;   rname:alfa);
   begin
     if top >= const4 then consterror(rname,'CONST4    ',const4);
     top:=top+1;
   end; (*NEWELM*)
 
   procedure matrixout(s:bitmatrix);
   var
     i,j: integer;
   begin
     write(blst,lf,lf);
     write(blst,' BITMATRIX');
     for i:=0 to nontslut do
     begin write(blst,lf,' ');
       for j:=0 to nontslut do
       if ((j mod (setmax+1)) in s[i].r[j div (setmax+1)]) then write(blst,'1') else
 write(blst,'0');
     end;
     write(blst,lf,lf);
   end;
 
   procedure inithelp;
   var
     i,symb:integer;
   begin
     i:=0;
     while i <= antalprod do
     begin
       symb:= prod[i].leftside;
       help[symb].prodindex:= i;
       repeat i:=i+1;
       until symb<> prod[i].leftside;
     end;
   end;
 
   procedure skrivparser(  p: pointer);
     (*  PROCEDURE TIL TEST AF GENERERET PARSER   *)
   var
     t,i: integer; lqbep: pointer;
     dummy: integer;
   begin
     page(blst);
     write(blst,lf,lf,' PARSER',lf,lf);
     write(blst,' BASIS TILSTADR   MODE   DERIVP   NEXTP  PRODNO  INF');
     write(blst,lf,lf);
     if antaltilst=0 then t:=tilstnr else t:=antaltilst;
     for i:=0 to t do
     begin
       lqbep:=tilstand[i].oldstart;
       repeat
         with lqbep^ do
         begin
           if ifbasis then write(blst,' *') else write(blst,'  ');
           write(blst,ord(lqbep):13,mode:6);
           if derivp=nil then write(blst,'       NIL')
           else write(blst,ord(derivp):10);
           if nextp =nil then write(blst,'     NIL')
           else write(blst,ord( nextp):8);
           if (lbbegin <= i) and (i <= lbend)
            then begin
              write(blst,' LOOKBACK: ');
              if lookbp=nil then write(blst,'       NIL')
              else write(blst,ord(lookbp):10);
            end
           else begin
              write(blst,prodnr:6);
              write(blst,'    ');
              if mode<>0 then
               if inf <= termg
                then begin write(blst,' ');
                  outalf20(internrep[inf],dummy) end
               else nontwrit(inf,dummy);
            end;
           write(blst,lf);
           lqbep:=derivp;
         end;
       until lqbep=nil;
       write(blst,lf);
     end;
   end; (*SKRIVPARSER*)
 
   procedure allocp(var p: pointer;   m:integer; a: alfa);
   begin
     if freeptr <> nil then
      begin
        p:=freeptr; freeptr:=freeptr^.derivp;
      end
     else
      begin
        case m of
           1: (* changed by JLK to please p2c: new(p,1); *) new(p);
           5: (* changed by JLK to please p2c: new(p,5); *) new(p);
        end;
        if p=nil then consterror(a,'CONST6    ',const6);
        seqIndex:=seqIndex+1; p^.seq:=seqIndex; (* line added by jlk to solve Linux problem *)
      end;
     p^.derivp:=nil;
   end; (*ALLOCP*)
 
 
   procedure initempty;
   var pn,rhsinx,j: integer; empty,changes: boolean;
   begin for pn:=0 to nontslut do emptya[pn]:=false;
     repeat changes:=false;
       for pn:=0 to antalprod do
        if not emptya[prod[pn].leftside] then
        begin empty:=true;
         rhsinx:=prod[pn].start;
         for j:=1 to prod[pn].laengde (*possibly zero*) do
            empty:=empty and emptya[rhs[rhsinx+j].symbol];
         if empty then
         begin
             emptya[prod[pn].leftside]:=true;
             changes:=true;
        end;end;
     until changes=false;
     if options[36] then
     begin write(blst,lf,lf);
        writeln(blst,'The following nonterminals may produce the empty string:');
        for pn:=nontstart to nontslut do
        if emptya[pn] then
        begin  write(blst,'  '); j:=0;  nontwrit(pn,j); writeln(blst);
        end;
        write(blst,lf,lf);
     end;
   end; (* INITEMPTY *)
 
 
 
   procedure remember(p:pointer);
     (* REMEMBER IS USED TO COUNT THE
        FREQUENCY OF HOW OFTEN
        THE DIFFERENT VALUES OF NEXTP
        IN A LOOKBACKSTATE ARE USED *)
   label 5;
   var i: integer;
   begin
     for i:=1 to fcqi do
        if fcq[i].udgang=p then 
        begin
            fcq[i].frekvens:=fcq[i].frekvens+1;
	    goto 5
        end;
     fcqi:=fcqi+1;
     if fcqi>const3 then consterror(' REMEMBER ','CONST3    ',const3);
     fcq[fcqi].udgang:=p;
     fcq[fcqi].frekvens:=1;
    5:
   end (* REMEMBER *) ;
 
   procedure optimize(var maxnextp:pointer; var md:integer);
     (* OPTIMIZE FINDS THE NEXTP,WHICH IS MOST OFTEN USED IN
        THE STATE,AND DELETES THE STATEELEMENTS WHERE IT OCCURS*)
   label 10;
   var p:pointer;
     max,i,husk:integer;
   begin
     if options[21] then
      begin   write(blst,lf,' ','FCQ',lf,lf,'    UDGANG','  FREKVENS',lf);
        for i:=1 to fcqi do with fcq[i] do
        write(blst,ord(udgang),frekvens,lf);
        write(blst,lf,lf);
      end;
     maxnextp:=fcq[1].udgang;
     max:=fcq[1].frekvens;
     for i:=2 to fcqi do
     with fcq[i] do
     if frekvens >max then
      begin max:=frekvens; maxnextp:=udgang end;
 
     if md=4 then
      begin
        p:=begintilst;
        while p^.nextp<>maxnextp do p:=p^.derivp;
        husk:=p^.prodnr;
        (* THE LOOKAHEAD-SET OF PROD. <>HUSK' WILL BE DELETED *)
      end;
 
 
     while(begintilst^.nextp=maxnextp) and (begintilst^.mode=md) do
     begintilst:=begintilst^.derivp;
 
     p:=begintilst;
     repeat
       oldp:=p;
       repeat
         p:=p^.derivp;
         if p=nil then goto 10;
       until ( p^.nextp<>maxnextp) or (p^.mode<>md);
       10:
          oldp^.derivp:=p;
     until p=nil;
     if md=4 then md:=husk;
 
   end (* END OPTIMIZE *) ;
 
   procedure timecheck(a:alfa20);
   var m:dayfilemsg;
     i:integer;
     b:alfa;
     time:integer;
   begin
     time:=clock-mstime;
     mstime:=clock;
     m:='                      USED            MS';
     constval(time,b);
     for i:=1 to 10 do m[i+27]:=b[i];
     for i:=1 to 20 do m[i+1]:=a[i];
     msg(m);
   end; (* TIMECHECK *)
 
   procedure heapcheck(a:alfa20);
   var m:dayfilemsg;
     i:integer;
     b:alfa;
     function heap:integer;begin heap:=777 end;
     (* ASSEMBLY LANGUAGE ROUTINE TO RETURN *)
     (* ACTUAL SIZE OF HEAP .               *)
   begin
     m:=' HEAP                                   ';
     constval(heap,b);
     for i:=1 to 10 do m[i+30]:=b[i];
     for i:=1 to 20 do m[i+6]:=a[i];
     msg(m);
   end; (* HEAPCHECK *)
 
   procedure constcheck(a:alfa;c1,c2:integer);
   var m:dayfilemsg;
     b1,b2:alfa;
     i:integer;
   begin
     m:='                                        ';
     constval(c1,b1); constval(c2,b2);
     for i:=1 to 10 do m[i+1]:=a[i];
     for i:=1 to 10 do m[i+12]:=b1[i];
     for i:=1 to 10 do m[i+25]:=b2[i];
     msg(m);
   end; (* CONSTCHECK *)
 
   procedure writem(pnr,dot:integer);
   var t,i:integer;
   begin
     flush(blst);
     t:=0; nontwrit(prod[pnr].leftside,t);
     write(blst,' ::= '); t:=t+5;
     for i:=1 to prod[pnr].laengde do
     begin
       if i=dot then begin
          write(blst,' .  '); t:=t+4;
        end;
       if rhs[i+prod[pnr].start].symbol<=termg
        then outalf20(internrep[rhs[i+prod[pnr].start].symbol],t)
       else nontwrit(rhs[i+prod[pnr].start].symbol,t);
       write(blst,' ');
     end;
     if (dot=0) or (dot=prod[pnr].laengde+1) then write(blst,' .');
     flush(blst);
   end; (* WRITEM *)
 
   procedure ingrammar;
   label 111,10,555,13,7777;
   const maxopt=13;
   type
     chtype=(alfanum,special,sep);
     labelarr= (*packed*) array[1..100] of char;
     buftype=array[1..alf3] of char;
   var  buf:alfa;
     buffer:buftype;
     metasymbol: array[1..5] of char;
     mnemo: array [1..maxopt] of
     record opt:alfa;
        num:integer;
     end;
     m:          array[0..5] of alfa;
     alfav,metavar: alfa;
     eofflag:boolean;
     chgroup: array[char] of chtype;
     i: integer;

     function testch(ch1,ch2: char): boolean;
       (* USED BY TERMINPUT AND TERMINAL *)
     begin 
       testch:=((chgroup[ch1]=chgroup[ch2]) and (chgroup[ch2]<>sep))
       (*TRUE- IF CH1 AND CH2<>SEP AND IN SAME GROUP OF CHARS *)
       or
       (options[5] and (chgroup[ch1]<>sep) and (chgroup[ch2]<>sep));
       (*TRUE- IF OPTIONS[5] AND CH1,CH2<>SEP *)
     end; (*TESTCH*)
 
     procedure inch; forward;

     procedure pack(b:buftype;inx:integer; var a:alfa);
     var i:integer;
     begin
	for i:=1 to alfalength do a[i]:=b[inx+i-1]
     end;
 
     procedure terminput;
     label 22,10,11,12,14,100;
       (*INDLAESNING AF TERMINALER ADSKILT MED SPACE EL. EOL
         OG AFSLUTTET MED METASYMBOL 4 *)
     var i,j: integer;
       c: array[1..alfal20] of char;
       runp,gemp:termpointer;
       alfac,emptyalfa,namealfa,cstalfa,stringalfa,erroralfa: alfa20;
       stoperror: boolean; chh: char;

 
       procedure inputerror(nr:integer);
         (* ERROR-PROCEDURE LOCAL FOR TERMINPUT*)
       begin
	  if odd(nr) then writeln(blst);
         case nr of
            1 : write(blst,'*****  END OF FILE ENTCOUNTERED.');
            2 : begin writeln(blst); write(blst,'  ***  TERMINAL DUPLICATED.');
               end;
            3 : consterror('TERMINPUT ','CONST12   ',const12);
            6 : begin stoperror:= true;
		   repeat inch until ch=' '; writeln(blst);
		   write(blst,'  ***  TERMINAL MORE THAN ',alfal20:2,' CHARACTERS.');
		   writeln(blst);
               end;
            7 : consterror('TERMINPUT ','CONST2    ',const2);
            4 : begin stoperror:= true;
		   repeat inch until ch=' '; writeln(blst);
                 write(blst,'  ***  ILLEGAL CONCATENATION.');
	       end;
	   8  : begin stoperror:=true; writeln(blst);
		    writeln(blst,'*** Illegal m5 in terminput');
		end;
	   9  : begin stoperror:=true; writeln(blst);
		    writeln(blst,'*** Illegal character combination in terminal');
		end;
	   10 :  begin stoperror:=true; writeln(blst);
		    writeln(blst,'*** Empty terminal symbol');
		 end;
         end;
         (*  VED ULIGE NR. HELT UD- ELLERS HUSK FEJLEN    *)
         write(blst,lf,'          ');
         if odd(nr) then stop(0);
       end;
 
       procedure fresh;
         (* NY CELLE I TERMTREE ALLOCERES OG INITIALISERES   *)
       begin new(termtop);
         if termtop=nil then inputerror(3);
         with termtop^ do
         begin ok:= false; tegn:=ch;intern:=-1;
           niveaup:= nil; higherp:= nil;
         end;
         trmax:=trmax+1; (*USED IN PROCEDURE FINALPARSER*)
       end;

       (************** OLM: 11.4.93 ********)
       var noNewTerm: boolean; (* see below *)
       function newTermNo:integer; 
         (* allocate new terminal number *)
         begin if noNewTerm then (* skip *)
               else begin
                 if termantal<const2 then termantal:=termantal+1 
                 else inputerror(7);
               end;
               noNewTerm:=false; 
               newTermNo:=termantal
         end;

      (******** end OLM 11.4.93 **********)
     begin
       (*   INITIALISERING   *)
       noNewTerm:=false; (* OLM: 11.4.93 *)
       trmax:=0; (*SEE PROCEDURE FRESH*)
       for chh:= minch to maxch do
       with entry[chh] do
       begin  termp:= nil; ok1:= false; intern1:=-1 end;
       errorval:=-1 ;
          (* NB: 0 is -BOBS-EOI- which is the last terminal on input *)
       erroralfa:= '_ERROR_             ';
       emptyvalue:= -1;
       emptyalfa:= '_EMPTY_             ';
       nameval:= -1;
       namealfa:=  '_NAME_              ';
       cstval:= -1;
       cstalfa:=   '_KONST_             ';
       stringval:= -1;
       stringalfa:='_STRING_            ';
       stringch:=' ';
       gl:= nil; gn:= nil; gc:= nil; gs:=nil; go:=nil;
       termantal:=1;
       stoperror:= false;
       (* LQKKE SAALAENGE FLERE TERMINALER   *)
       ch:=s;
       while ch=' ' do inch;
       while ch<>metasymbol[4] do
       begin if ch <> metasymbol[5] then inputError(8);
	  inch;
	  i:=0;
	  (*   LQKKE -SAALAENGE NAESTE CHAR-VAERDI GODKENDT   *)
	  repeat
	     if ch = metasymbol[5] then
	     begin inch;
		if ch <> metasymbol[5] then goto 100;
	     end;
	     if (i > 0) and not testch(c[i],ch) then inputerror(9);
	     if (i=alfal20) and not options[4] then inputerror(6);
	     if i < alfal20 then
	     begin i:=i+1;
		c[i]:=ch;
	     end;
	     (*  NAESTE CHAR-V. SQGES I ALLEREDE OPBYGGET TRAE   *)
	     if i > 1 then
	     begin
	      if i=2 then
		with entry[c[1]] do
		begin if termp=nil then
		begin fresh;termp:=termtop;
		   gemp:= termtop; goto 10;
		end else runp:= termp;
		end else
		   with gemp^ do
		   begin if higherp=nil then
		   begin fresh; higherp:=termtop;
		      gemp:= termtop; goto 10;
		   end else runp:= higherp;
		   end;
		while runp^.tegn<>ch do
		   with runp^ do
		   begin if niveaup=nil then goto 11;
		      runp:= niveaup;
		   end;
		gemp:= runp;
		goto 10; (* this code was written by BBK *)
		11: (*  CHAR NOT FOUND - NY CELLE OPRETTES   *)
	        begin fresh;
		   runp^.niveaup:= termtop;
		   gemp:= termtop;
	        end;
	     end;
	     10: inch;
	  until false;
	  100: if i = 0 then inputerror(10);
	  (* ch = ' ' or m[4] *)
	  if ((ch=' ') or (ch=metasymbol[4])) then
	  begin
	     if options[3] and (ch=' ') then
	     begin inch;
		if ch= metasymbol[1] then
		begin inch; noNewTerm:=true; (*OLM 11.4.93:??*) goto 12 end;
	     end;
            (* NY TERMINAL REGISTRERES - TEST FOR GENGANGERI   *)
          (* OLM: 11.4.93
           *if termantal<const2 then termantal:=termantal+1 else inputerror(7);
           *)
            12: (*GOTO 12 LIG NY TERMINAL IKKE NYT NUMMER*)
                if i=1 then
                 with entry[c[1]] do
                 begin 
                   if ok1 then begin  inputerror(2); goto 14 end
                   else begin
		      intern1:=newTermNo;
                      (*writeln(blst,intern1);*)
                      ok1:= true;
                   end
                 end else
                 with gemp^ do
                 begin
                   if ok then begin inputerror(2); goto 14 end
		   else begin
                      intern:= newTermNo;
                      (*writeln(blst,intern);*)
                      ok:= true;
                   end
                 end;
            (* OLM 11.4.93: 
	     * before this correction, each occurence of a terminal symbol
             * gave rise to a new terminal number. In addition dublicate
	     * occurrences of NAME, KONST, etc., implied that gn, gc, etc
	     * was set to refer to the last allocated cell (via termtop).
             * In case of dublicate NAME, etc. termtop did not refer to
             * to the last char of e.g. NAME. The last char in NAME is referred
	     * by gemp.
      	     * The correction avoids a new terminal number for dublicate
             * terminals. In addition a dublicate terminal is not tested
             * for being NAME, etc.
             *)
            (* TERMINAL PAKKES OG GEMMES- TEST FOR EVT. EMPTY-TERMINAL  *)
            for j:=1 to i do alfac[j]:=c[j];
            for i:=i+1 to alfal20 do alfac[i]:= ' ';
            if erroralfa=alfac then
            begin errorval:=termantal; go:=termtop; end
            else if emptyalfa= alfac then
            begin emptyvalue:=termantal;gl:=termtop end
            else if namealfa=alfac then
            begin nameval:=termantal;gn:=termtop end
            else if cstalfa=alfac then
            begin cstval:=termantal;gc:=termtop end
            else if stringalfa=alfac then
            begin stringval:= termantal;gs:= termtop end;
            internrep[termantal] := alfac;
	   14: (* OLM 11.4.93 *)
          end else inputerror(4);
         22: while ch=' ' do inch;
       end;
       inch;
       internrep[0]:= 'BOBS-GO             ';
       internrep[1]:= '-EOF-               ';
       if options[1] then outterminal;
       if stoperror then stop(2);
     end;
     (*----------------------------------------------------------*)
 
 
 
     procedure gramerror(a : integer);
     forward;
 
 
     (*----------------------------------------------------------*)
     procedure terminal;
       (* KALDES MED CHAR-VALUE I CH; LEVERER I TERMREP DEN INTERNE
          REPRAESENTATION AF NAESTE TERMINAL PAA INPUT-
          HVIS EN FINDES- ELLERS -1 *)
     label 66,77,88;
     var
       buf: array[1..alf3] of char;
       gemp,runp: termpointer;
 
       procedure inputerror(nr:integer);
         (*  ERROR-PROC. LOCAL FOR TERMINAL    *)
       begin
	  errorboo:=true; error2:=true; error:=true; termrep:=0;
	  writeln(blst);
	  case nr of 
	    1 : begin 
		  writeln(blst,'*** Empty terminal symbol');
		  writeln(blst);
		  gramerror(23)
		end;
	   2 : begin
		  writeln(blst,'*** Fatal system error: illegal call of terminal');
		  writeln(blst);
		  gramerror(23)
		end;
	   3 : begin 
		  writeln(blst,'***  Illegal terminal symbol');
		  writeln(blst);
		  gramerror(23);  (*GOTO88;*)
              end;
         end;
       end;
 
       function metach(ch:char):boolean;
       var
         b:boolean;
         j:integer;
       begin  b:= false;
         for j:=1 to 4 do b:=(b or (ch=metasymbol[j]));
         metach:= b;
       end; (*METACH*)
 
     begin
       (* IN DEC 10 PASCAL, JUMPS OUT OF A PROCEDURE ARE NOT ALLOWED *)
       (* INPUTERROR(6) SHOULD TERMINATE BY GOTO 88; THIS IS INSTEAD *)
       (* SIMULATED BY LABEL 77 AND GOTO 77 *)
	while ch=' ' do inch;
	if ch <> metasymbol[5] then inputerror(2);
	inch; i:=0;
	repeat
	   if ch = metasymbol[5] then
	   begin
	      inch;
	      if ch <> metasymbol[5] then goto 66;
	   end;
	   if i < (alf3-1) then begin  i:=i+1; buf[i]:= ch; end;
	   if i = 1 then else
	      begin
		 if i = 2 then
		    with entry[buf[1]] do
		       if termp=nil then goto 77 else runp:= termp
		 else
		    with gemp^ do
		       if higherp=nil then goto 77 else runp:= higherp;
		 while runp^.tegn<>ch do
		    with runp^ do
		    begin
		       if niveaup=nil then goto 77;
		       runp:= niveaup;
		    end;
		 gemp:= runp;
	      end;
	   inch;
	until false;
	66:

       (* OPSAMLET ALFA-VAERDI TESTES SOM TERMINAL      *)
	(* writeln(blst); write(blst,'Terminal: "');
	 * for j:=1 to i do write(blst,buf[j]); write(blst,'"=');
	 *)
	if i = 0 then inputError(1);
	if i = 1 then
        with entry[buf[1]] do
	   if ok1 then termrep:= intern1 else goto 77 else
	      with gemp^ do
		 if ok then termrep:= intern else goto 77;
	goto 88;
	77: inputerror(3);
	88: (*writeln(blst,termrep)*);
     end;
     (* SLUT PROCEDURE TERMINAL     *)
     (*----------------------------------------------------------*)
 
 
     procedure space;
     forward;
 
 
     procedure nterminal(var meta : char);
     forward;
 
     procedure fejl( i : integer);
     begin write(blst,lf);
        if  not (i in [8,9,12,13]) then write(blst,lf); write(blst,'  ***  ');
       case i of
          1  : write(blst,' EOF ENCOUNTERED IN READING THE GRAMMAR');
 
          2  : write(blst,' = EXPECTED IN GOALSYMBOLCARD');
          3  : write(blst,' GOALSYMBOLCARD EXPECTED');
          4  : write(blst,' EMPTY IS NOT THE ONLY SYMBOL IN RIGHTSIDE');
          5  : write(blst,' ERROR(S) IN METASYMBOLS');
          6  : write(blst,' METASYMBOLCARD EXPECTED');
          7  : consterror('INGRAMMAR ','CONST2    ',const2);
          8  : write(blst,' AN ALTERNATIVE ON A RIGHTSIDE HAS NO SYMBOLS');
          9  : 
        write(blst,' THE STRING-ESCAPE CHAR MUST APPEAR IN THE LIST OF TERMINALS');
          10 : write(blst,' TWO OR MORE METASYMBOLS ARE ALIKE');
          17 : write(blst,' ERROR(S) IN STRINGCARD ');
          18 : write(blst,' TOO LONG NONTERMINAL ');
          19 : write(blst,' TOO LONG RIGHTSIDE (MAX 15) ');
 
          11 : write(blst,' INPUT FILE EMPTY ');
          12 : write(blst,' METASYMBOL 3 APPEARS IN WRONG CONTEXT');
          13 : write(blst,' METASYMBOL 1 WAS EXPECTED');
          14 : consterror('INGRAMMAR ','CONST11   ',const11);
          15 : write(blst,' ILLEGAL CHARACTER IN OPTION LIST');
          16 : write(blst,' OPTION NUMBER IS NOT DEFINED');
          20 : write(blst,' METASYMBOL 4 WAS EXPECTED IN COMMENT-DEFINITION');
          21 : write(blst,' METASYMBOL 4 WAS EXPEXTED AFTER COMMENT-DEFINITION');
          22 : write(blst,' COMMENT =  WAS EXPECTED ') ;
          23 : write(blst,' NONTERMINAL = ... M4 ... M4  was expected');
	  24 : write(blst,' SYMBOLS in COMMENTS DEFINITION MUST BE ENCLOSED BY',
                   ' METASYMBOL 5 (") AS IN COMMENT="...";"..."')
 
       end;
       if i in [1,2,3,5,6,10,11] then 
            writeln('!!!!! ERROR(S) IN INPUT                      ');
	writeln(blst);
	errorboo:=true;
	if i=4 then nboo2:=true else
        if  not (i in [8,9,12,15,16,13,18,19]) then stop(0);
       options[8]:=false;
     end;
 
 
     procedure gramerror;
     begin
       if a < 23 then (*NOT CALLED FROM TERMINAL*) fejl(a);
       while metasymbol[4]<>s do space;
       space;
     end;
 
 
     procedure goalsymb;
       (* PROCEDUREN LAESER GOALSYMBOLKORTET*)
     var i: integer;
     begin
       for i:=1 to alfalength do
       begin
         buffer[i]:=s;
         space;
       end;
       pack(buffer,1,alfav);
       if alfav='GOALSYMBOL' then
        begin
          if s='=' then
           begin
             nterminal(metasymbol[4]);
             goalhusk:=count;
           end else fejl(2);
        end else fejl(3);
       goaltest:=true;
       nboo1:=false;
       space;
     end;
 
 
     procedure goalprod;
       (* INDSAETTELSE AF GOALPRODUKTIONEN*)
     var i: integer;
     begin
       (* INDSAETTELSE AF HQJRESIDE*)
       huskp:=point;
       rhs[point].basisl:=3;
 
       newelm(point,'GOALPROD  ');  rhs[point].symbol:=0;
 
       newelm(point,'GOALPROD  ');
          with rhs[point] do
          if goaltest then symbol:=goalhusk else symbol:=count;
       newelm(point,'GOALPROD  ');  rhs[point].symbol:=1;
       for i:=1 to 4 do
       with rhs[huskp] do
       begin
         allocate(huskp);
         link:=rhsnil;
         parserp:=nil;
       end;
       goalboo:=false;
       point:=huskp;
     end;
 
    procedure nontmeta;
    (* read the terminal symbols used to delimit nonterminals*)
    (* when parsing sentential forms *)
    var buf: (*packed*) array[1..12] of char; i: integer;
    begin
       for i:= 1 to 12 do
         begin buf[i]:=s; space end;
       if  buf='NONTERMINAL=' then
        begin ch:=s; terminal; nontl:=termrep;
           if ch<> ' ' then s:=ch else space;
           if ch<> metasymbol[4] then gramerror(23)
           else begin
             space; ch:=s; terminal; nontr:=termrep;
             if ch<> ' ' then s:=ch else space;
             if s<> metasymbol[4] then gramerror(23)
             else space;
        end end else gramerror(23);
     end;
 
     procedure comment ;
       (* THE PROCEDURE READS THE COMMENT CARD IF ANY *)
     var
       buf : (*packed*) array[1..8] of char ;
       i: integer;
     begin
       for i:=1 to 8 do
       begin
         buf[i]:=s ;
         space ;
       end ;
       if buf='COMMENT=' then
        begin
          ch:=s ;
          terminal ;
          combegin:=termrep ;
          if ch<> ' ' then s:=ch else space ;
          if s<> metasymbol[4] then
           gramerror(20)
          else
           begin
	      i:=1 ; space ;
	      if s <> metasymbol[5] then fejl(24);
	      space;
	      while ((s<>metasymbol[5]) and (i<=alfalength)) do
	      begin
		 comend[i]:=s;
		 space ;
		 i:=i+1 ;
	      end ;
	      comlength:=i-1 ;
	      space;
	      if s<> metasymbol[4] then gramerror(21)
             else space ;
           end ;
        end
       else
        gramerror(22) ;
     end ;
 
 
     procedure dumpnonterminternrep;
     begin
       if options[6] then
        begin write(blst,lf,lf,lf);
          write(blst,' A LIST OF NONTERMINALS WITH INTERNAL REPRESENTATION ');
          write(blst,lf,lf);
          noword:=false;
          nterminal(metasymbol[3]);
        end;
     end;
 
     procedure inch;
     begin
       if eof(input) then
       begin ch:= ' ';
             if eofflag then fejl(1) else goto 7777;
       end else
        if eoln(input) then
        begin
          if options[8]=false then begin writeln(blst); write(blst,'     '); end;
          readln; ch:=' ';
        end else
        begin read(ch);
          if options[8]=false then write(blst,ch);
        end;
     end;(*INCH*)
 
     procedure space;
     begin
       repeat
         inch;
       until ch <> ' ';
       s:=ch;
     end;
 
 
     procedure laes(var a : integer);
     var i: integer;
     begin
       i:=1;
       while(i<=a) do
       begin
         buffer[i]:=s;
         i:=i+1; space;
       end;
       if i<12 then for i:=i to 12 do buffer[i]:=' '
     end;
 
 
     procedure stringdef;
     var
       buf: (*packed*) array[1..9] of char;
       i: integer;
     begin
       for i:=1 to 9 do
       begin
         buf[i]:=s;
         space;
       end ;
       if buf='STRINGCH=' then stringch:=s  else fejl(17);
       if entry[stringch].ok1=false then fejl(9);
       space;if s=metasymbol[4] then space;
     end; (*SLUT PAA STRING *)
 
 
 
 
 
 
     procedure nterminal;
     var
       alfa1,alfa2,alfa3 :alfa;
       boo : boolean;
       i:integer;
 
       procedure nextword;
       label 26;
       var i: integer;
       begin
         space;
         if s=metasymbol[3] then
          begin gramerror(12); error1:=true;
            goto 26;
          end;
         i:=1;
         while s<> meta do
         begin
           if i <= 30 then buffer[i]:=s;
           space; i:=i+1;
         end;
         for i:=i to 30 do buffer[i]:=' ';
         pack(buffer,1,alfa1);
         pack(buffer,11,alfa2);
         pack(buffer,21,alfa3);
         26:
            (*END NEXTWORD*)
       end;
 
 
 
       procedure udord(p:pointer1);
         procedure visitnode(p:pointer1);
         begin
           with p^ do write(blst,' ',word1,word2,word3);
           write(blst,' INTERNAL VALUE'); write(blst,' ',p^.nontermvaerdi,lf);
         end;
 
       begin if p<>nil then
          begin udord(p^.llink);
            visitnode(p);
            udord(p^.rlink);
          end;
       end;
 
 
       procedure indord;
       begin boo:=true; dynp:=first;
         while((dynp<>nil) and boo) do
         with dynp^ do
         if ((alfa1=word1) and (alfa2=word2) and (alfa3=word3)) then
          begin(*ORDET VAERET FQR*)
            boo:=false;
            count:=nontermvaerdi;
            if venstreboo then
             begin
               i:=1;(*UNDERSQGE OM VSIDE VAERET FQR*)
               while (i<k) and (husk[i]<>count) do i:=i+1;
               if (i<k) then rhs[lefthelp[count]].link:=point;
               (*HVIS VAERET FQR DA I<K POINTER SAETTES*)
             end;
          end else
          begin last:=dynp;
            if (alfa1<word1) then dynp:=llink else
             if (alfa1=word1) and (alfa2<word2) then dynp:=llink else
              if (alfa1=word1) and (alfa2=word2) and (alfa3<word3)
              then dynp:=llink else
               dynp:=rlink;
          end;
         if boo then
          begin new(statp); if statp=nil then fejl(14);
            with statp^ do
            begin word1:= alfa1; word2:=alfa2;
              word3:=alfa3;
              llink:=nil;
              rlink:=nil;
              nontermvaerdi:=internv; count:=internv;
              if internv >= const2 then fejl(7);
              internv:=internv+1;
              husknonterm[count].nontermp:=statp;
            end;
            with last^ do
            if (word1>alfa1) then llink:=statp else
             if (word1=alfa1) and (word2>alfa2) then llink:=statp else
              if (word1=alfa1) and (word2=alfa2)  and (word3>alfa3)
              then llink:=statp else rlink:=statp;
          end;
       end;
 
     begin
       if noword then
        begin
          if nontermboo then
           begin
             nextword; new(first);
             with first^ do
             begin word1:=alfa1;
               word2:=alfa2; word3:=alfa3;
               llink:=nil;
               rlink:=nil;
               count:=internv;
               husknonterm[count].nontermp:=first;
               nontermboo:=false;
               nontermvaerdi:=internv;
               internv:=internv+1;
             end;
           end else begin nextword; if (errorboo=false) then indord  end;
        end else udord(first);
     end;
 
 
     procedure metasymb;
       (* METASYMB LAESER ET KORT MED FQLGENDE UDSEENDE : *)
       (*  METAVARIABLE M1=   M2=  M3=  M4=  M5= *)
     begin
       count:=11; laes(count);
       pack(buffer,1,alfav);
       if alfav=metavar then
        begin (*METAVARIABLE GENKENDT*)
          j:=1;
          while j <= 5 do
          begin
            count:=3; laes(count);
            pack(buffer,1,alfav);
            if m[j]=alfav then
             begin
               metasymbol[j]:=s;
               i:=j;
               if i>1 then
                while i>1 do
                begin
                  i:=i-1;
                  if s=metasymbol[i] then fejl(10);
                end;
               j:=j+1;
             end else fejl(5);
            if j <= 5 then space;
          end
        end else fejl(6);
     end;
 
 
     procedure init;
     var c: char; i: integer;
     begin
       mnemo[1].opt:='NYLALR    ';mnemo[1].num:=27;
       mnemo[2].opt:='PROD      ';mnemo[2].num:=16;
       mnemo[3].opt:='TILSTAND  ';mnemo[3].num:=17;
       mnemo[4].opt:='VHRECURS  ';mnemo[4].num:=25;
       mnemo[5].opt:='TIMECHECK ';mnemo[5].num:=47;
       mnemo[6].opt:='LOOKBACK  ';mnemo[6].num:=21;
       mnemo[7].opt:='LALR1     ';mnemo[7].num:=51;
       mnemo[8].opt:='LALR2     ';mnemo[8].num:=52;
       mnemo[9].opt:='LALR3     ';mnemo[9].num:=53;
       mnemo[10].opt:='PARSER    ';mnemo[10].num:=15;
       mnemo[11].opt:='HEAPCHECK ';mnemo[11].num:=46;
       mnemo[12].opt:='EMPTY     ';mnemo[12].num:=36;
       mnemo[13].opt:='LRCOND    ';mnemo[13].num:=35;
       eofflag:=true;
       for c:=minch to maxch do chgroup[c]:=special;
       for c:='A' to 'Z' do chgroup[c]:=alfanum;
       for c:='a' to 'z' do chgroup[c]:=alfanum;
       for c:='0' to '9' do chgroup[c]:=alfanum;
       chgroup['_']:=alfanum;
       chgroup[' ']:=sep;
       error:=false;
       (* the following is done in the main-program
          FOR i:=1 TO const18 DO options[i]:=false;  *)
 
       combegin:=0 ;
       comlength:=1 ;
       for i:=1 to alfalength do comend[i]:=' ' ;
       linx:=0; prodseqno:=0;
       nolooki:=0; (* INDEX TO NOLOOK *)
       nontl:=-1; nontr:=-1;
     end; (*INIT*)
 
     function findlabel(var lab:labelarr; labellength: integer):integer;
     var i,j,k,no:integer;
       p:pointer2;
       boo:boolean;
 
       procedure enter(no:integer);
       var i:integer;
       begin
         nolook[nolooki]:=no;
         i:=0;
         while nolook[i]<>no do i:=i+1;
         if i=nolooki then nolooki:=nolooki+1;
       end;
 
     begin
       boo:=false; no:=0;
       for i:=nontstart+1 to internv - 1 do
       begin
         p:=help[i].rightp;
         while p<>rhsnil do
         begin
           if (rhs[p].length=labellength) or options[33]
            then begin
              boo:=true;
              k:=rhs[p].first;
              if options[33] then begin
                 while labelbuf[k]<>' ' do k:=k+1;
                 k:=k+1;
               end;
              if (rhs[p].length-(k-rhs[p].first))=labellength then
               begin
                 for j:=1 to labellength do
                 boo:=(labelbuf[k+j-1]=lab[j]) and boo;
                 if boo then begin
                    findlabel:=rhs[p].first;
                    enter(rhs[p].first);
                    no:=no+1;
                  end;
               end
            end;
           p:=rhs[rhs[p].basisl+p].link;
         end;
       end;
       if no=0 then begin
          write(blst,lf,'LABEL NOT FOUND: ',lab:labellength,lf);
          findlabel:=-1;
        end;
       if no>1 then begin
          write(blst,lf,'LABEL DECLARED MORE THAN ONCE: ',
          lab:labellength,lf);
          findlabel:=-1;
        end;
     end;
 
     procedure readlabel(pt:integer);
     var lo,i:integer; sa:alfa;
     begin prodseqno:=prodseqno+1; rhs[pt].seqno:=prodseqno;
       if options[33] or options[34] then
        begin  lo:=linx;
          rhs[pt].first:=lo;
          if options[33] then
           (* use the input seqNo as the first part of the label *)
           begin
             if linx+15>const19
             then consterror('READLABEL ','CONST19   ',const19);
             constval(prodseqno,sa); i:=2;
             while sa[i]<>')' do
             begin labelbuf[linx]:=sa[i];
               i:=i+1; linx:=linx+1;
             end;
             labelbuf[linx]:=' '; linx:=linx+1;
           end;
          if options[34] then
           (* READ THE LABEL GIVEN, AND STOP ON THE FIRST OCURRENCE OF
              METASYMBOL 1 *)
           begin space;
             while s<> metasymbol[1] do
             begin labelbuf[linx]:=s;
               linx:=linx+1; inch; s:=ch;
               if (linx+1)>=const19
               then consterror('READLABEL ','CONST19   ',const19);
             end;
           end;
          if (linx-lo)>const20 then
           begin lo:=linx;
             writeln(blst,' *** A PRODUCTION LABEL MUST NOT EXCEED',
                      const20:4,' CHARS');
           end;
          rhs[pt].length:=linx-lo;
        end;
     end; (*READLABEL*)
 
     procedure readspecialpurposeinput;
     var lab: labelarr;
       a:alfa;
       fl:integer;
       length:integer;
 
       procedure readalfa(var a:alfa);
       var i:integer;
       begin
         i:=1;
         space;
         a:='          ';
         while s in ['A'..'Z','0'..'9'] do
         begin
           if i<= 10 then begin
              a[i]:=s;
              i:=i+1;
            end;
           inch;
           s:=ch;
         end; (* WHILE *)
       end; (* READALFA *)
 
       procedure readlabel(var lab: labelarr; var l:integer);
       var i:integer;
 
         function valid(ch:char):boolean;
         begin
           valid:=(ch in ['A'..'Z','a'..'z','0'..'9','-','/','_','*'])
	      (* OR
           ((ch >= chr(ord('A')+40B)) AND (ch <= chr(ord('Z')+40B))); *)
         end (* valid *);
 
       begin
         i:=1;
         space;
         ch:=s;
         while valid(ch) do
         begin
           lab[i]:=ch;
           i:=i+1;
           inch;
         end;
         l:=i-1;
       end;
 
     begin
       eofflag:=false;
       readalfa(a);
       eofflag:=true;
       allnolook:=false;
       if a='NOLOOKAHEA' then
        begin
          ch:=',';
          while ch<>'.' do
          begin
            readlabel(lab,length);
            if (lab[1]='*') and (length=1) then allnolook:=true else
             fl:=findlabel(lab,length);
            while ch=' ' do inch ;
            if not ((ch=',') or (ch='.')) then begin writeln(blst,',OR. EXPECTED');
               s:='.';
             end;
          end;
        end;
     end; (* READ-SPECIAL-PURPOSE-INPUT *)
 
   begin init;
write(blst,'************ A LIST OF INPUT WITH POSSIBLE ERRORMESSAGES  ************');
     write(blst,lf,lf,'    ');
     space; (* READ FIRST NON-BLANK CHARACTER ON INPUT*)
     if s='O' then
      (* OPTIONS INDLAESES *)
      begin
        repeat   if s='M' then begin fejl(15); goto 111 end;
          space;
        until s='(';
        space;
        repeat
          while s=',' do space;
          if (s >= '0') and (s <= '9') then
           begin
             optno:=0;
             repeat
               optno:=optno*10+ord(s)-ord('0');
               space;
             until (s<'0') or (s>'9');
             if optno>const18 then fejl(16)
             else options[optno]:=not options[optno];
           end else
           if s<>')' then
            begin
              for i:=1 to 10 do if s in ['A'..'Z','0'..'9']
               then begin
                 buf[i]:=s; space;
               end
              else buf[i]:=' ';
              if buf='          '
               then
               repeat if s='M' then goto 111;
                 space;
               until s=')'
              else begin
                 for i:=1 to maxopt do
                 if mnemo[i].opt=buf
                  then begin
                    options[mnemo[i].num]:=not options[mnemo[i].num];
                    goto 555;
                  end;
                 write(blst,lf,' UNKNOWN MNEMONIC ',buf,' - IGNORED',lf);
                 555: end;
            end;
        until s=')';
        space;
        111:
      end;
     (* SLUT PAA INDLAESNING AF OPTIONS *)
 
      metavar:='METASYMBOL';
      m[1]:='M1=       '; m[2]:='M2=       ';
      m[3]:='M3=       '; m[4]:='M4=       ';
      m[5]:='M5=       ';
     for i:=0 to const2 do
     begin
       (* INITIALISERING AF NONTERMHUSK*)
       husknonterm[i].rightboo:=false;
       husknonterm[i].leftboo:=false;
     end;
     for i:=0 to const2 do help[i].rightp:=rhsnil;
     emptyboo:=false; error1:=false;
     errorboo:=false; error2:=false;
     if s='M' then begin metasymb;space end else
      begin (*DEFAULT VAERDIER FOR METASYMBOLER *)
	 metasymbol[1]:='=';
	 metasymbol[2]:='|';
	 metasymbol[3]:='<';
	 metasymbol[4]:=';';
	 metasymbol[5]:='"';
	 write(blst,lf);
	 writeln(blst,' NO METASYMBOLS HAVE BEEN CHOSEN THE FOLLOWING ARE USED ');
	 writeln(blst,' M1== M2=| M3=< M4=; M5="'); write(blst,lf,' ',s);
      end;
 
     terminput; (*READ TERMINAL SYMBOLS *)
 
     k:=1; top:=1;
     termg:=termantal; venstreboo:=false;
     termantal:=termantal+1;
     nontstart:=termantal;
     help[nontstart].rightp:=top;
     termantal:=termantal+1;
       if termantal>=const2 then consterror('INGRAMMAR ','CONST2    ',const2);
     internv:=termantal;
     goalhusk:=termantal; (*this should be the goalsymb if no GOALCARD is def*)
     nontermboo:=true;
     empty:=127; error3:=false;
     noword:=true;
     space;
     point:=top;
     goaltest:=false;
     nboo1:=true; nboo2:=false;
     while s in ['G','S','C','N'] do
     case s of
        'G' : goalsymb;
        'S' : stringdef;
        'C' : comment;
        'N' : nontmeta;
     end ;
     goalboo:=true;
     13 : while s<>metasymbol[4] do
          begin
             firstboo:=true; tal:=0;
             if s='M' then
              begin (* METASKIFT*)
                 metasymb;
              end else
              begin
                if s<>metasymbol[3] then
                begin
                  gramerror(12);goto 13 ;
                end else
                begin
                  (* NY VENSTRE SIDE*) venstreboo:=true;
                  nterminal(metasymbol[3]);
                  if error1 then begin error1:=false; goto 13 end;
                  husk[k]:=count;
                  k:=k+1;
                  if goalboo then goalprod;
                  husknonterm[count].leftboo:=true;
                  if help[count].rightp =rhsnil then help[count].rightp:=point;
                  rhs[point].parserp:=nil;
                  rhs[point].link:=rhsnil;
                  helpp:=point; huskp:=point;
                  newelm(point,'INGRAMMAR ');
                end;
               space; venstreboo:=false;
               if s<>metasymbol[1] then
                begin gramerror(13);
                  goto 13 ;
                end else
                begin readlabel(helpp);
                  space;
                  10 : if s=metasymbol[2] then
                        begin (*END OF ALTERNATIVE/BEGINNING OF NEXT*)
                          if tal=0 then
                           begin gramerror(8); goto 13 end;
                          if emptyboo and (tal>1) then fejl(4);
                          emptyboo:=false;
                          rhs[helpp].basisl:=tal; tal:=0;
                          helpp:=point;
                          rhs[huskp].link:=point;
                          rhs[point].link:=rhsnil;
                          rhs[point].parserp:=nil;
                          newelm(point,'INGRAMMAR ');
                          readlabel(helpp);
                          space;
                          goto 10;
                        end   else
                        if s=metasymbol[3] then
                         begin (*READ NONTERMINAL*)
                           nterminal(metasymbol[3]);
                           if error1 then begin error1:=false; goto 13 end;
                           tal:=tal+1;
                           if tal>15 then
                            begin gramerror(19); goto 13 end;
                           husknonterm[count].rightboo:=true;
                           rhs[point].parserp:=nil;
                           rhs[point].link:=rhsnil;
                           rhs[point].symbol:=count;
                           huskp:=point; newelm(point,'INGRAMMAR ');
                           firstboo:=false;
                           space; goto 10;
                         end else
                         if s<>metasymbol[4] then (*READ TERMINAL*)
                          begin ch:=s; terminal;
                            if error2 then begin error2:=false; goto 13 end;
                            if emptyvalue=termrep then emptyboo:=true;
                            rhs[point].parserp:=nil;
                            rhs[point].link:=rhsnil;
                            tal:=tal+1;
                            if tal>15 then
                             begin gramerror(19); goto 13 end;
                            rhs[point].symbol:=termrep;
                            huskp:=point; newelm(point,'INGRAMMAR ');
                            firstboo:=false;
                            if ch<>' ' then s:=ch else space;
                            goto 10
                          end else
                          begin (*ENDOF ALTERNATIVE/NO MORE FOR THIS LHS*)
                            if tal=0 then
                             begin gramerror(8); goto 13 end;
                            if emptyboo and (tal>1) then fejl(4);
                            emptyboo:=false;
                            rhs[helpp].basisl:=tal;
                            lefthelp[husk[k-1]]:=huskp;
                          end;
                end
             end;
            space; emptyboo:=false;
          end;
      readspecialpurposeinput;
      writeln(blst); writeln(blst);
writeln(blst,'*********************************  END OF LIST ****************************');
      writeln(blst); writeln(blst);
      if errorboo then stop(2);

     if options[6] then dumpnonterminternrep;
     7777: end;
 
   procedure unused;
   var i: integer;
   begin page(blst);
 write(blst,'*******************************  GRAMMARCHECKS  **************************');
      writeln(blst);
     (* TEST AF OM DER EX NONTERMINALER ,DER KUN BRUGES PAA ENTEN HQJRE ELLER*)
     (* VENSTRE SIDE,HELE GRAMMATIKKEN CHECKES PAANAER GOALPROD. DENNE OVER - *)
 
     (*OVERSPRINGES,FINDES DER FEJL STANDSER PROGRAMMET *)
     if nboo1 then goalhusk:=husk[1];
     for i:=termantal to internv-1 do
     begin
       with husknonterm[i] do
       begin
         if  not (leftboo and rightboo) then
          begin
            with nontermp^ do
            if nontermvaerdi<>goalhusk then
             (* VITESTER KUN HVIS DET IKKE ER GOALSYMBOLET*)
             begin
               write(blst,' ',word1,word2,word3);
               if leftboo then write(blst,' APPEARS ONLY IN LEFTSIDE ')
               else write(blst,' APPEARS ONLY IN RIGHTSIDE');
               write(blst,lf);
               nboo2:=true;
             end
          end
       end
     end;
     nontslut:=internv-1;
     if nboo2 then
      stop(3)
     else
      begin
	 writeln(blst);
	 writeln(blst,'IT HAS BEEN CHECKED THAT ALL NONTERMINALS');
	 writeln(blst,'EXCEPT THE GOALSYMBOL APPEAR IN BOTH');
	 writeln(blst,'LEFT AND RIGHTSIDE OF A PRODUCTION');
	 writeln(blst);
      end;
   end; (* UNUSED *)

   procedure erasure;
   label 10,100;
   var
     lambda,m,ll,kk,k,i,j,l: integer;
     pq,oldp,p,pp,ppp: pointer2;
     boo,ok,slut: boolean;
   begin if not options[31] then goto 100; (* OBS. ERASURE IS NOT PERFORMED*)
     boo:=false;
     lambda:=emptyvalue;
     if lambda=0 then
     begin
	writeln(blst);
	writeln(blst,'IT HAS BEEN CHECKED THAT NO NONTERMINAL');
	writeln(blst,'CAN PRODUCE THE EMPTY STRING ');
	writeln(blst); 
        goto 100;
      end;
     ok:=false;
     for i:=nontstart to nontslut do
     help[i].status:=firsttim;
     10:
        for i:=nontstart to nontslut do
        (* I GENNEMLQBER ALLE VENSTRESIDER *)
        begin
          p:=help[i].rightp;
          while p<>rhsnil do
          begin
            pp:=p;
            ll:=rhs[p].basisl;
            allocate(p);
            if ll=1 then
             if rhs[p].symbol=lambda then
              (* EN HQJRESIDE ER GENKENDT SOM DEN TOMME STRENG *)
              begin
                ok:=true; (* OK ER TRUE HVIS EMPTY FINDES PAA EN HQJRE SIDE *)
                (*  PROD. A..LAMBDA FJERNES *)
                if pp=help[i].rightp then help[i].rightp:=rhs[p].link
                else rhs[oldp].link:=rhs[p].link;
                if help[i].status=firsttim then
                 begin
                   help[i].status:=finish;
                   for j:= nontstart+1 to nontslut do
                   begin
                     p:=help[j].rightp;
                     while p<>rhsnil do
                     begin
                       k:=rhs[p].basisl; l:=ord(p)+k;
                       pp:=p;
                       for m:=1 to k do
                       begin
                         allocate(pp);
                         symb:=rhs[pp].symbol;
                         if symb=i    then
                          begin
                            pq:=p;
                            newelm(point,'ERASURE   ');
                           (* ppp:=point; rhs[point].p !! truncation *)
                            if k=1  then
                             begin
                               rhs[point].basisl:=1;
                               newelm(point,'ERASURE   ');
                               rhs[point].symbol:=lambda;
                               rhs[point].parserp:=nil;
                               allocate(pq);
                             end else
                             begin
                               rhs[point].basisl:=k-1;
                               while ord(pq)<l do
                               begin
                                 allocate(pq);
                                 if pq<>pp then
                                  begin newelm(point,'ERASURE   ');
                                      rhs[point].parserp:=nil; (*TRUNC*)
                                    rhs[point].symbol:=rhs[pq].symbol;
                                  end;
                               end;
                             end;
                            rhs[point].link:=rhs[pq].link;
                            rhs[pq].link:=ppp;
                          end;
                       end;
                       oldp:=pp;
                       p:=rhs[pp].link;
                     end;
                   end;
                   goto 10; (* DER STARTES NU FORFRA MED GRAMMATIKKEN *)
                 end;
              end;
            for kk:=2 to ll do allocate(p);
            oldp:=p;
            p:=rhs[p].link;
          end;
        end;
     repeat
       slut:=true;
       for i:=nontstart to nontslut do
       begin
         p:=help[i].rightp;
         while p<>rhsnil do
         begin
           pp:=p; ll:=rhs[p].basisl;
           boo:=false;
           for kk:=1 to ll do
           begin
             allocate(pp); symb:=rhs[pp].symbol;
             if symb>termg then
              boo:=boo or (help[symb].rightp=rhsnil);
           end;
           if boo then
            begin if p=help[i].rightp then
               begin
                 pq:=rhs[pp].link;
                 help[i].rightp:=pq;
                 if pq=rhsnil then slut:=false;
               end
              else rhs[oldp].link:=rhs[pp].link;
            end else
            oldp:=pp;
           p:=rhs[pp].link;
         end;
       end;
     until slut;
     write(blst,lf,lf);
     if ok then
      begin
        writeln(blst,' THE GRAMMAR IS MODIFIED FOR ERASURE ');
	 writeln(blst,' I. E. NO NONTERMINAL CAN NOW PRODUCE THE EMPTY STRING');
      end else
      begin
        writeln(blst,' EMPTY HAS BEEN SPECIFIED AS A TERMINAL SYMBOL,');
        writeln(blst,' BUT IT HAS NOT BEEN USED ')
      end;
     writeln(blst);
     100:
   end;
 
(****************************************************************************)
(* ELIMINATED, since pascal compiler complains about too many local variables?
(* NOTE: internal comments herein have been substituted with "( *" eand "* )"
 procedure vhrecurs;
   label 10;
   var
     sn: record  case b: boolean of
               true: (p: integer ( * pointer2 * ) );
               false: (pvaerdi: integer);
            end;
     p2: pointer2;
     ( * OBS! In the original version of BOBS, sn.p is a pointer2 * )
     ( * This might not work in all Pascal implementations.       * )
     ( * P2 is used to coerse p * )

     boo: boolean;
     ii,ll,i,j,l: integer;
     start: integer;
     pt1s,ph1s: bitmatrix ;

     procedure writeheadsandtails;
     label 10,20;
     var
       nomoretails,nomoreheads: boolean;
       headsymb,tailsymb,symb,tael,i :integer;
     begin
       page(blst);
       write(blst,'A LIST OF PRODUCED 1-HEADS AND 1-TAILS FOR ALL NONTERMINALS');
       for i:=1 to 34 do write(blst,' '); write(blst,'I');
       for i:=1 to 45 do write(blst,' '); write(blst,'I',lf);
       write(blst,'              SYMBOL              I     TERMINAL TAILS');
       write(blst,lf);
       for i:=1 to 34 do write(blst,' '); write(blst,'I');
       for i:=1 to 45 do write(blst,' '); write(blst,'I');
       for symb:=nontstart+1 to nontslut do
       begin
         tael:=1; nomoreheads:=false; nomoretails:=false;
         headsymb:=0; tailsymb:=0;
         write(blst,lf,' ');
         for i:=1 to 33 do write(blst,'-'); write(blst,'I');
         for i:= 1 to 45 do write(blst,'-'); write(blst,'I');
         for i:=1 to 45 do write(blst,'-');
         write(blst,lf,' ');
         nontwrit(symb,tael);
         repeat
           if headsymb<>0 then write(blst,lf); ( * NO LINESHIFT FIRST TIME IN LOOP * )
           for tael:=tael+1 to 34 do write(blst,' ');      write(blst,'I');
           for i:=1 to 4 do ( * PRINT 4 HEADS IF THEY EXIST ELSE SPACES * )
           begin
             headsymb:=headsymb+1;
             while headsymb<nontstart do
             if(headsymb mod (setmax+1))in ph1s[symb].r[headsymb div (setmax+1)
] then goto 10
             else headsymb:=headsymb+1;
             nomoreheads:=true;
             10:
                if nomoreheads then write(blst,' ','    ')
                else write(blst,' ',internrep[headsymb]);
           end;
           write(blst,' ','I');
           for i:=1 to 4 do ( * PRINT 4 TAILS IF THEY EXIST ELSE SPACES * )
           begin
             tailsymb:=tailsymb+1;
             while tailsymb<nontstart do
             if(tailsymb mod (setmax+1))in pt1s[symb].r[tailsymb div (setmax+1)
] then goto 20
             else tailsymb:=tailsymb+1;
             nomoretails:=true;
             20:
                if nomoretails then write(blst,' ','    ')
                else write(blst,' ',internrep[tailsymb]);
           end;
           tael:=0;
         until nomoretails and nomoreheads;
       end;
       write(blst,lf,' ');
     end;
 
 
     procedure iterer(var matrix: bitmatrix);
     var
       n,up1,up2,nn,m,k,kk,l,i,j: integer;
       slut:boolean;
       gem,boo: rtypeset;
       trans: bitmatrix;
       fresh: rtype;
     begin
       n:=nontslut div (setmax+1);
       nn:=nontslut-n*(setmax+1);
       if options[19] then write(blst,lf,' NONTSLUT',nontslut,'        N',n); ( * trunc * )
 
 
       repeat up1:=setmax;  slut:=true;
         ( * MATRIXEN MATRIX TRANSPONERES  OVER I MATRIXEN TRANS * )
         k:=-1;
         for m:=0 to n do
         begin
           if m=n then up1:=nn;
           for kk:=0 to up1 do
           begin
             k:=k+1;
             j:=-1; up2:=setmax;
             for l:=0 to n do
             begin
               boo:=[]; if l=n then up2:=nn;
               for i:=0 to up2 do
               begin
                 j:=j+1;
                 if(kk in matrix[j].r[m]) then boo:=boo + [i];
               end;
               trans[k].r[l]:=boo;
             end;
           end;
         end;
 
         for i:=0 to const13 do fresh.r[i]:=[];
         ( * HER STARTES SELVE ITERERINGEN * )
         for k:=nontstart to nontslut do
         with matrix[k] do
         begin
           i:=-1;  up2:=setmax;
           for l:=0 to n do
           begin
             gem:=[]; if l=n then up2:=nn;
             for m:=0 to up2 do
             begin
               i:=i+1; boo:=[];
               for j:=0 to n do
               boo:=boo + (r[j] * trans[i].r[j]);
                if boo<>[] then gem:=gem + [m];
             end;
             fresh.r[l]:=gem;
           end;
           for j:=0  to n do
           begin
             gem:=r[j] + fresh.r[j];
             if gem<>r[j] then
              begin  r[j]:=gem;
                slut:=false;
              end;
           end;
         end;
       until slut;
     end;
   begin
     if options[25] then goto 10;
     i:=nontslut div (setmax+1);
     if i>const13 then
      begin
        write(blst,lf,lf,' CONST13',' MUST BE',i,lf);
        consterror('VHRECURS  ','CONST13   ',const13);
      end;
     for i:=0 to const2 do
     for j:=0 to const13 do
     begin
       ph1s[i].r[j]:=[];
       pt1s[i].r[j]:=[];
     end;
     with sn do
     for i:=nontstart to nontslut do
     begin
       p:=help[i].rightp;
       while p<>rhsnil do
       begin
         l:=rhs[p].basisl;
         p2:=p;
         allocate(p2);
         ll:=rhs[p].symbol;
         ii:=ll div (setmax+1);
         ph1s[i].r[ii]:=ph1s[i].r[ii] + [ll mod (setmax+1)];
         pvaerdi:=pvaerdi+l-1;
         ll:=rhs[p].symbol;
         ii:=ll div (setmax+1);
         pt1s[i].r[ii]:=pt1s[i].r[ii] + [ll mod (setmax+1)];
         p:=rhs[p].link;
       end;
     end;
     if options[20]  then
      begin
        matrixout(ph1s);
        matrixout(pt1s);
      end;
     iterer(ph1s);
     iterer(pt1s);
     if options[20]  then
      begin
        matrixout(ph1s);
        matrixout(pt1s);
      end;
     if options[18] then writeheadsandtails;
     boo:=false; l:=1;
     start:=nontstart+1;
     for ii:=start to nontslut do
     begin i:=ii div (setmax+1);
       if( ph1s[ii].r[i] * pt1s[ii].r[i] * [ii mod (setmax+1)])<>[] then
        begin
          boo:=true;
          write(blst,lf,' '); nontwrit(ii,l);
        end;
     end;
     if boo then
      begin
        writeln(blst);
        write(blst,' THE ABOVE STANDING NONTERMINALS ');write(blst,lf);
        write(blst,' ARE BOTH LEFT AND RIGHT RECURSIVE ');write(blst,lf);
        write(blst,' THE PROGRAM TERMINATES ');
        stop(3);
      end;
      writeln(blst);
      writeln(blst,'IT HAS BEEN CHECKED THAT NO NONTERMINAL'); 
      writeln(blst,'IS BOTH LEFT AND RIGHT RECURSIVE');
      writeln(blst);
     10:
   end;
*)
(********************* vhrecurs***************************)

   procedure termination;
   var
     p: pointer2;
     nonew,termboo: boolean;
     i,j,k: integer;
   begin
     for i:=nontstart to nontslut do help[i].term:=false;
     repeat
       nonew:=true;
       for i:=nontstart to nontslut do
       if ( not help[i].term)then
        begin
          p:=help[i].rightp;
          while p<>rhsnil do
          begin
            k:=rhs[p].basisl; termboo:=true;
            for j:=1 to k do
            begin
              allocate(p);
              with rhs[p] do
              if symbol>termg then termboo:=termboo  and  (help[symbol].term);
            end;
            if termboo then
             begin
               nonew:=false;
               help[i].term:=true; p:=rhsnil;
             end else p:=rhs[p].link;
          end;
        end;
     until nonew;
     termboo:=false;
     k:=0;
     for i:=nontstart+1 to nontslut do
     if(help[i].rightp<>rhsnil) and ( not help[i].term) then
      begin
        write(blst,lf,lf,' ');  nontwrit(i,k);
        termboo:=true;
      end;
     if termboo then
      begin write(blst,lf,lf);
        write(blst,' THE ABOVE STANDING NONTERMINALS CANNOT PRODUCE');write(blst,lf);
        write(blst,' A STRING OF ONLY TERMINAL SYMBOLS ');
        stop(3);
      end else
      begin writeln(blst);
        writeln(blst,'IT HAS BEEN CHECKED THAT ALL NONTERMINALS CAN');
        writeln(blst,'PRODUCE A STRING OF ONLY TERMINAL SYMBOLS');
	writeln(blst)
      end;
   end;
 
 
 
 
   procedure idogfjern(b:boolean);
   var
     boo1,boo2,boo3,boo4,fjboo : boolean ;
     function fjernkaede(var t:boolean) : boolean ;
     var
       i,k,l,m,n,s,fjern,indsat :integer ;
       j : pointer2 ;
       procedure fjskriv ;
       var
         z : integer ;
       begin
         z:=1 ;
         write(blst,' ') ;
         nontwrit(fjern,z) ;
         write(blst,'  HAS BEEN SUBSTITUTED BY  ') ;
         nontwrit(indsat,z) ;
         write(blst,lf) ;
       end ;
 
     begin
       fjernkaede:=false ;
       k:=nontslut ;
       i:=nontstart-1 ;
       repeat
         i:=i+1 ;
         j:=help[i].rightp ;
         if (j<>rhsnil) then
          begin
            if (rhs[j].basisl=1) then
             begin
               allocate(j) ;
               if((rhs[j].link=rhsnil)  and (rhs[j].symbol > termg)) then
                begin
                  indsat:=rhs[j].symbol ;
                  fjern:=i ;
                  help[i].rightp:=rhsnil;
                  fjernkaede:=true ;
                  fjboo:=true ;
                  if (t) then
                   fjskriv ;
                  s:=nontstart-1 ;
                  repeat
                    s:=s+1 ;
                    j:=help[s].rightp ;
                    if (j<>rhsnil) then
                     begin
                       l:=rhs[j].basisl ;
                       m:=0 ;
                       repeat
                         for n:=1 to l do
                         begin
                           allocate(j) ;
                           if (rhs[j].symbol=fjern) then
                            rhs[j].symbol:=indsat ;
                         end ;
                         if (rhs[j].link<>rhsnil) then
                          begin
                            j:=rhs[j].link  ;
                            l:=rhs[j].basisl ;
                          end
                         else m:=1 ;
                       until m=1 ;
                     end ;
                  until s=k ;
                end ;
             end ;
          end ;
       until i=k ;
     end ;
 
 
     function identprod (var t:boolean) :boolean ;
     var
       laengde1,laengde2,i,j,kk :integer ;
       ens,idboo : boolean ;
       startp1,startp2,stepp1,stepp2,lastok : pointer2 ;
 
       procedure skriv(var x:integer) ;
       var
         l,jj,ll : integer ;
         stepp3 : pointer2 ;
       begin
         (*UDSKRIVNING OM AENDRING I GRAMMATIKKEN *)
         stepp3:=startp2 ;
         if (x=1) then
          begin
            write(blst,lf,lf) ;
            write(blst,' IDENTICALS PRODUCTIONS EXIST   ') ;
            write(blst,lf) ;
            write(blst,' AND THE GRAMMAR IS MODIFIED  ') ;
            write(blst,lf) ;
            write(blst,' THE FOLLOWING PRODUCTION(S) EXIST MORE THAN ONCE ') ;
            write(blst,lf) ;
          end ;
         write(blst,' ') ;
         jj:=1  ;
         nontwrit(j,jj) ;
         write(blst,' ::= ') ;
         for  l:=1 to laengde2 do
         begin
           allocate(stepp3) ;
           ll:=rhs[stepp3].symbol ;
           if (ll <= termg) then
            (* HQJRE SIDE ER ET TERMINAL SYMBOL *)
            outalf20(internrep[ll],jj)
           else
            (*HQJRE SIDE ER ET NONTERMINAL SYMBOL *)
            nontwrit(ll,jj) ;
           write(blst,' ') ;
         end ;
         write(blst,lf) ;
       end ;
 
 
     begin
       kk:=0 ;
       idboo:=false ;
 
       for j:=nontstart to nontslut do
       begin
         startp1:=help[j].rightp ;
         if (startp1<>rhsnil) then
          begin
            repeat
              laengde1:=rhs[startp1].basisl ;
              startp2:=startp1 ;
              for i:=1 to laengde1 do allocate(startp2) ;
              lastok:=startp2 ;
              startp2:=rhs[startp2].link ;
              if (startp2<>rhsnil) then
               begin
                 repeat
                   ens:=false ;
                   stepp1:=startp1 ;
                   stepp2:=startp2 ;
                   laengde2:=rhs[stepp2].basisl ;
                   if (laengde1=laengde2) then
                    begin
                      ens:=true ;
                      for i:=1 to laengde1 do
                      begin
                        allocate(stepp1) ; allocate(stepp2) ;
                        if (rhs[stepp1].symbol<>rhs[stepp2].symbol) then 
                           ens:=false;
                      end ;
                      if (ens) then
                       begin
                         kk:=kk+1 ;
                         if (t) then
                          skriv(kk) ;
                         idboo:=true ;
                         rhs[lastok].link:=rhs[stepp2].link ;
                       end ;
                    end
                   else
                    for i:=1 to laengde2 do allocate(stepp2) ;
                   if ( not ens) then
                    lastok:=stepp2 ;
                   stepp2:=rhs[stepp2].link ;
                   if (stepp2<>rhsnil ) then
                    startp2:=stepp2 ;
                 until stepp2=rhsnil ;
                 for i:=1 to laengde1 do allocate(startp1) ;
                 startp1:=rhs[startp1].link ;
                 if (startp1=rhsnil) then startp1:=startp2 ;
               end
              else
               startp2:=startp1 ;
            until startp1=startp2 ;
          end ;
       end;
       if((idboo=false)  and  t) then
        begin
	   writeln(blst);
          writeln(blst,'IT HAS BEEN CHECKED  THAT THERE ') ;
          writeln(blst,'EXISTS NO IDENTICAL PRODUCTIONS ') ;
	   writeln(blst);
        end ;
       identprod:=idboo;
     end;
 
   begin
     if (b  and  options[23]) then
      begin
        write(blst,lf) ;
        write(blst,' DUMP BEFOR IDOGFJERN ') ;
        write(blst,lf,lf) ;
        dump5 ;
        write(blst,lf,lf) ;
        dump2 ;
        write(blst,lf,lf) ;
      end ;
     fjboo:=false ;
     boo1:=b ;
     boo2:=b ;
     boo3:=true ;
     while (boo3) do
     begin
       boo4:=identprod(boo1) ;
       if options[28] then
        boo3:=false
       else
        boo3:=fjernkaede(boo2) ;
       boo3:=boo3  or  boo4 ;
       boo1:=false ;
     end ;
     if (options[28]=false) then
      begin
        if (fjboo  and  b) then
         begin
           write(blst,' THE GRAMMER HAS BEEN MODIFIED FOR SIMPLE CHAINS ') ;
           write(blst,lf) ;
           write(blst,' USING THE ABOVE STANDING SUBSTITUTIONS ') ;
           write(blst,lf) ;
         end ;
        if (b  and  (fjboo=false)) then
         begin
           write(blst,' THE GRAMMER HAS BEEN CHECKED FOR ') ;
           write(blst,lf) ;
           write(blst,' SIMPLE CHAINS ') ;
           write(blst,lf) ;
         end ;
      end ;
     if (b  and  options[24]) then
      begin
        write(blst,lf) ;
        write(blst,' DUMP AFTER IDOGFJERN ') ;
        write(blst,lf,lf) ;
        dump5 ;
        write(blst,lf,lf) ;
        dump2 ;
        write(blst,lf,lf) ;
      end  ;
   end ;
   procedure freelist(pt: pointer);
   var p: pointer;
   begin p:=pt;
     while p^.derivp<>nil do p:=p^.derivp;
     p^.derivp:=freeptr;
     freeptr:=pt;
   end; (*FREELIST*)
 
(*$L+*)
   procedure lr0;
   label 20;
     (******   PROC. LR(0) KRAEVER :                                 *)
     (* GOALPRODUKTIONSNUMMER I 'GOALPROD'                    *)
     (* FQRSTE FRIE CELLE I RIGHTSIDE I 'TOP'                 *)
     (* 'LEFTSIDE' I PROD-ARRAY FQRSTE TOMME CELLE NULSTILLET    *)
   var
     stack: array[1..const9] of
     (*packed*) record
               symbovg: 0..const2;
               tilstp: pointer
            end;
     helpp,closp,oldp:pointer;
     lqbep2: pointer2;
     baslae,modeh,stacktop,stacktael,i,symb,prodno:integer;
     kopi: boolean;
     goalprod: integer;
 
     procedure niceparser ;
     var
       i,pnr,l,count,nbcount,nextcount,suc,statenr,nr : integer ;
       p : pointer ;
       rightp :pointer2 ;
 
       function sqg( p : pointer) : integer ;
       var i : integer ;
       begin i:=0 ;
         while (p<>tilstand[i].oldstart) do
         i:=i+1;  sqg:=i ;
       end (*SQG*) ;
 
       procedure linemark ;
       var i : integer ;
       begin  write(blst,lf) ;
	  for i:= 1 to nextcount do write(blst,' ') ;
	     write(blst,'^') ; write(blst,lf);
       end (*LINEMARK*) ;
 
       procedure udskriv ;
       var k,j : integer ;
       begin
         with prod[pnr] do
         begin k:=leftside ;
           rightp:=start; l:=laengde ;
         end ;
         if (statenr>0) then  write(blst,' ',blank)
            else write(blst,' ',i:10) ;
         if (suc >= 0) then write(blst,suc:10,' ')
         else begin
            if (nr=0) then write(blst,'    REDUCE ')
            else  write(blst,blank,' ') ;
          end ;
         write(blst,'    ') ;
         count:=26 ;
         if (k=nontstart) then
          begin
            write(blst,'<GOALSYMBOL>') ;
            count:=count+12 ;
          end
         else  nontwrit(k,count) ;
         write(blst,' ::= ') ; count:=count+5 ;
         nbcount:=count ; nextcount:=-1 ;
         for k:=1 to l do
         begin
           if (k=nr) then nextcount:=count ;
           allocate(rightp) ;
           with rhs[rightp] do
           begin
             if (symbol  >=  nontstart) then  nontwrit(symbol,count)
             else outalf20(internrep[symbol],count);
             write(blst,' ') ; count:=count+1 ;
             if (count >= 110) then
              begin
                if (nextcount >= 0) then linemark
                else write(blst,lf) ;
                for j:=1 to nbcount do write(blst,' ') ;
                nextcount:=-1 ; count:=nbcount ;
          end;end;end;
         if (nextcount >= 0) then linemark
         else write(blst,lf) ;
       end (*UDSKRIV *) ;
 
     begin
       page(blst);
       write(blst,'*************************');
       write(blst,'  THE LR(0)-MACHINE  ');
       write(blst,'**************************') ;
       write(blst,lf,lf) ;
       write(blst,' STATE NUMBER SUCCESSOR   CONFIGURATION SETS') ;
       write(blst,lf) ;
       for i:=0 to tilstnr do
       begin p:=tilstand[i].oldstart ;
         statenr:=0 ;
         repeat
           with p^ do
           begin pnr:=prodnr ; nr:=mode ;
             if (nextp<>nil) then suc:=sqg(nextp)
             else suc:=-1 ;
             p:=derivp ;
           end ;
           udskriv ; statenr:=statenr+1 ;
         until (p=nil) ;
         write(blst,lf) ;
       end ;
       write(blst,lf) ;
     end (*NICEPARSER*) ;
 
     procedure juster(startp:pointer; boo:boolean);
       (******   FOR NY TILSTAND NOTERES FOREKOMST AF  *)
       (* (PROD. NR., SYMBOL NR.) FOR DENNE   *)
       (* uses global variables top, baslae, inf and begintilst (=startp??) *)
     var
       i: integer;
     begin
       lqbep:= startp;
       while lqbep<>nil do
       with lqbep^ do
       begin
         lqbep2:= prod[prodnr].start;
         for i:= mode downto 1 do allocate(lqbep2);
         if rhs[lqbep2].parserp<>nil then
          begin
            while rhs[lqbep2].link<>rhsnil do lqbep2:= rhs[lqbep2].link;
            rhs[lqbep2].link:= top;
            lqbep2:= top;
            newelm(top,'LR0       ');
          end;
         with rhs[lqbep2] do
         begin
           basis:= boo;
           if boo then basisl:= baslae;
           parserp:= begintilst;
           link:= rhsnil;
         end;
         lqbep:= derivp;
       end
     end;
 
     procedure stackellerej;
       (******   CHECKER HVORVIDT  (TILSTAND, OVERGANGSSYMBOL)
         ER STAKKET ELLER SKAL STAKKES      *)
     begin
       with classtop^ do
       with help[inf] do
       if  not overgang then
        begin
          stacktael:= stacktael+1;
          if stacktop= const9 then consterror('LR0       ','CONST9    ',const9);
 
          stacktop:= stacktop+1;
          overgang:= true;
          with stack[stacktop] do
          begin
            symbovg:= inf;
            tilstp:= begintilst;
          end
        end
     end;
 
procedure geninititems;
(* This procedure extends the BOBS system  such that any  nonterminal
   can be  the startsymbol (goal symbol) of the parser.
   For each nonterminal A in [nontStart+1, nontSlut], a production
      G ::=  bobs-go A  -eof-
   is added.
   These productions  are stored in prod[antalProd+1] ... prod[antalprod+M]
   where M=(nontSlut - nontStart)
   Note nontStart is the goal-symbol generated by BOBS. Not the goalsymbol
   specified by the user.
 
   For each A in [nontStart+1,nontSlut] the following LR(0)-items are generated
      [G ::= bobs-go . A -eof-]
   where G is the goalsymbol generated by BOBS.
 
  tilstand[0] will denote the start state of the goalsymbol.
  tilstand[A-nontStart] will denote the start state of nonterm A.
  If A is the goalsymbol specified by the user
  then tilstand[0]=tilstand[A-nontstart];
 
  In procedure compress, a change has also been made. In all reduce states
  for goalproductions mode must be 0. mode=0 terminates the parsing.
  *)
   var sy: integer;
 
   function makegoalprod(sy: integer):integer;
   var ptr: pointer2; i: integer;
   begin
      prodcount:=prodcount+1;
      makegoalprod:=prodcount;
 
      ptr:=top;
      prod[prodcount].start:=top; prod[prodcount].leftside:=nontstart;
      prod[prodcount].laengde:=3; prod[prodcount].lookbackp:=nil;
      rhs[top].basisl:=3;
      newelm(top, 'GOALPROD  '); rhs[top].symbol:=0;
      newelm(top,'GOALPROD  ');  rhs[top].symbol:=sy;
      newelm(top,'GOALPROD  ');  rhs[top].symbol:=1;
      newelm(top,'GOALPROD  '); (* note it is assumed that top is unused*)
      for i:=1 to 4 do
      with rhs[ptr] do
      begin
        link:=rhsnil;
        parserp:=nil;
        allocate(ptr);
      end;
(*      top:=ptr;*)
   end;
 
   function goalitem(sy: integer): pointer;
   var ptr: pointer2;
   begin
      allocp(classtop,1, 'LR0       '); goalitem:=classtop;
      with classtop^ do
      begin ifbasis:=true; prodnr:=makegoalprod(sy);
           mode:=1;
           ptr:= prod[prodnr].start;
           allocate(ptr); inf:=rhs[ptr].symbol;
           derivp:=nil;
      end;
      stacktop:=stacktop+1;
      stack[stacktop].tilstp:=classtop;
      stack[stacktop].symbovg:=classtop^.inf;
      begintilst:=classtop; juster(classtop,true);
    end;
 
begin stacktop:=0; prodcount:=antalprod;
   baslae:=1; (*used by procedure juster *);
   tilstnr:=0; tilstand[tilstnr].oldstart:=goalitem(goalhusk);
   for sy:=nontstart+1 to nontslut do
   begin tilstnr:=tilstnr+1;
      if sy <> goalhusk then  tilstand[tilstnr].oldstart:= goalitem(sy)
      else tilstand[tilstnr].oldstart:=tilstand[0].oldstart;
   end
end;
 
 
     (******    INITIALISERING   *)
   begin
     goalprod:= 0;
     top:=point; newelm(top,'LR0       ');
     freeptr:=nil; antaltilst:=0; lbbegin:=0; lbend:=-1;
 
     geninititems;
 
    (* This comment encloses the code allocating the 'old' initial item *
       allocp(rodp,1,'LR0       ');
       classtop:= rodp;
       WITH rodp^ DO
       BEGIN
         ifbasis:=true;
         prodnr:= goalprod;
         mode:= 1;
         lqbep2:= prod[goalprod].start;
         allocate(lqbep2);
         inf:= rhs[lqbep2].symbol;
         derivp:= nil;
       END;
       baslae:=1;
       stacktop:= 1;
       WITH stack[1] DO
       BEGIN
         tilstp:= rodp;
         symbovg:= rodp^.inf
       END;
       tilstnr:= 0;
       tilstand[tilstnr].oldstart:= rodp;
       juster(rodp,true);
     end of old initial item generation  *)
 
     allocp(classtop,1,'LR0       ');
     begintilst:= classtop;
     while stacktop>0 do
     begin
       (******    TILSTAND,OVERGANGSSYMBOL AFSTAKKES.   *)
       with stack[stacktop] do
       begin
         oldp:=tilstp;
         symb:= symbovg;
       end;
       lqbep:= oldp;
       stacktael:= 0;
       baslae:= 0;
       stacktop:= stacktop- 1;
       for i:=0 to const2 do
       with help[i] do
       begin
         afledt:= false;
         overgang:= false;
       end;
       (******    NYT BASIS-SET GENERERES  *)
       while lqbep^.inf<>symb do lqbep:= lqbep^.derivp;
       closp:= lqbep;
       while true do
       begin
         if baslae= const5 then consterror('LR0       ','CONST5    ',const5);
         baslae:= baslae+ 1;
         with classtop^ do
         begin
           ifbasis:=true;
           nextp:= nil;
           prodnr:= lqbep^.prodnr;
           modeh:= lqbep^.mode+1;
           if prod[prodnr].laengde<modeh then
            begin
              mode:= 0;
              inf:=0;
            end else
            begin
              mode:= modeh;
              lqbep2:= prod[prodnr].start;
              for i:= mode downto 1 do allocate(lqbep2);
              inf:= rhs[lqbep2].symbol;
              stackellerej;
            end;
         end;
         repeat
           lqbep:= lqbep^.derivp;
           if lqbep = nil then goto 20;
         until lqbep^.inf=symb;
         helpp:= classtop;
         allocp(classtop,1,'LR0       ');
         helpp^.derivp:= classtop
       end;
       20: classtop^.derivp:= nil;
       (******   TEST OM BASIS-SET ER GENGANGER  *)
       kopi:= false;
       lqbep2:= prod[begintilst^.prodnr].start;
       for i:= begintilst^.mode downto 1 do allocate(lqbep2);
       if rhs[lqbep2].parserp<>nil then
        while (lqbep2<>rhsnil) and ( not kopi) do
        with rhs[lqbep2] do
        begin
          if basis then
           if baslae=basisl then
            begin
              kopi:= true;
              lqbep:= begintilst;
              while (lqbep<>nil) and kopi do
              with lqbep^ do
              begin
                kopi:= false;
                helpp:= parserp;
                while helpp<>nil do
                begin
                  kopi:=((prodnr=helpp^.prodnr) and (mode=helpp^.mode)) or kopi;
 
                  helpp:= helpp^.derivp
                end;
                lqbep:= derivp
              end;
            end;
          if  not kopi then lqbep2:= link
        end;
       if kopi then
        (******   BASIS-SET GENKENDT  *)
        begin
          closp^.nextp:= rhs[lqbep2].parserp;
          stacktop:= stacktop- stacktael;
          freelist(begintilst);
          allocp(classtop,1,'LR0       ');
          begintilst:=classtop;
        end else
        (******    BASIS-SET ACCEPTERET SOM NYT  *)
        begin
          closp^.nextp:= begintilst;
          if tilstnr= const10 then consterror('LR0       ','CONST10   ',const10)
;
          tilstnr:= tilstnr+1;
          tilstand[tilstnr].oldstart:= begintilst;
          juster(begintilst,true);
          (******     TILHQRENDE CLOSURE-SET GENERERES.    *)
          closp:= classtop;
          lqbep:= begintilst;
          while lqbep<>nil do
          with lqbep^ do
          with help[inf] do
          begin
            if mode > 0 then
             if  not (inf  <=  termg) then
              if  not afledt then
               begin
                 afledt:= true;
                 prodno:= prodindex;
                 while prod[prodno].leftside = inf do
                 with prod[prodno] do
                 begin
                   helpp:= classtop;
                   allocp(classtop,1,'LR0       ');
                   helpp^.derivp:= classtop;
                   with classtop^ do
                   begin
                     ifbasis:=false;
                     lqbep2:= start;
                     allocate(lqbep2);
                     inf:= rhs[lqbep2].symbol;
                     if prod[prodno].laengde=0 
                        then (*EMPTY RIGHTHAND SIDE*) mode:=0 (*TRUNC!!*)
                        else mode:=1;
                     prodnr:= prodno;
                     derivp:= nil;
                     nextp:= nil;
                   end;
                   if classtop^.mode>0 then stackellerej;
                   prodno:= prodno+1;
                 end;
               end;
            lqbep:= derivp;
          end;
          with closp^ do
          if derivp<>nil then juster(derivp,false);
          allocp(classtop,1,'LR0       ');
          begintilst:= classtop
        end;
     end;
     gemp:= classtop;
     if options[2] then skrivparser(classtop);
     if options[30] then niceparser ;
     (*   dump1;  point:=top;  top:=1; dump2; top:=point; *)
   end;
   (******  END OF PROCEDURE  LR0      *)
 
(*$L-*)
   procedure lookb;
     (* LOOKB GENERATES THE LOOKBACKSTATES *)
   var
     prodnr,symb,md,r1:integer;
     point: pointer2;  tilstp:pointer;
   begin
     prod[0].lookbackp:=nil;
     antaltilst:=tilstnr;
     lbbegin:=tilstnr+1;
     freeptr:=nil;
 
     prodnr:=1;
     while prodnr <= antalprod do (*FOR prodnr:=1 TO antalprod DO*)
     with prod[prodnr] do
     begin
       fcqi:=0;
       allocp(classtop,5,'LOOKBP    ');
       begintilst:=classtop; symb:=leftside;
       point:=start; if laengde>0 then (*RHS NOT EMPTY*) allocate(point);
       while point<>rhsnil do
       with classtop^ do
       begin     mode:=5;
         tilstp:=rhs[point].parserp;
         if tilstp=nil then
          begin
            write(blst,' THE STARTSYMBOL CANNOT PRODUCE A STRING CONTAINING ');
            write(blst,lf,' '); r1:=1; nontwrit(leftside,r1);
            write(blst,lf,lf); stop(3);
          end;
         lookbp:=tilstp;
         while tilstp^.inf<>symb do tilstp :=tilstp^.derivp;
         tilstp:=tilstp^.nextp; remember(tilstp);
         nextp:=tilstp;  oldp:=classtop;
         allocp(classtop,5,'LOOKB     ');
         oldp^.derivp:=classtop;
         point:=rhs[point].link;
       end;
       oldp^.derivp:=nil;
       if fcqi=1 then
        begin
          lookbackp:=begintilst^.nextp;
          freelist(begintilst);
        end else
        begin
          md:=5; optimize(tilstp,md);
          oldp^.derivp:=classtop;
          with classtop^ do
          begin  derivp:=nil;
            nextp:=tilstp;
            lookbp:=nil ;
            mode:=5;
          end;
 
          antaltilst:=antaltilst+1;
          if antaltilst>const10
             then consterror('LOOKB     ','CONST10   ',const10);
          tilstand[antaltilst].oldstart:=begintilst;
          lookbackp:=begintilst;
        end;
 
       (* lookBackEntry[symb]:=lookbackp; *)
 
       while prod[prodnr+1].leftside=symb do
       begin  prodnr:=prodnr+1;
         prod[prodnr].lookbackp:=lookbackp;
       end;
       prodnr:=prodnr+1;
     end;
     lbend:=antaltilst;
     freeptr:=nil;
 
     if options[15] then
     begin skrivparser(gemp); (*
       writeln(blst,'nontL=',nontL:1,' nontR=',nontR:1);
       writeln(blst); writeln(blst,'LookBackEntry:');
       FOR i:=nontStart to nontSlut DO  writeln(blst,i:3,ord(lookBackEntry[i]));
       writeln(blst);*)
     end;
     if options[16] then dump5; (* PROD ARRAY*)
     if options[17] then dump1; (* TILSTANDS ARRAY *)
   end (* END LOOKB *) ;
 
   (**************************************************************)
   (*                                                            *)
   (*                      ADEQUAD                               *)
   (*                                                            *)
   (**************************************************************)
 
 
   procedure adequad;
   type
     item=(*packed*) record p,d: 0..const1; nobot:boolean end;
     laset=(*packed*) array[0..const2] of boolean;
     tilstcheck=(nyindgang,nyvej,udenom) ;
     state = pointer;
 
   var    it1,it2: item;
 
     (* used by function entertm   *)
     tm: array [0..const10] of state;
     tmtop: integer;
 
     prodant,termant,lalaengde,pnr,lsymb,i,j,k,l :integer ;
     boo,lrok,headwrite : boolean ;
     start,helpp,lqbep1,lqbep2,lqbep3,lastok,stopp : pointer ;
     lookant : array[1..const14] of (*packed*) record
                                              ant   : 1..const8 ;
                                              point : pointer
                                           end ;
     stack : array[1..const2] of (*packed*) record
                                           symb  : 0..const2 ;
                                           pnr   : 0..const1 ;
                                           token : modetype
                                        end ;
     la1: laset;
     la: array[0..const2] of integer;
     pr1,pr2:integer; (*prod.no. of conflicting productions.*)
     (* used in testconflicts and lrcond   *)
 
 
     (****************************************************************)
     (*                                                                *)
     (*                   SMALL PROCEDURES                             *)
     (*                                                                *)
     (******************************************************************)
 
     function symbmax:integer;
     begin
       if options[59] then symbmax:=nontslut else symbmax:=nontstart-1
     end;
 
     function itemeq(it1,it2:item):boolean;
     begin
        itemeq:=(it1.p=it2.p) and (it1.d=it2.d) and (it1.nobot=it2.nobot)
     end;
 
     procedure cr(n:integer);
     begin writeln(blst);
       for n:=n downto 1 do write(blst,' ');
     end;
 
     procedure empty(var m:laset);
     var i:integer;
     begin
       for i:=0 to symbmax do m[i]:=false;
     end;
 
     procedure inter(var m:laset; n:laset);
     var i:integer;
     begin
       for i:=0 to symbmax do m[i]:=m[i] and n[i];
     end;
 
     procedure union(var m:laset; n:laset);
     var i:integer;
     begin
       for i:=0 to symbmax do m[i]:=m[i] or n[i];
     end;
 
     function isempty(m: laset):boolean;
     var b:boolean; i:integer;
     begin b:=false;
       for i:=0 to symbmax do b:=b or m[i];
       isempty:=not b
     end;
 
 
     function terminal( symb:integer ): boolean;
     begin
       terminal:= (symb<=termg) or options[59]
     end;
 
 
     function emptys(pn:integer; l:integer): boolean;
     label 33;
     var
       i:integer;
       emptyboo: boolean;
     begin
       if  prod[pn].laengde+1<>l then
        begin
          emptyboo:=true; (* OPTIMIST *)
          for i:=l to prod[pn].laengde do
          begin
            emptyboo:=emptyboo and emptya[rhs[prod[pn].start+i].symbol];
            if not emptyboo then goto  33;
          end;
        end
       else emptyboo:=true;
       33:
          emptys:=emptyboo;
     end; (* EMPTYS *)
 
     function gotox(r:pointer; symb:integer): pointer;
     begin
       while r^.inf<>symb do r:=r^.derivp;
       gotox:=r^.nextp;
     end; (* GOTOX *)
 
     function gotos(r:pointer; p,l:integer): pointer;
     var i,sy:integer;
     begin
       for i:=1 to l do
       begin
         sy:=rhs[prod[p].start+i].symbol;
         while r^.inf<>sy do r:=r^.derivp;
         r:=r^.nextp;
       end;
       gotos:=r;
     end;
 
     procedure pred(p,l:integer; t:pointer; var rl:integer; var s:pointer);
     label 10;
     begin
       if rl=-1 then
        begin (* INITIAL CALL *)
          rl:=prod[p].start;
          if prod[p].laengde>0 then rl:=rl+1;
        end;
       while rl<>rhsnil do
       begin
         s:=rhs[rl].parserp;
         rl:=rhs[rl].link;
         if gotos(s,p,l-1)=t then goto 10;
       end;
       s:=nil;
       10:
     end; (* PRED *)
 
 
     (*****************************************************)
     (*                                                   *)
     (*           AUXILLARY PROCEDURES                    *)
     (*                                                   *)
     (*****************************************************)
 
     procedure optimalisering(   x : tilstcheck ) ;
     var seq :  integer;
     begin 
       case x of
          nyindgang :
             begin
		seq:=lastok^.seq; lastok^:=helpp^; lastok^.seq:=seq;
             end ;
          nyvej :
             begin
               lastok^.derivp:=helpp ;
               lastok:=helpp ;
             end ;
          udenom :
             begin
               lastok^.derivp:=helpp ;
             end ;
       end ;
     end ;
 
 
 
     procedure lalrtext (   x : integer ) ;
     var
       i : integer ;
     begin page(blst);
       for i:=1 to 71 do write(blst,'*');
       write(blst,lf,lf) ;
       write(blst,'         ') ;
       case x of
          1 : begin
		 writeln('******** The grammar is LALR(1)');
		 writeln(blst,'The grammar is LALR(1) '); writeln(blst);
		 for i:=1 to 71 do write(blst,'*'); writeln(blst);
	      end ;
	 2: begin
	       writeln('!!!!!!!! The grammar is NOT LALR(1)!!! '); writeln;
	       writeln('A parser for the grammar has however been constructed.');
	       writeln('THIS PARSER MAY NOT WORK PROPERLY!!!');
	       writeln('When a parse conflict occurs, ');
	       writeln('the parser selects one of the possibilities.');
	       writeln('If the parse conflict is due to an ambiguity,');
	       writeln('one of the possible right parses is produced.');
	       writeln('If the grammar is unambiguous and NON LALR(1),');
	       writeln('a parse error may appear on a syntactic correct string!');
	       writeln;	       

	       writeln(blst,'The grammar is NOT LALR(1) '); writeln(blst);
	       for i:=1 to 71 do write(blst,'*'); writeln(blst); writeln(blst);
	       writeln(blst,'A parser for the grammar has however been constructed.');
	       writeln(blst,'THIS PARSER MAY NOT WORK PROPERLY!!!');
	       writeln(blst,'When a parse conflict occurs, ');
	       writeln(blst,'the parser selects one of the possibilities.');
	       writeln(blst,'If the parse conflict is due to an ambiguity,');
	       writeln(blst,'one of the possible right parses is produced.');
	       writeln(blst,'If the grammar is unambiguous and NON LALR(1),');
	       writeln(blst,'a parse error may appear on a syntactic correct string!');
	       writeln(blst); writeln(blst);
	       
          end ;
       end ;
     end ;
 
 
     procedure adeqwrite (   x : integer ) ;
     begin
       case x of
          5 :
             begin
               (*OVERSKRIFT TIL LOOKAHEAD-MAENGDERNE LALR1 *)
               page(blst);
               write(blst,' ','*********************');
               write(blst,'  A list of LR(1) conflicts  ');
               write(blst,'*********************');
               cr(0); cr(0);
             end ;
          6 :
             begin
               (*UDSKRIFT AF AFSLUTNING PAA LOOKAHEAD-MAENGDERNE LALR1 *)
               cr(0); cr(0);
               write(blst,' ','*********************');
               write(blst,' End of LR(1) conflicts  ');
               write(blst,'*************************');
               cr(0); cr(0);
             end ;
          3,4: begin writeln(blst,' adequad udskrift er fjernet '); end;
       end ;
     end ;
 
     function findreduce(pnr:integer):pointer;
 
     var
       p1,p2: pointer2;
       pt: pointer;
 
     begin
       with prod[pnr] do
       if laengde=0 then findreduce:=lookbackp
       else
        begin p1:=start;
          while rhs[p1].parserp^.derivp<>nil do
          begin p2:=p1; p1:=rhs[p1].link;
            if p1=rhsnil then
             begin   allocp(pt,1,'FINDREDUCE');
               with pt^ do
               begin mode:=3; inf:=laengde-1; prodnr:=pnr; 
                     nextp:=lookbackp; derivp:=nil; (*TRUNC*)
               end;
               antaltilst:=antaltilst+1; updatemax(10,antaltilst);
               if antaltilst>const10 
                  then consterror('FINDREDUCE','CONST10   ',const10);
               tilstand[antaltilst].oldstart:= pt;
               newelm(top,'FINDREDUCE'); p1:= top;
               rhs[p1].parserp:=pt; rhs[p1].link:=rhsnil; rhs[p2].link:=p1;
             end;
          end;
          findreduce:= rhs[p1].parserp;
        end;
     end;  (* FINDREDUCE *)
 
 
     procedure initdot;
     var i:integer; p:pointer;
     begin
       for i:=0 to antaltilst do
       begin
         p:=tilstand[i].oldstart;
         while p<>nil do
         begin
           p^.dot:=p^.mode;
           p:=p^.derivp;
         end;
       end;
     end; (* INITDOT *)
 
     (*****************************************************************)
     (*                                                                *)
     (*                    NEW LOOKAHED                                *)
     (*                                                                *)
     (******************************************************************)
 
 
 
     procedure lookahead(pointp:pointer; prodno,dotno:integer; var look:laset);
     var
       j,reclevel: integer; (* MISCELANEOUS *)
 
       done: array [0..const16] of (* CONST16 > MAX NUMBER OF PRODUCTIONS *)
       (*packed*) record
                 dotno:integer;
                 mrk: boolean;
                 lnk: 0..const16;  (* INTERNAL Done-LINK *)
                 hidep: pointer;
              end;
 
       donetop: integer;  (* MARKS UN-USED PART OF Done *)
       (* POINTS TO LAST ITEM USED *)
 
 
 
       function enterdone(r:pointer; symb:integer):boolean;
          (* IF r IN done[symb] OR r=nil THEN enterdone=false *)
          (* IF r NOTIN done[symb]       THEN enterdone=true  *)
          (*                  AND r is inserted in done[symb] *)
       label 2;
       var
         i,oldi:integer;    (* LOOP-POINTER TO Done *)
       begin enterdone:=false; i:=symb;
         while done[i].mrk do
         with done[i] do
         if hidep<>r then
          begin oldi:=i; i:=lnk end
         else goto 2;
         if i=0 then (*not found*)
          begin donetop:=donetop+1; updatemax(16,donetop);
            if donetop>const16 
               then consterror('EnterDone ','const16   ',const16);
            done[oldi].lnk:=donetop; i:=donetop
          end;
         with done[i] do
         begin hidep:=r; mrk:=true; lnk:=0 end;
         enterdone:=true;
         2:
       end; (* EnterDone *)
 
       function entertm(r:pointer):boolean;
         (* IF r IN    tm THEN entertm=false *)
         (* IF r NOTIN tm THEN entertm=true  *)
         (*          AND r is inserted in tm *)
       var i: integer;
       begin tm[0]:=nil; i:=0;
          while (tm[i]<>r) and (i<tmtop) do i:=i+1;
          if tm[i]=r then entertm:=false
          else begin tmtop:=tmtop+1;
             tm[tmtop]:=r; entertm:=true;
       end; end; (* entertm*)
 
       procedure trans( r: pointer );
       begin
         if entertm(r)  then
          while r<>nil do
          begin
            if r^.dot<>0  then
	       begin
		  (* OLM: 16.8.95; the following stmt used to be
		   *  if terminal(...) then ... else if emptya[...] then ...;
		   *  This does NOT work with option 59, since terminal(x)
		   *  returns true for terminal as well as nonterminals with
		   *  this option. The reason is that 59 includes nonterminals
		   *  in the lookahead sets.
		   *)
		  if terminal(r^.inf) then look[r^.inf]:=true;
		  if emptya[r^.inf] then trans(r^.nextp);
	       end;
            r:=r^.derivp;
       end; end; (* TRANS *)
 
 
       procedure lalr1(t:pointer; pn: integer; dn:integer);
       var
         lhs,rlink:integer;
         s,r:pointer;
       begin if options[39] then writeln(blst,ord(s),pn,dn,reclevel);
         reclevel:=reclevel+1;
         lhs:=prod[pn].leftside;
         begin
           (* FOR s IN pred(T,...)        *)
           rlink:=-1; pred(pn,dn,t,rlink,s);
           while s<>nil do
           begin
             if enterdone(s,lhs) then
              begin
                trans(gotox(s,lhs));
                r:=s;
                while r<>nil do
                begin
                  if (r^.dot<>0) and (r^.inf=lhs) then
                   if emptys(r^.prodnr,r^.dot+1) then lalr1(s,r^.prodnr,r^.dot);
 
                  r:=r^.derivp;
             end; end;
             pred(pn,dn,t,rlink,s);
         end; end;
         reclevel:=reclevel-1;
       end; (* LALR1 *)
 
     begin (* LOOKAHEAD *)
       if options[39] then
        begin  write(blst,'     ');writech('-',60);
          write(blst,lf,lf,'     STATE    PRODNO     DOTNO     LEVEL',lf);
        end;
       donetop:=nontslut; tmtop:=0;
       for j:=0 to donetop do done[j].mrk:=false;
       empty(look);  reclevel:=0;
 
       if dotno=0 then lalr1(pointp,prodno,prod[prodno].laengde+1)
                  else lalr1(pointp,prodno,dotno);
 
       lalaengde:=0;
       for j:=0 to symbmax do
       if look[j] then
        begin la[lalaengde]:=j; updatemax(8,lalaengde);
          if lalaengde<const8 then lalaengde:=lalaengde+1
          else consterror('LOOKAHEAD ','CONST8    ',const8);
        end;
     end;  (* LOOKAHEAD *)
 
 
     (****************************************************************)
     (*                                                                *)
     (*                   OLD LOOKAHEAD                                *)
     (*                                                                *)
     (******************************************************************)
 
 
     procedure lalrlookahead(pointp : pointer ; prodno : integer) ;
 
     var
       j,l,info : integer;
       ll: array[0..const16] of
       (*packed*) record
                 mrk,lamrk: boolean;
                 lnk: 0..const16;
                 hidep: pointer
              end;
       lltop: integer;
 
       tm: array[1..const16] of  (*packed*) record s: pointer; lnk: 0..const16 end;
       tmtop: integer;
 
 
       procedure lalr1(statep: pointer; prodno,dotno: integer);
       label 2;
       var
         leftinf,hinx: integer;
         rightp,prodp,syinx: pointer2;
         runp,transp,loopp,lalrpt: pointer;
 
         procedure trans(t: pointer; stacktop: integer);
         label 10;
         var inx,lhs,i: integer; r: pointer;
         begin
            for i:=tmtop downto stacktop+1 do
               if (tm[i].s=t) and (tm[i].lnk=stacktop) then goto 10;
            inx:=stacktop;
            while inx>0 do if tm[inx].s=t then goto 10 else inx:=tm[inx].lnk;
            (* push t *)
            tmtop:=tmtop+1; 
            if tmtop>const16 then consterror('trans     ','const16   ',const16);
            updatemax(16,tmtop);
            tm[tmtop].s:=t; tm[tmtop].lnk:=stacktop; stacktop:=tmtop;
            (* parse *)
            while t<>nil do
            begin
               if t^.mode<>0 then ll[t^.inf].lamrk:=true
               else (* reduce *)
               begin inx:=stacktop; i:=prod[t^.prodnr].laengde;
                  while (inx>0) and (i >0) do
                  begin inx:=tm[inx].lnk; i:=i-1 end;
                  if inx=0 then
                  begin allocp(r,1,'trans     ');
                     r^.prodnr:=t^.prodnr; r^.mode:=i; r^.derivp:=lalrpt; 
                     (* lalrpt TRUNC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*)
                  end else
                  begin r:=tm[inx].s; lhs:=prod[t^.prodnr].leftside;
                     while r^.inf<>lhs do r:=r^.derivp;
                     trans(r^.nextp,inx);
               end; end;
               t:=t^.derivp;
           end;
        10:
        end; (* trans *)
 
       begin
         with prod[prodno] do
         begin leftinf:=leftside; rightp:=start; 
             if laengde>0 then (*RHS NOT EMPTY TRUNC !!!!!!!!!!!!!!!!*)
         end;
         prodp:=rightp;
         while prodp<>rhsnil do
         begin runp:=rhs[prodp].parserp; loopp:=runp; syinx:=rightp;
           for hinx:=1 to dotno do
           begin info:=rhs[syinx].symbol;
             while loopp^.inf<>info do loopp:=loopp^.derivp;
             loopp:=loopp^.nextp; allocate(syinx);
           end;
           if loopp=statep then
            begin
              if ll[leftinf].mrk then
               begin hinx:=leftinf;
                 repeat with ll[hinx] do
                   begin if runp=hidep then goto 2;
                     l:=hinx; hinx:=lnk;
                   end;
                 until hinx=0;
                 lltop:=lltop+1;
                 if lltop>const16 
                    then consterror('LALRLOOKAH','const16   ',const16);
                 updatemax(16,lltop);
                 hinx:=lltop; ll[l].lnk:=hinx;
               end else hinx:=leftinf;
              with ll[hinx] do begin mrk:=true; hidep:=runp; lnk:=0; end;
              transp:=runp;
              while transp^.inf<>leftinf do transp:=transp^.derivp;
              transp:=transp^.nextp;
              tmtop:=0; lalrpt:=nil;
              trans(transp,0);
              loopp:=lalrpt;
              while loopp<>nil do with loopp^ do
              begin lalr1(runp,prodnr,mode); loopp:=derivp end;
              if lalrpt<>nil then freelist(lalrpt);
            end;
           2: (*TRY NEXT *)  prodp:= rhs[prodp].link;
         end;
       end;  (*LALR1*)
 
 
     begin lltop:=const2;
       for j:=0 to const2 do with ll[j] do
       begin mrk:=false; lamrk:=false; end;
       lalr1(pointp,prodno,prod[prodno].laengde);
       lalaengde:=0;
       for j:=0 to symbmax do
       if ll[j].lamrk then
        begin la[lalaengde]:= j; updatemax(8,lalaengde);
          if lalaengde<const8 then lalaengde:=lalaengde+1
          else consterror('LalrLookah','const8    ',const8);
        end;
     end; (* LALRLOOKAHEAD *)
 
 
     (*************************************************************)
     (*                                                                *)
     (*                       LR-COND                                  *)
     (*                                                                *)
     (******************************************************************)
 
 
     function lrcond( it1,it2: item;
       t:     (* STATE  *)  pointer;
       var c1,c2: laset): boolean;
 
     var
       check: boolean;
       done: array[0..const16] of   (* CONST16 > MAX NO OF PROD *)
       (*packed*) record rf: pointer;
                 ita,itb: item;
                 mrk:boolean;
                 lnk: 0..const16; (* INTERNAL DONE-link *)
              end;
       donetop: integer;
       global,lr,locallr,locallalr,la1,la2: laset;
       tm: array [0..const10] of pointer;
       tmtop: integer;
       i:integer;
 
 
       procedure dotrans(r:pointer; var transla: laset);
 
         function entertm( r:pointer ): boolean;
         var
           i: integer;       (* LOOP-POINTER TO TM *)
           (* RETURNS FALSE IN  R  ALREADY REGISTERED (OR NIL), *)
           (* OTHERWISE TRUE, PLUS THAT  R  IS INSERTED  *)
 
         begin tm[0]:=nil; i:=0;
           while (tm[i]<>r) and (i<tmtop) do i:=i+1;
           if tm[i]=r then entertm:=false
           else begin tmtop:=tmtop+1;
              tm[tmtop]:=r; entertm:=true
            end;
         end; (* ENTERTM *)
 
         procedure trans( r: pointer );
           (*       *)
         begin
           if entertm(r) then
            while r<>nil do
            begin
              if r^.dot<>0 then
               if terminal(r^.inf) then transla[r^.inf]:=true
               else if emptya[r^.inf] then trans(r^.nextp);
              r:=r^.derivp;
            end; (* WHILE *)
         end; (* TRANS *)
 
       begin
         empty(transla);
         tmtop:=0; trans(r);
       end; (* DOTRANS *)
 
       procedure sort(var it1,it2: item; var swap: boolean);
       var it: item;
       begin
         if (it1.d<it2.d) or (it1.d=it2.d) and (it2.p<it1.p)
          or (it1.p=it2.p) and (it1.d=it2.d) and (it2.nobot<it1.nobot) 
         then (* Swap *)
          begin it:=it1; it1:=it2; it2:=it; swap:= not swap; end;
       end;
 
       function enterdone( r:pointer; it1,it2: item; swap:boolean ): boolean;
         (* RETURNS FALSE IF  (IT1,IT2,R) in Done or R=NIL *)
         (* OTHERWISE TRUE, and inserts (IT1,IT2,R) in Done*)
         (* DONETOP MUST BE INITIALIZED TO   ANTALPROD     *)
       label 10;
       var
         i,oldi:integer;      (* LOOP-POINTER TO DONE *)
       begin
         sort(it1,it2,swap);
         enterdone:=false;
         if (r<>nil) and (it1.p>0) then
          begin
            i:=it1.p;
            while done[i].mrk do (*done[0] is never used; done[i].mrk=false*)
            with done[i] do
            if (rf=r) and itemeq(ita,it1) and itemeq(itb,it2) then
             begin enterdone:=false; goto 10 end
            else begin oldi:=i; i:=lnk end;
            if i=0 then (*not found*)
             begin donetop:=donetop+1; updatemax(16,donetop);
               if donetop>const16 
                  then consterror('lr-cond   ','const16   ',const16);
               done[oldi].lnk:=donetop;
               i:=donetop;
             end;
            with done[i] do
            begin rf:=r; ita:=it1; itb:=it2; mrk:=true; lnk:=0 end;
            enterdone:=true;
          end;
         10:
       end; (* ENTERDONE *)
 
       procedure pritem(it: item);
       begin
         if it.nobot then write(blst,'    ') else write(blst,' // ');
         writem(it.p,it.d); cr(16);
       end;
 
       procedure cond(ir,jr:item; t:pointer; lr:laset;
         level:integer; conflict, swap:boolean);
       var
         lhs,rlink,inf:integer;
         s,r:pointer;
         contrib,loopp,moreconflict:boolean;
         is,js: item;
 
         function bottom:boolean;
         begin bottom:=not (is.nobot or js.nobot) end;
 
         procedure trace;
         var a1,a2,a3:integer;
         begin
           if options[38] then
            writeln(blst,is.p,is.d,is.nobot,js.p,js.d,js.nobot,
            ord(s),rhs[prod[js.p].start+js.d].symbol);
           contrib:=false; moreconflict:=false;
           (* find possible conflicts*)
           if jr.nobot then
            begin a1:=js.p; a2:=prod[a1].start; a3:=rhs[a2+js.d].symbol;
              if options[38] then writeln(blst,a1,a2,a3);
              (* LocalLALR:= Global INTER (FIRST(..)- e ) *)
              dotrans(gotox(s,a3 (*rhs[prod[Js.P].start+Js.D].symbol*) )
                           ,locallalr);
              inter(locallalr,global);
 
              (* LocalLR:=LocalLALR INTER LALR1(Is,S) *)
              if ir.nobot then lookahead(s,is.p,is.d,la1) (* result in LA1 *)
              else empty(la1);
              locallr:=la1;
              inter(locallr,locallalr);
 
              (* LR:=LR UNION LocalLR *)
              union(lr,locallr);
 
              contrib:=not isempty(locallalr);
              conflict:= conflict or contrib;
 
              if not conflict then
               begin lookahead(s,js.p,js.d,la2);
                 inter(la1,la2); moreconflict:=not isempty(la1)
                 (* MoreConflict= (LALR1(Is,S) INTER LALR1(Js,S)) <> EMPTY *)
               end;
            end;
         end; (*Trace*)
 
         procedure print;
	 var i: integer;
         begin
           write(blst,'(',level:4,')---------------------------------------------');
           cr(16);
 
           if not swap then pritem(is);
           pritem(js);
           if contrib then
            begin write(blst,' ':20); write(blst,'which generates: ');  cr(41);
              for i:=0 to termg do
              if locallalr[i] then
               begin outalf20(internrep[inf],dummy);
                 if lr[i] then write(blst,' ') else write(blst,' ! no LR-conflict ');
              end;
            end; cr(16);
           if swap then pritem(is);
           if bottom then
            begin  write(blst,'(***  path terminated by bottom  ***)'); cr (16); end
else
            if loopp then
             begin  write(blst,'(***  path terminated by loop    ***)'); cr(16); end;
 
         end; (*Print*)
 
 
       begin
         sort(ir,jr,swap);
         is:=ir; is.d:=is.d-jr.d+1;
         lhs:=prod[jr.p].leftside;
         if options[38] then writeln(blst,' COND:',ir.p,ir.d,jr.p,jr.d,ord(t));
         rlink:=-1;
         pred(jr.p,jr.d,t,rlink,s);
         while s<>nil do
         begin r:=s;
           while r<>nil do
           begin
             if (r^.dot <> 0) and (r^.inf = lhs)  then
              begin
                with js do
                begin p:=r^.prodnr; d:=r^.dot;
                  nobot:=jr.nobot and emptys(p,d+1);
                  if options[38] then
                   writeln(blst,' cond-inner',is.p,is.d,is.nobot,p,d,nobot,ord(s));
                end;
                loopp:=not enterdone(s,is,js,swap);
                trace;
                if conflict or not bottom and moreconflict then
                 begin  print;
                   if  not(loopp or bottom) then
                    cond(is,js,s,lr,level+1,conflict,swap)
                 end; end;
             r:=r^.derivp;
           end;
           pred(jr.p,jr.d,t,rlink,s);
         end end; (* COND *)
 
     begin (* LRCOND *)
       check:=true;
       donetop:=antalprod;
       for i:=0 to const16 do done[i].mrk:=false;
       empty(lr);
       global:=c1; inter(global,c2);
       cond(it1,it2,t,lr,0,false,false);
       lrcond:=check;
     end; (* LRCOND *)
 
 
     procedure testconflicts(confstate: pointer);
       (**************************************************************)
       (* USING GLOBAL VARIABLES:                                    *)
       (*  STACK: ARRAY CONTAINING SHIFT-INFORMATION                 *)
       (*  LOOKANT: ARRAY CONTAINING REDUCE-INFORMATION              *)
       (*  TERMANT: INTEGER (MAXIMUM ENTRY IN STACK)                 *)
       (*  PRODANT: INTEGER (MAXIMUM ENTRY IN LOOKANT)               *)
       (**************************************************************)
     var  c1,c2: laset;
       i,j: integer;
       conflict: boolean;
       (**)
       procedure mark(var c: laset; index: integer);
       var i:integer;
         p: pointer;
       begin
         empty(c);
         p:=lookant[index].point;
         for i:=1 to lookant[index].ant do
         begin
           c[p^.inf]:=true;
           p:=p^.derivp;
         end;
       end; (* MARK *)
       (**)
       function check: boolean;
       var i: integer;
         b: boolean;
       begin
         b:=false;
         for i:=0 to nontstart-1 do (* CHECK TERMINALS ONLY *)
         b:=b or (c1[i] and c2[i]);
         if b and headwrite then
          begin headwrite:=false; lrok:=false;
            adeqwrite(5);
          end;
         check:=b;
       end; (* CHECK *)
       (**)
       procedure ShiftReduceConflict(prodindex: integer);
       var i: integer;
         inf: symbol;
         p:pointer;
       begin cr(02);
         for i:=1 to 61 do write(blst,'-'); cr(02);
         write(blst,'LALR(1) conflict of type SHIFT/REDUCE') ;cr(0);cr(04);
         write(blst,'Conflicting item(s):');
         for i:=1 to termant do
         begin
           inf:=stack[i].symb;
           if c1[inf] and c2[inf] then (* CONFLICT ON INF *)
            begin cr(06);
              writem(stack[i].pnr,stack[i].token);
              with it1 do
               begin p:=stack[i].pnr; d:=stack[i].token; nobot:=false end;(*trunc*)
            end;
         end;
         cr(04);
         write(blst,'In conflict with production:'); cr(06);
         p:=lookant[prodindex].point;
         write(blst,p^.prodnr:3,': ');
         writem(p^.prodnr,0);
         it2.p:=p^.prodnr; it2.d:=prod[it2.p].laengde+1; it2.nobot:=true;
         cr(06);
         write(blst,'Lookaheadset:'); cr(06);
         for i:=0 to termg do
           if c2[i] then begin outalf20(internrep[i],dummy); write(blst,' ') end;
         cr(04);
         write(blst,'Conflict on symbol(s):'); cr(06);
         for i:=0 to termg do
           if c1[i] and c2[i] then (* CONFLICT *)
           begin outalf20(internrep[i],dummy); write(blst,' ') end;
         cr(04);
         write(blst,'Other shift item(s) in that state:');
         for i:=1 to termant do
         begin
           inf:=stack[i].symb;
           if not (c1[inf] and c2[inf]) then
            begin cr(06);
              writem(stack[i].pnr,stack[i].token);
            end;
         end;
         cr(0);
         if options[35] then
          begin write(blst,'Backwards trace:'); cr(04);
            if lrcond(it1,it2,confstate,c1,c2) then else;
          end;
       end;
       (**)
       procedure ReduceReduceConflict(index1,index2:integer);
       var i:integer; p: pointer;
       begin
         pr1:=lookant[index1].point^.prodnr;
         pr2:=lookant[index2].point^.prodnr;
         cr(02);
         for i:=1 to 61 do write(blst,'-'); cr(02);
         write(blst,'LALR(1) conflict of type: REDUCE/REDUCE'); cr(04);
         write(blst,'first conflicting production:'); cr(06);
         p:=lookant[index1].point;
         write(blst,pr1:3,': '); writem(p^.prodnr,0); cr(06);
         write(blst,'Lookahead set:'); cr(05);
         for i:=0 to termg do
         begin
           if c1[i] then begin outalf20(internrep[i],dummy); write(blst,' ') end
         end;
         cr(04);
         write(blst,'second conflicting production:'); cr(05);
         p:=lookant[index2].point;
         write(blst,pr2:3,': '); writem(p^.prodnr,0); cr(06);
         write(blst,'lookahead set:'); cr(05);
         for i:=0 to termg do
           if c2[i] then begin outalf20(internrep[i],dummy); write(blst,' ') end;
         cr(04);
         write(blst,'Conflict on symbol(s)'); cr(05);
         for i:=0 to termg do
           if c1[i] and c2[i] then begin outalf20(internrep[i],dummy); end;
         cr(04);
 
         if options[35] then
          begin write(blst,'Backwards trace:'); cr(04);
            with it1 do begin p:=pr1; d:=prod[p].laengde+1; nobot:=true end;
            with it2 do begin p:=pr2; d:=prod[p].laengde+1; nobot:=true end;
            if lrcond(it1,it2 ,confstate,c1,c2)
             then else;
          end;
       end; (* REDUCE/REDUCE-CONFLICT *)
 
     begin
       empty(c1);
       for i:=1 to termant do
       c1[stack[i].symb]:=true;
       for i:=1 to prodant do
       begin
         mark(c2,i);
         (* IF C1 AND C2 ARE DISJOINT THERE IS NO SHIFT/REDUCE CONFLICT *)
         conflict:=check;
         if conflict then ShiftReduceConflict(i);
       end;
       (* CHECK IF LOOKANT[I]=/=LOOKANT[J], I=/=J *)
       for i:=1 to prodant-1 do
       begin
         mark(c1,i);
         for j:=i+1 to prodant do
         begin
           mark(c2,j);
           (* IF C1 AND C2 ARE DISJOINT THERE IS NO REDUCE/REDUCE CONFLICT *)
           conflict:=check;
           if conflict then ReduceReduceConflict(i,j);
         end;
       end;
     end; (* TESTCONFLICTS *)
 
 
 
     (******************************************************************)
     (*                                                                *)
     (*                  TEST - PROCEDURES                             *)
     (*                                                                *)
     (******************************************************************)
 
     procedure predtest;
     var
       rlink,i:integer; (* INDEX TO PROD *)
       oldprodno,oldstate:integer;
       s:pointer; (* LINK-POINTER IN RHS *)
       t:pointer2; (* DVS. DENNE *)
 
     begin
       if options[38] (* PRED-TEST *)
        then begin
          if options[15] then (* SKRIVPARSER(GEMP) ALREADY CALLED *)
          else    skrivparser(gemp);
          page(blst);write(blst,lf);
          writech('*',20); write(blst,' PRED-TEST (OPTION 38) ');
          writech('*',20); write(blst,lf,lf);
          write(blst,'PRODNO     STATE      PRED',lf,lf);
          oldprodno:=-1; oldstate:=-1;
          for i:=1 to antalprod do
          begin
            t:=prod[i].start;
            while t<>rhsnil do
            begin
              rlink:=-1;
              pred(i,prod[i].laengde+1,rhs[t].parserp,rlink,s);
              while s<>nil do
              begin
                if oldprodno=i then write(blst,'         ')
                else write(blst,i:7,'  ');
                oldprodno:=i;
                if oldstate=ord(rhs[t].parserp) then write(blst,'          ')
                else write(blst,ord(rhs[t].parserp):7,'   ');
                oldstate:=ord(rhs[t].parserp);
                write(blst,ord(s),lf);
                pred(i,prod[i].laengde+1,rhs[t].parserp,rlink,s);
              end;
              t:=rhs[t].link;
            end;
          end;
        end;
     end; (* PREDTEST *)
 
     procedure looktestud(start:pointer; pnr:integer);
     var
       w,t:integer;
     begin (* UDSKRIV LOOKAHEADMAENGDERNE *)
       write(blst,ord(start),pnr); t:=25;
       for w:=0 to lalaengde-1 do
       begin
         outalf20(internrep[la[w]],dummy); t:=t+11;
         if t>60 then begin
            write(blst,lf,' ':20);
            t:=25;
          end;
       end;
       write(blst,lf,lf);
     end; (* OPTION 37 *)
 
     procedure testlrcond;
     var p,d: array [1..10] of integer;
       j,i:integer;
       r,t:pointer;
     begin
       for j:=1 to tilstnr do
       begin
         t:=tilstand[j].oldstart;
         r:=t; i:=0;
         while r<>nil do
         begin
           if r^.mode=0 then
            begin
              i:=i+1;
              p[i]:=r^.prodnr;
              d[i]:=prod[p[i]].laengde+1;
            end;
           r:=r^.derivp;
         end;
         if i>1 then
          begin
            write(blst, p[1], d[1], p[2], d[2], ord(t) );
            (*     IF LRCOND( P[1], D[1], P[2], D[2], T )
                   THEN WRITE(BLST,' NO LR(1)-CONFLICT',LF)
                   ELSE WRITE(BLST,' IS NOT LR(1)',LF);*)
          end;
       end;
     end; (* TESTLR *)
 
 
     procedure lookaheadtest;
     var
       i,t:integer;
     begin
       if options[40] then
        begin
          page(blst);write(blst,lf);
          writech('*',25);write(blst,' LOOKAHEAD-TEST '); writech('*',25);
          write(blst,lf);writech(' ',25);
          if options[27]  then write(blst,' OLD LOOKAHEAD',lf)
          else write(blst,' NEW LOOKAHEAD',lf);
          for i:=1 to antalprod do
          begin  t:=prod[i].start;
            while t<>rhsnil do
            begin
              if options[27]  then lalrlookahead(rhs[t].parserp,i)
                              else lookahead(rhs[t].parserp,i,0,la1);
              looktestud(rhs[t].parserp,i);
              t:=rhs[t].link;
            end;
          end;
          options[39]:=false;
        end;
     end; (* LOOKAHEADTEST *)
 
 
 
     (******************************************************************)
     (*                                                                *)
     (*                 ADEQUAD- BODY                                  *)
     (*                                                                *)
     (******************************************************************)
 
 
 
   begin
 
     initdot;
     (* file lalrk.pas must be inserted
        stack1:=nil; stack2:=nil;
        IF options[51] THEN lalrklookahead(1);
        IF options[52] THEN lalrklookahead(2);
        IF options[53] THEN lalrklookahead(3);
        IF options[54] THEN lalrklookahead(4);
        IF options[55] THEN lalrklookahead(5);
     *)
 
     if options[38] then predtest;
     if options[40] then lookaheadtest;
     if options[7] then msg('- OPTION 7 IGNORED                      ');
     if options[42] then testlrcond;
     lrok:=true ;
     headwrite:=true ;
     boo:=true ;
     for i:=1 to tilstnr do
     begin
       start:=tilstand[i].oldstart ;
       prodant:=0 ;
       termant:=0 ;
       helpp:=start ;
       repeat
         k:=helpp^.mode ;
         if (k=0) then
          prodant:=prodant+1
         else
          if ((helpp^.inf <= symbmax) and (helpp^.nextp<>nil)) then
           termant:=termant+1 ;
         helpp:=helpp^.derivp ;
       until (helpp=nil) ;
       if (prodant>const14) then
        consterror('ADEQUAD   ','CONST6    ',const6) ; updatemax(6,prodant);
 
       (* test if the state is inadequate or adequate       *)
       if ((prodant>1) or ((prodant=1) and (termant>0))) then
        begin (* inadequate state *)
          (* compute lookahead and add to items *)
          prodant:=0 ;
          termant:=0 ;
          helpp:=start ;
          repeat
            k:=helpp^.mode ;
            if (k=0) then
             begin
               pnr:=helpp^.prodnr ;
               lsymb:=prod[pnr].leftside ;
 
               (**********************************************)
               if options[27] then (* Old LookAhead *)
                lalrlookahead(start,pnr)
               else (* New LookAhead  *)
                lookahead(start,pnr,0,la1) ;
               (**********************************************)
 
               l:=lalaengde-1 ;
               allocp(lqbep1,1,'ADEQUAD   ');
               helpp^.nextp:=lqbep1 ;
               prodant:=prodant+1 ;
               lookant[prodant].ant:=lalaengde ;
               lookant[prodant].point:=lqbep1 ;
               lqbep3:= findreduce(pnr);
               for j:=0 to l do
               begin
                 lqbep2:=lqbep1 ;
                 with lqbep2^ do
                 begin
                   nextp:=lqbep3 ;
                   inf:=la[j] ;
                   prodnr:=pnr ;
                   mode:=4 ;
                   if (j=l) then
                    derivp:=helpp^.derivp
                   else
                    begin
                      allocp(lqbep1,1,'ADEQUAD   ');
                      derivp:=lqbep1 ;
                    end ;
                 end ;
               end ;
             end
            else
             with helpp^ do
             begin
               if ((inf <= symbmax) and (nextp<>nil)) then
                begin
                  termant:=termant+1 ;
                  if (termant > const2) then
                   consterror('ADEQUAD   ','CONST2    ',const2)
                  else
                   begin
                     stack[termant].symb:=inf ;
                     stack[termant].pnr:=prodnr ;
                     stack[termant].token:=mode ;
                   end ;
                end ;
               mode:=2 ;
             end ;
            helpp:=helpp^.derivp ;
          until (helpp=nil) ;
 
 
          (**************************************)
          (* test for conflicts in state: start *)
 
             testconflicts(start);
          (***************************************)
 
        end
       else
        if (prodant=0) then
         begin  (* adequate state of type shift *)
           helpp:=start ;
           while (helpp<>nil) do
           begin
             helpp^.mode:=1 ;
             helpp:=helpp^.derivp ;
           end ;
         end ;
       (*NU ER DENNE TILSTAND FAERDIG,HVIS LOOKAHEAD
         VAR NQDVENDIG ER DEN SAT IND
         DER MANGLER NU KUN AT BLIVE JUSTERET POINTERE.
         DER SKER UNDER OPTIMALISERING.OPTIMALISE-
         RING VIL KUN SKE HVIS GRAMMATIKKEN ER SLR1 *)
     end ;

(**************** experimental change ******************************)
(* A parser will be constructed even if the grammar is NON LALR(1) *)
(*    if (lrok) then
      begin*********) (* the grammar is LALR(1) *)
(*******************************************************************)
        (* Optimization is performed by removing superfluous entries *)
        for i:=1 to tilstnr do
        begin
          start:=tilstand[i].oldstart ;
          lastok:=start ;
          prodant:=0 ;
          termant:=0 ;
          count:=0 ;
          lqbep1:=start ;
          repeat
            helpp:=lqbep1 ;
            count:=count+1 ;
            with lqbep1^ do
            begin
              stopp:=derivp ;
              if ((mode=0) and (nextp<>nil)) then
               begin
                 (*NU ER DET EN REDUKTION
                   PRODANT,TERMANT,COUNT SIGER OM DER SKAL
                   VAERE NY INDGANG *)
                 if ((prodant=0) and (termant=0)) then
                  begin
                    helpp:=nextp;
                    optimalisering(nyindgang);
                  end
                 else
                  begin
                    helpp:=nextp ;
                    optimalisering(nyvej) ;
                  end ;
                 prodant:=prodant+1 ;
                 (*LASTOK SKAL VAERE DET SIDSTE
                   AF LOOKAHEADELEMENTERNE *)
                 repeat
                   lqbep3:=lastok^.derivp ;
                   if (lqbep3<>stopp) then
                    lastok:=lqbep3 ;
                 until (lqbep3=stopp) ;
               end
              else
               if (mode=0) then
                (*IN THIS STATE: ONLY ONE REDUCTION       *)
                (*IF ITS AN EMPTY REDUCTION, THEN         *)
                (*SOME NONTERMINAL TRANSITIONS MAY APPEAR *)
                with prod[prodnr] do
                begin mode:=3; nextp:=lookbackp; prodant:=prodant+1;
                  if laengde=0 then inf:=0 else inf:=laengde-1;
                  if count>1 then optimalisering(nyindgang);
                end
               else
                begin
                  if (inf <= symbmax) then
                   begin
                     (*NU ER DET ET TERMINAL SYMBOL *)
                     if (count>1) then
                      begin
                        if (nextp<>nil) then
                         begin
                           helpp:=lqbep1 ;
                           if ((prodant=0) and (termant=0)) then
                            optimalisering(nyindgang)
                           else
                            optimalisering(nyvej) ;
                         end
                        else
                         begin
                           helpp:=stopp ;
                           optimalisering(udenom) ;
                           termant:=termant-1 ;
                         end ;
                      end ;
                     termant:=termant+1 ;
                   end
                  else
                   begin (*NONTERMINAL TRANSITION *)
                     helpp:=derivp ;
                     if ((termant=0) and (prodant=0)) then
                      optimalisering(nyindgang)
                     else
                      begin
                        helpp:=stopp ;
                        optimalisering(udenom) ;
                      end ;
                   end ;
                end ;
            end ;
            lqbep1:=stopp ;
          until (lqbep1=nil) ;
        end ;
 
        (*******************************)
        if options[12] then adeqwrite(6);
        if lrok then lalrtext(1);
(********************************* experimental change ********)
(*    end********) (* IF LROK THEN *)
(*   else
      begin******) (* IF NOT LROK *)
      if lrok=false then
      begin adeqwrite(6);
         lalrtext(2);
       (****  stop(0) ;*********)
      end ;
     (*******************************)
 
   end ;  (* ADEQUAD *)
 
   procedure finalparser;
 
   type
     symbol=-1..const2;
     errorno=0..const1; (* changed from errno to avoid linking problem on Linux/jlk *)
     rslength=0..15;
     prodno=0..const1;
     lrinx=0..const7;
     lrelm=(*packed*) record
                     chain: lrinx;  (*NEXT ITEM IN THIS STATE*)
                     next : lrinx;  (*NEXT STATE*)
                     case kind: rslength (*TYPE OF STATE*) of
                        1,2,4,6: (symb: symbol; err: errorno);
                        0,3:     (rs: rslength; prodn: prodno);
                        5:     (lb: lrinx);
                     end; (*RECORD*)
   var
     lr: array[lrinx] of lrelm;
     smax,
     errorcount, (* set by errorTables *)
     firstt,last(* ,incr - used by stateNo - now obsolite *),i: integer;
 
 
     procedure copy(var ch:char; skip: boolean);
     begin
       if eof(parsin) then
        begin
          write(blst,lf); write(blst,' FILE PARSIN IS NOT A CORRECT PARSER ');
          msg('=ERROR(S) IN FILE   PARSIN              ');
          stop(0);
        end
       else
        (* changed by JLK to please p2c:
         * begin ch:=parsin^;
         *   if not skip then
         *    if eoln(parsin) then writeln(parsout)
         *    else write(blst,parsout,ch);
         * end;
         * get(parsin);*)
         begin
	   if not skip then
            if eoln(parsin) then begin read(parsin,ch); writeln(parsout) end
            else begin read(parsin,ch); write(parsout,ch) end
           else read(parsin,ch)
         end;
     end; (*COPY*)
 
 
     procedure search(skip : boolean);
     var
       a: array[1..5] of char;
       i: integer; found:boolean; ch: char;
     begin found:=false;
       a[1]:='B'; a[2]:='O'; a[3]:='B'; a[4]:='S'; a[5]:=' ';
       repeat copy(ch,skip);
         if ch='*' then
          begin   repeat copy(ch,skip) until ch<>'*';
            i:=1;
            while (a[i]=ch) and (i<5) do
            begin
              copy(ch,skip); i:=i+1;
            end;
            found:=i>4;
          end;
       until found;
       while not eoln(parsin) do copy(ch,skip); copy(ch,skip);
     end;(*SEARCH*)
 
function stateno(pt: pointer): integer;
var
   k,l,u,sno,ptSeq : integer;
begin	     
   if pt=nil then begin sno:=0; ptSeq:=0 end
   else
      begin (*BINARY SEARCH*)
	 l:=firstt; u:=last; ptSeq:=pt^.seq;
	 repeat k:=(l+u) div 2;
	    (* changed from:
	     *	  if ord(tilstand[k].oldstart) <= ord(pt) then l:=k+incr;
	     *    if ord(tilstand[k].oldstart) >= ord(pt) then u:=k-incr;
	     * by jlk to solve Linux problem
	     *)
	    if tilstand[k].oldstart^.seq <= ptSeq then l:=k+1;
	    if tilstand[k].oldstart^.seq >= ptSeq then u:=k-1;
	    (* changed from:
	     *    until (l*incr) > (u*incr);
	     * by jlk to solve Linux problem
	     *)
	 until l > u;
	 sno:=tilstand[k].newstart;
         if options[74] then
            writeln(blst,'stateno:',ord(tilstand[k].oldStart)
	   	   ,tilstand[k].oldstart^.seq:4
		   ,ord(pt),pt^.seq:4, k:4, tilstand[k].newstart:4);
      end;
   stateno:=sno;
end;(*STATENO*)
 
procedure emitconstants;
     var m: integer;
     begin
       if not options[32] then (*USE STANDARD SKELETON COMPILER *)
        begin reset(parsin,'parsin');   (*ON FILE PARSIN, AND DELIVER IT *)
          rewrite(parsout,'parsout'); (*ON FILE PARSOUT WITH INITIALISED CONSTANTS*)
          search(false);
          writeln(parsout,' goalSymbol=',goalhusk:1,';');
          writeln(parsout,' nontStart=',nontstart:1,';');
          writeln(parsout,' SYMBMAX=',nontslut:1,';');
          if errorcount < prodcount then m:=prodcount else m:=errorcount;
          writeln(parsout,' PRODMAX=',antalprod:1,';');
          writeln(parsout,' prodFMax=',m:1,';');
          writeln(parsout,' LRMAX=',smax:1,';');
          writeln(parsout,' LXMAX=',trmax:1,';');
          writeln(parsout,' ERRORVAL=',errorval:1,';');
          writeln(parsout,' NAMEVAL=',nameval:1,';');
          writeln(parsout,' CONSTVAL=',cstval:1,';');
          writeln(parsout,' STRINGVAL=',stringval:1,';');
          writeln(parsout,' STRINGCH=');
          if stringch='''' then writeln(parsout,''''''''';')
          else writeln(parsout,'''',stringch,''';');
          writeln(parsout,' COMBEGIN=',combegin:1,';') ;
          writeln(parsout,' COMLENGTH=',comlength:1,';') ;
          if options[57] or options[59] then
          begin writeln(parsout,' nontL=',nontl:1,';');
                writeln(parsout,' nontR=',nontr:1,';');
          end;
          search(true); writeln(parsout,' (*BOBS*) ');
          search(false);
        end;
       writeln(tables,goalhusk);writeln(tables,nontstart);
       writeln(tables,nontslut);writeln(tables,antalprod); writeln(tables,m);
       writeln(tables,smax);writeln(tables,trmax);
       writeln(tables,errorval);writeln(tables,nameval);
       writeln(tables,cstval);writeln(tables,stringval);
       if options[57] then writeln(tables,ord(stringch))
                      else writeln(tables,' ',stringch);
       writeln(tables,combegin);writeln(tables,comlength);
       if options[57] or options[59] then
       begin writeln(tables,nontl:1); writeln(tables,nontr:1) end;
     end; (*EMITCONSTANTS*)
 
     procedure emitlex;
     type
       lxinx=-256..const12; (* NOTE! CHAR MAY NOT CONTAIN MORE THAN 256 CHARS*)
       lxelm=(*packed*) record
                       np,hp: 0..const12;
                       tv: symbol;
                       ch: char
                    end;
 
     var
       lx: array[lxinx] of lxelm;
       tinx,t: integer;
       x: integer (* added by JLK to make p2c happy - see next p2c modification *);
       procedure convertlex;
       var c: char;
 
         procedure incrtinx;
         begin
           if tinx<const12 then tinx:=tinx+1
           else consterror('CONVERTLEX',' CONST12  ',const12);
           updatemax(12,tinx);
         end;
 
         procedure visit(p: termpointer);
         begin
           with p^, lx[tinx] do
           begin tv:=intern; ch:=tegn;
             if niveaup<>nil then
              begin incrtinx; np:=tinx;
                visit(niveaup);
              end
             else np:=0;
             if higherp<>nil then
              begin incrtinx; hp:=tinx;
                visit(higherp);
              end
             else hp:=0;
           end;
         end; (*VISIT*)
       begin
         (*TRANSFORM CLASS TERMTREE INTO ARRAY LX*)
         tinx:=0;
         lx[0].ch:=' '; lx[0].hp:=0; lx[0].np:=0; lx[0].tv:=0;
         (* LX[0] IS NOT USED *)
         for c:=minch to maxch do
         with lx[ord(c)-ord(maxch)-1], entry[c] do
         begin tv:=intern1; ch:=c;  np:=0;
           if termp<>nil then
            begin incrtinx; hp:=tinx;
              visit(termp);
            end
           else hp:=0;
         end;
       end; (*CONVERTLEX*)
 
     begin convertlex;
       for t:=-(ord(maxch)-ord(minch)+1) to tinx do
       with lx[t] do
       begin
         if options[57] then write(tables,ord(ch):1,' ')
                         else write(tables,' ',ch);
         write(tables,np:1,' ',hp:1,' ');
         x:=tv; if x<0 then writeln(tables,0:1) else writeln(tables,x:1);
         (* modified by JLK to please p2c:
          * Old: if tv<0 then writeln(tables,0:1) else writeln(tables,tv:1);
          *)
       end;
     end; (*EMITLEX*)
 
     procedure emitpars;
     var si: lrinx;
 
       function nolookahead(p:integer):boolean;
       var i:integer;
       begin
         if allnolook then nolookahead:=true else
          begin
            nolook[nolooki]:=p;
            i:=0;
            while nolook[i]<>p do i:=i+1;
            nolookahead:=(i<>nolooki);
          end;
       end;
 
 
     begin
       writeln(blst); writeln(blst); write(blst,' ');
       for si:=0 to smax do
       with lr[si] do
       begin
         if kind=3 then
          if nolookahead(rhs[prod[prodn].start].first) then kind:=7;
         if kind=7 then write(blst,'NOLOOKAHEAD ON ',prodn:1,lf);
         write(tables,chain:1,' ',next:1,' ',kind:1,' ');
         case kind of
            1,2,4,6: writeln(tables,symb:1,' ',err:1);
            0,3,7  : writeln(tables,rs:1,' ',prodn:1);
            5      : writeln(tables,lb:1);
         end;
       end;
     end; (*EMITPARS*)
 
(*     PROCEDURE emitLookBackEntry;
     VAR I: integer;
     BEGIN writeln(tables);
       FOR I:=nontStart to nontSlut do
         writeln(tables,stateNo(lookBackEntry[I]));
     END; *)
 
     procedure compress;
       (* THE CLASS PARSER IS COMPRESSED INTO THE ARRAY LR*)
     var
       state: integer;
       laoptim,tailoptim: boolean;
       statep: pointer;
       si,sstart: lrinx;
       seq: integer; (* added by jlk to avoid Linux problem *)
 
       procedure lapres(var start:pointer);
       var
         sp:pointer; m: integer;
       begin sp:=start;
         begintilst:=sp;
         fcqi:=0;       (*BEGINTILST AND FCQI ARE USED IN OPTIMIZE*)
         while sp<>nil do
         with sp^ do
         begin
           if mode = 4 then remember(nextp);
           sp:=derivp;
         end;
         m:=4;
         optimize(sp,m);
         allocp(classtop,1,'LAPRES    ');
         oldp^.derivp:=classtop; (*OLDP IS SET IN OPTIMIZE*)
         with classtop^ do
         begin inf:=0; prodnr:=m;
           mode:=4 ;nextp:=sp; derivp:=nil
         end;
         start:=begintilst;
       end; (*LAPRES*)
 
       procedure deletetail(s:integer);
       label 10,20;
       var t:integer;
         sinx,tinx,sx,tx,oldsinx,smatch: lrinx;
         sptr,tptr,sp,tp: pointer;
         maxmatch: boolean;
       begin t:=1; smatch:=const7; maxmatch:=false;
         while (t<s) and not maxmatch do
         begin sinx:=lr[sstart].chain; oldsinx:=sstart;
           sptr:=tilstand[s].oldstart^.derivp;
           while (sinx>0) and (sinx<smatch) do
           begin tinx:=tilstand[t].newstart; tptr:=tilstand[t].oldstart;
             while tinx>0 do
             begin
               if lr[sinx].symb=lr[tinx].symb then
                begin sx:=sinx; tx:=tinx; sp:=sptr; tp:=tptr;
                  while (sx>0) and (tx>0) do
                  with lr[sx],sp^ do
                  if (symb=lr[tx].symb) and (kind=lr[tx].kind)
                   and (nextp=tp^.nextp) then
                   begin sx:=chain; sp:=derivp;
                     tx:=lr[tx].chain; tp:=tp^.derivp;
                   end
                  else goto 10;
                  if sx=tx then (*SX=TX=0*)
                   begin (*SUCCESSFUL MATCH*)
                     maxmatch:=oldsinx=sstart;
                     smatch:=oldsinx; si:=smatch+1;
                     lr[smatch].chain:=tinx;
                     goto 20;
                   end;
                end;
               10:tinx:=lr[tinx].chain; tptr:=tptr^.derivp;
             end; (*WHILE TINX>0 DO*)
             oldsinx:=sinx; sinx:=lr[sinx].chain;
             sptr:=sptr^.derivp;
           end; (*WHILE SINX>0....*)
           20:t:=t+1;
         end;
       end; (*DELETETAIL*)
 
 
     begin (*COMPRESS*)
       laoptim:= not options[22]; tailoptim:= not options[29];
       si:=0;
 
       (*COPY PARSER TO LR AND MERGE IDENTICAL TAILS OF STATES*)
       for state:=0 to antaltilst do
       begin statep:=tilstand[state].oldstart;
         sstart:=si;
         tilstand[state].newstart:=sstart;
         if laoptim  and  (statep^.mode in [2,4]) then
	 begin lapres(statep);
	    seq:=tilstand[state].oldstart^.seq; (* added by jlk to avoid Linux problem *)
            tilstand[state].oldstart^:=statep^;
	    tilstand[state].oldstart^.seq:=seq; (* added by jlk to avoid Linux problem *)
          end;
         while statep<>nil do
         with lr[si],statep^ do
         begin
           if derivp=nil then chain:=0 else chain:=si+1;
           if (mode in [3,4]) then (*PRODNR IS UNDEF IF MODE=5*)
            if  (prod[prodnr].laengde=0) then mode:=6;
           kind:=mode;
           case mode of
              1,2,4,6:
                 begin  symb:=inf; err:=prodnr;
                    if mode <= 2 then err:=0;
                 end;
              3:
                 begin
                   rs:=inf; prodn:=prodnr;
                   if (prodn=0)
                     or (prodn > antalprod) (*see proc handleProd in LR0 *)
                   then begin kind:=0; prodn:=0; end;
                 end;
              5: ;
           end; (*CASE*)
           statep:=derivp;
           if si>=(const7-1) then consterror('COMPRESS  ','CONST7    ',const7);
           si:=si+1;
         end;
         if tailoptim and (lr[sstart].kind in [1,2,4]) then deletetail(state);
       end;
 
       smax:=si-1; (*INDEX OF LAST ELEMENT USED IN LR*)
 
       (*ADJUST NEXT AND LB IN LR BY MEANS OF ARRAY TILSTAND*)
 
	firstt:=0; last:=antaltilst; (* line added by jlk to solve Linux problem *)
	(*INITIALIZATIONS FOR THE FUNCTION STATENO
	 *  - obsolite due to new binary search method
	 *  - see changes, sept. 1994
	 * if ord(tilstand[0].oldstart) < ord(tilstand[antaltilst].oldstart) then
	 * begin incr:=1;
	 *  firstt:=0; last:=antaltilst;
         * end
         * else
         * begin incr:=-1;
         *   firstt:=antaltilst; last:=0;
         * end;
	 *)
	if options[17] then dump1;
	for state:=0 to antaltilst do
       begin sstart:=tilstand[state].newstart;
         statep:=tilstand[state].oldstart;
         si:=sstart;
         while statep<>nil do
         with lr[si], statep^ do
         begin next:=stateno(nextp);
           if mode=5 then lb:=stateno(lookbp);
           si:=chain;
           if si<sstart then statep:=nil (*REST OF THE STATE IS A TAIL*)
           else statep:=derivp;
         end;
       end;(*FOR*)
     end;(*COMPRESS*)
 
     procedure errortable ;
     label 33;
     var
       i,i5,no,j,StateIcount,StateJcount: integer;
       lqbep,testp,gemp: lrinx;
     begin page(blst); no:=0;
       write(blst,'***********************  COMPILER ERROR MESSAGES  ***********');
       write(blst,lf,lf,lf,' ');
       write(blst,'  ERRORNO : 0      ** ILLEGAL TERMINAL SYMBOL **');
       write(blst,lf,lf,lf,' ');
       write(blst,'  ERRORNO :        EXPECTED SYMBOL:');
       for i:=1 to antaltilst do tilstand[i].errorno:= 0;
       for i:=1 to antaltilst do with tilstand[i] do
       if ((lr[newstart].kind =1) and (errorno=0)) then
        begin if no<const1 then  no:= no+1
        else consterror('ERRORTABLE','CONST1    ',const1);
          updatemax(1,no);
          errorno:= no; i5:=0; lr[newstart].err:= no;
          lqbep:= newstart; write(blst,lf,lf,no,' :        ');
          StateIcount:=0;
          while lqbep<>0 do with lr[lqbep] do
          begin StateIcount:= StateIcount+1;
            if i5 > 50 then begin write(blst,lf,blank,blank); i5:=0; end;
            symbwrite(symb,i5); write(blst,' ');
            lqbep:= chain; i5:=i5+1;
          end;
          for j:= i+1 to antaltilst do
          if ((lr[tilstand[j].newstart].kind =1) and (tilstand[j].errorno=0)) 
          then
           begin lqbep:=newstart; gemp:=tilstand[j].newstart; 
             (* count no. of elements in 'gemp' *)
             StateJcount:=0; testp:=gemp;
             while testp<>0 do 
             begin StateJcount:=StateJcount+1; 
                   testp:=lr[testp].chain
             end;

             (* match StateI and StateJ *)
             while lqbep<>0 do with lr[lqbep] do
             begin testp:= gemp;
               while symb<> lr[testp].symb do
               begin testp:= lr[testp].chain; 
                 if testp=0 then goto 33;
               end;
               lqbep:= chain; 
             end;
             if StateIcount=StateJcount then with tilstand[j] do
              begin errorno:=no; lr[newstart].err:=no;
              end;
             33:  (* NOT IDENTICAL      *)
           end;
	end;
	writeln(blst); writeln(blst); writeln(blst);
       write(blst,'*********************************************************************');
       errorcount:=no;
     end;
 
     procedure emitlabels;
     var pn,i: integer;
         procedure spl(a: alfa);
         var i: integer;
         begin for i:=1 to alfalength do
               if a[i] <> ' ' then write(tables,a[i]);
         end;
         procedure spl20(a: alfa20);
         var i: integer;
         begin for i:=1 to alfal20 do
               if a[i] <> ' ' then write(tables,a[i]);
         end;
         procedure tv(p: pointer1);
         begin
            if p<> nil then
            with p^ do
            begin tv(llink); tv(rlink); write(tables,' ',nontermvaerdi:1,' ');
                spl(word1); spl(word2); spl(word3); writeln(tables)
         end end;
 
     begin writeln(tables);
       for pn:=1 to antalprod do
       begin write(tables,pn:5,' ');
         if options[56] then
         with prod[pn] do
         begin  write(tables,laengde:1,' ',leftside:1,' ');
             for i:= start+1 to start+laengde do
                 write(tables,rhs[i].symbol:1,' ');
         end;
         with rhs[prod[pn].start] do
         for i:=first to first+length-1 do
         write(tables,labelbuf[i]);
         writeln(tables);
       end;
       if options[56] then
       begin
           writeln(tables,nontstart:1,' ','StartSymbol');
           for i:=1 to nontstart-1 do
           begin write(tables,i:1,' '); spl20(internrep[i]); 
                 writeln(tables) 
           end;
           tv(first); (* nonterminals*)
       end;
     end; (*EMITLABELS*)
 
   begin (*FINALPARSER*)
     (*DELETE 'ERROR','NAME','KONST','STRING' AND 'EMPTY' FROM TERMTREE*)
     if go<>nil then with go^ do
      begin intern:=0; ok:=false; end;
     if gs<>nil then with gs^ do
      begin intern:=0; ok:=false; end;
     if gl<>nil then with gl^ do
      begin intern:=0; ok:=false; end;
     if gn<>nil then with gn^ do
      begin intern:=0; ok:=false; end;
     if gc<>nil then with gc^ do
      begin intern:=0; ok:=false; end;
 
     rewrite(tables,'tables');
 
     compress;
     errortable;
     emitconstants;
     if options[57] then
        for i:=1 to comlength do writeln(tables,ord(comend[i]):1)
     else  writeln(tables,comend:comlength) ;
     emitlex;
     if options[17] then dump1; (* TILSTANDS ARRAY *)
     emitpars;
(*     IF options[57] then emitLookBackEntry;*)
     if options[33] or options[34] then emitlabels;
      updatemax(7,smax+1);
   end; (*FINALPARSER*)
 
   (******************************************************)
   (*                                                    *)
   (*            M-A-I-N     PROGRAM                     *)
   (*                                                    *)
   (******************************************************)
 
    begin
       rewrite(blst,'bobslist');
       writeln('******** BOBS SYSTEM  - LALR(1) Parser Generator - Version 1.4');
       writeln(blst,'******** BOBS SYSTEM  - LALR(1) Parser Generator - Version 1.4 ********');
       writeln(blst,'******** DER ER BQF I BOBS!');
 
 
   (***** setting of default options              ***************)
     for i:=1 to const18 do options[i]:=false;
     options[28]:= true;    (* don't remove single productions  *)
     (* removed by JLK - is already done by generator:
      * options[32]:= true;    PARSIN and PARSOUT are ignored   
      *)
     options[56]:= true;    (* write(blst,ord(ch)) not ch on tables  *)
     options[57]:= true;    (* the grammar is written to tables *)
 
     page(blst);
     write(blst,'Default options:');
     for i:=1 to const18 do
        if options[i] then write(blst,i:1,' ');
     writeln(blst);
   (**************************************************************)

seqIndex:=0;
 
   initmax;
 
 
   mstime:=clock;
   (* HEAPCHECK('AT PROGRAM-START         '); *)
   ingrammar ;
   if not options[28] then
   begin options[28]:=true;
    writeln(blst,'Option 28 is ignored; single productions are not removed');
   end;
   if options[47] then timecheck('INGRAMMAR           ');
   if options[46] then heapcheck('AFTER INGRAMMAR     ');
   unused;
   idogfjern(true) ;
   termination ;
   erasure ;
   idogfjern(false);
   (*vhrecurs;*)
   if options[47] then timecheck('GRAMMAR-CHECKS      ');
   if options[46] then heapcheck('AFTER GRAMMAR-CHECKS');
   initprod ;
   inithelp;
   initempty;
 (*   RoseGram; *)
   outgrammar ; updatemax(1,antalprod); updatemax(2,nontslut);
   if options[47] then timecheck('OUT-GRAMMAR         ');
   if options[46] then heapcheck('AFTER OUT-GRAMMAR   ');
   if options[51] then goto 999;
 
   lr0;
   lookb; updatemax(10,antaltilst); updatemax(4,top);
   if options[47] then timecheck('LR0 & LOOKB         ');
   if options[46] then heapcheck('AFTER LR0 & LOOKB   ');
   (*msg(' *** adequad                            ');*)
   adequad;
   if options[47] then timecheck('ADEQUAD             ');
   if options[46] then heapcheck('AFTER ADEQUAD       ');
   if options[50] then goto 999; (* KUN RES. FRA ADEQUAD AF INTERESSE *)
   finalparser;
   if options[47] then timecheck('FINALPARSER         ');
   if options[46] then heapcheck('AT END OF PROGRAM   ');
   999: printmax;
 end.
 
 



