
void invoke_External(){
  int arg1,arg2,arg3;
  arg1 = op1(bc,&glsc);
#ifdef TRACE
        fprintf(trace,"invokeExternal: %i \n",arg1);
#endif
	switch (arg1) {
	case 1:
	  arg3 = vPop(thisStack);
	  arg2 = vPop(thisStack);
	  Y = rPop(thisStack); // origin - not used

#ifdef __ARDIUNO__
	  printf("pinMode(%i,%i)\n",arg2,arg3);
	  mraa_gpio_context pin = mraa_gpio_init(13);
	  if (arg3 == 0) 
	    {printf("OUTPUT\n"); mraa_gpio_dir(pin,MRAA_GPIO_OUT);}
	  else 
	    {mraa_gpio_dir(pin,MRAA_GPIO_IN);};
#endif
	  break;
	case 2:
	  arg3 = vPop(thisStack);
	  arg2 = vPop(thisStack);
	  Y = rPop(thisStack); // origin - not used
#ifdef __arm__
	  if (arg3 == 0)
	    {clr_led()}
	    else
	      {set_led()}}
#else
	  printf("digitalWrite(%i,%i)\n",arg2,arg3);
#endif
#ifdef __ARDIUNO__
	  if (arg3 == 0) 
	    {mraa_gpio_write(pin,LOW);}
	  else 
	    {mraa_gpio_write(pin,HIGH);};
#elif defined  __CYGWIN__
	  printf("digitalWrite(%i,%i) not implemented for this platform\n"
		 ,arg2,arg3);
#endif
	    break;        
	case 3:
	  arg2 = vPop(thisStack);
	  Y = rPop(thisStack); // origin - not used
#ifdef linux
	  sleep(arg2);
#endif
	  break;
	case 4:
#ifdef usekbhit
#ifdef linux
#elif defined __CYGWIN__
          arg1 = _getch();
#endif
	  Y = rPop(thisStack); // origin - not used
#ifdef TRACE
          fprintf(trace,"_getch: %i\n",arg1);
#endif
	  vPush(thisStack,arg1);
#else
	  runTimeError("_getch not included (Cygwin) or implemented (Linux)");
#endif
	  break;
	case 5:
#ifdef usekbhit
	  Y = rPop(thisStack); // origin - not used
#ifdef linux
#elif defined __CYGWIN__
	  vPush(thisStack,_kbhit());
#endif
#else
	  runTimeError("_kbhit not included (Cygwin) or implemented (Linux)");
#endif
	  break;
	case 6:
#ifdef usewinsock2
	  printf("InvokeExternal: new_socket== socket(AF_INET, SOCK_STREAM, 0)\n");
	  //arg1 = socket(AF_INET, SOCK_STREAM, 0);
	  Y = rPop(thisStack); // origin - not used
#ifdef linux
#elif defined  __CYGWIN__
	  arg1 = socket(AF_INET, SOCK_STREAM,0);
	  if (arg1 == INVALID_SOCKET)
	    printf("Invalid socket: %d\n", WSAGetLastError());
	  vPush(thisStack,arg1);
#endif
#ifdef __arm__
#else
	  printf("No winsock2 library included - check #define usewinsock2\n");
#endif
#endif
	  //vPush(thisStack,100);
	  break;
	case 7:
#ifdef usewinsock2
	  arg3 = vPop(thisStack); // port no
	  Y = rPop(thisStack);    // the name of the server to connect to
	  X = rPop(thisStack);    // origin - not used
	  arg1 = vPop(thisStack); // socket: sockfd
	  //mkCstring(Y);
	  //printf("Host: [%s]\n",mkCstring(Y));
#ifdef linux
#elif defined  __CYGWIN__
          msg = mkCstring(Y);
	  he = gethostbyname(msg);
#endif
	  //Cast the h_addr_list to in_addr ,
	  //since h_addr_list also has the ip address in long format only
#ifdef linux
#elif defined  __CYGWIN__
	  addr_list = (struct in_addr **) he->h_addr_list;
	  
	  for(i = 0; addr_list[i] != NULL; i++) 
	    { //Return the first one;
	      strcpy(ip , inet_ntoa(*addr_list[i]) );
	    }
	  printf("Connect: %i %s %s %i \n",arg1,msg,ip,arg2);
	  server.sin_addr.s_addr = inet_addr(ip);
	  server.sin_family = AF_INET;
	  server.sin_port = htons(arg3);
	  arg3 = connect(arg1 , (struct sockaddr *)&server , sizeof(server));
	  if (arg3 < 0) printf("Connect error\n");
#endif
	  vPush(thisStack,arg3);
#endif
	  break;
	case 8:
#ifdef usewinsock2
	  arg1 = vPop(thisStack);
	  X = rPop(thisStack); // The message to be send
	  Y = rPop(thisStack); // origin - not used
	  
	  //msg = "Hello world\r\n\r\n";
#ifdef linux
#elif defined  __CYGWIN__
	  msg = mkCstring(X);
	  //printf("Send: %i %s\n", arg1, msg);
	  arg3 = send(arg1,msg,strlen(msg),0);
	  if (arg3 < 0) printf("Send error\n");
#endif
	  vPush(thisStack,arg3);
#endif
	  break;
	case 9:
#ifdef useqinsock2
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack); // origin - not used
	  //printf("Recv: %i\n",arg1);
