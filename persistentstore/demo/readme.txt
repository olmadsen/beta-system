How to use the demo programs
-----------------------------------------

1. Start EnsembleDeamon
The "ensembleDeamon" program must run on all computers either running a
client or a server. The program can be found in ~beta/distribution/...

2. Start a server
You can use "psmanager" or "npsmanager" (or your own server). The difference
between the two sample servers is that the latter supports notifications.

3. Start one or more clients
Use "simpleClient" or "usenotclient". In both cases you have to supply the
name of the host machine on which the server is running, and also the 
persistent store you wish to open/create.
   The former implements a number of registers of persons (in the same 
persistent store), and you can add/delete/... persons and list registers etc.
   The latter focuses on the locking and notification mechanisms. It uses a 
graphical user interface which makes it easy to get an understanding of the
mechanisms.

/damm 10/8/98