#ifdef linux
#elif defined  __CYGWIN__
	  msg = malloc(sizeof(char) * 2000);
	  arg2 = recv(arg1,msg,2000,0);
	  if (arg2 == SOCKET_ERROR){ 
	    arg3 = WSAGetLastError();
	    if (arg3 == WSAEWOULDBLOCK) { 
	      //printf("Recv NON-BLOCK\n");
	      rPush(thisStack,NULL);
	    } else {
	      printf("Recv failed with error code : %d\n" ,arg3);
	    }
	  }else {
	    msg[arg2] = 0;
	    //printf("Receive: %i %i %s\n",arg1,arg2,msg);
	    saveContext();
	    C2QBstring(thisBlock,msg);
	    restoreContext();
	  }
#endif
#endif
	  break;
	case 10:
#ifdef usewinsock2
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack);
#ifdef linux
#elif defined  __CYGWIN__
	  closesocket(arg1);
#endif
#endif
	  break;
	case 11:
#ifdef usewinsock2
	  arg2 = vPop(thisStack);
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack); // origin
	  printf("Bind: %i %i\n",arg1,arg2);
	  //Prepare the sockaddr_in structure
#ifdef linux
#elif defined  __CYGWIN__
	  server.sin_family = AF_INET;
	  server.sin_addr.s_addr = INADDR_ANY;
	  server.sin_port = htons( arg2 );
	  arg1 = bind(arg1 ,(struct sockaddr *)&server , sizeof(server));
	  if ( arg1 == SOCKET_ERROR)
	    {
	      printf("Bind failed with error code : %d" , WSAGetLastError());
	    }
#endif
	  vPush(thisStack,arg1);
#endif
	  break;
	case 12:
#ifdef usewinsock2
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack); // origin
#ifdef linux
#elif defined  __CYGWIN__
	  arg2 = listen(arg1,3);
#endif
#ifdef __arm__
#else
	  printf("Listen: %i %i\n",arg1,arg2);
#endif
#endif
	  break;
	case 13:
#ifdef usewinsock2
	  arg1 = vPop(thisStack);
	  Y = rPop(thisStack); // origin
#ifdef linux
#elif defined  __CYGWIN__
	  arg2 = sizeof(struct sockaddr_in);
	  //printf("Accept: %i\n",arg1);
	  arg2 = accept(arg1,(struct sockaddr *)&client, &arg2 );
	  //printf("After accept: %i\n",arg2);
	  if (arg2 ==  INVALID_SOCKET) {
	    arg3 = WSAGetLastError();
	    if (arg3 == WSAEWOULDBLOCK) {
	      //printf("Accept: no request in buffer\n");
	      arg2 = 1;
	    }else
	       printfs("accept failed with error code : %d\n" , arg3);
	  }
#endif
	  vPush(thisStack,arg2);
#endif
	  break;
	case 14:
#ifdef usewinsock2
	  arg2 = vPop(thisStack);
	  arg1 = vPop(thisStack);
          Y = rPop(thisStack); // origin
#ifdef linux
#elif defined  __CYGWIN__
	  u_long iMode = 1;
	  arg3 = ioctlsocket(arg1, FIONBIO,&iMode);
	  if (arg3 != NO_ERROR)
	    printf("ioctlsocket failed with error: %ld\n", arg3);  
#endif
#endif
}
