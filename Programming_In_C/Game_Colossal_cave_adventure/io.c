
/*=====================================================================================
 * This Colossal Cave Adventure Game is developed based on the orginal Fortran version.
 * Purpose: Part of course Assignment (programming in the Unix Environment)
 * 
 * Author: Tewelle Gerechaal
 * 		   Blekinge Institute of Technology, BTH, Sweden
 *======================================================================================*/ 


#include "definition.h"
#include <stdio.h>
#include <string.h>

getin(char **wrd1,char **wrd2) /* get command from user. no prompt, usually        */
{   
	char* s = malloc(sizeof(char));
	static char wd1buf[MAXSTR],wd2buf[MAXSTR];
	int first, numch,j,bytes;
	
	*wrd1=wd1buf;                   /* return ptr to internal string*/
	*wrd2=wd2buf;
	wd2buf[0]=0;                    /* in case it isn't set here    */
	numch=0;first=1;	
	
	memset(rcvd_msg,'\0',sizeof(rcvd_msg)); // reset storage.
	memset(*wrd1,'\0',MAXSTR); memset(*wrd2,'\0',MAXSTR);
	if((bytes=read_input)!=-1) // read user input commands
	 {
		 for(j=0,s=wd1buf;j<strlen(rcvd_msg)-2;++j)
		 {
			 if ((*s=rcvd_msg[j])>='A' && *s <='Z') 
				*s = *s - ('A' -'a');	/* convert to upper case        */
			if(*s==' ')
			{
				if (s==wd1buf||s==wd2buf)  /* first space   */
					continue;
				*s=0;
				if (first)      /* finished 1st wd; start 2nd   */
				{   
					first=numch=0;
					s=wd2buf;
					continue;//break;
				}
				else            /* finished 2nd word            */
				{       
					read_input;
					*s=0;
					return;
				}
				}
				else if(*s=='\n')
				{
					*s=0;
					return;
				}
				else
				{
					if (++numch>=MAXSTR)    /* string too long      */
					{   write_socket("Very long string. please give me a break.\n");
						wd1buf[0]=wd2buf[0]=0;
						read_input;
						return;
					}
					++s;
				}
		 }
			
		 /*write_socket(rcvd_msg);
		 printf("received: %s",rcvd_msg);
		 char* temp = malloc(sizeof(char)*strlen(rcvd_msg));
		 strcpy(temp,rcvd_msg); // back up b/c it will be corrupted in the following lines
		 *wrd1 = strtok(rcvd_msg," "); // first word
		 printf("rvd: %s", rcvd_msg);
		 *wrd2 = strstr(temp," "); // second word
		 printf("word1: %s",*wrd1);
		 printf("word2: %s",*wrd2);	 
		*/
		//printf("wrd1buf: %s",wd1buf);
		//write(new_fd,wd1buf, strlen(wd1buf));;
		//write(new_fd, wd2buf, strlen(wd2buf));write_socket("\n");
		
		
	}
	else write_socket("\nPlease enter a command\n");
}
void write_socket(char* msg)
{
	write(new_fd,msg,sizeof(msg));
}

int confirm(char* mesg)                           /* confirm irreversible action  */
{   int result;
	
	write(new_fd,mesg,sizeof(mesg));
	//printf("%s",mesg);              /* tell him what he did         */
	if((read_input!=-1) && (strcasecmp(rcvd_msg,"y")==0 || strncasecmp(rcvd_msg,"yes",3)==0)) //if (getchar()=='y')             /* was his first letter a 'y'?  */
		result=1;
	else    result=0;
	//read_input; //FLUSHLINE;
	return(result);
}
/*
 * Determine which texts should be read based on confirmation 
 */
int yes(int x,int y,int z)         /* do confirmation with rspeak         */
{   int result;
	//int bytes;
	while(1)
	{  
		rspeak(x);                     /* tell user what is needed */
		if((read_input!=-1) && (strncasecmp(rcvd_msg,"y",1)==0 || strncasecmp(rcvd_msg,"yes",3)==0))//if ((ch=getchar())=='y')
			result=TRUE;
		else if (strncasecmp(rcvd_msg,"n",1)==0 || strncasecmp(rcvd_msg,"no",2)==0)//ch=='n') 
			result=FALSE;
		//read_input;//FLUSHLINE;
		if ((strncasecmp(rcvd_msg,"n",1)==0 || strncasecmp(rcvd_msg,"no",2)==0)|| 
			(strncasecmp(rcvd_msg,"y",1)==0 || strncasecmp(rcvd_msg,"yes",3)==0))//ch=='y'|| ch=='n') 
			break;
		snd_msg="Please answer the question.\n";
		write(new_fd,snd_msg,strlen(snd_msg));
		
	}
	if (result==TRUE) rspeak(y);
	if (result==FALSE) rspeak(z);
	return(result);
}

int yesm(int x,int y,int z)                             /* confirm with mspeak          */
{   
	int result;

	while(1)
	{  
		mspeak(x);                     /* tell user what is wanted*/
		if((read_input!=-1) && (strncasecmp(rcvd_msg,"y",1)==0 || strncasecmp(rcvd_msg,"yes",3)==0))//if ((ch=getchar())=='y')
			result=TRUE;
			
		else if (strncasecmp(rcvd_msg,"n",1)==0 || strncasecmp(rcvd_msg,"no",2)==0)//ch=='n') 
			result=FALSE;
		//read_input;//FLUSHLINE;
		if ((strncasecmp(rcvd_msg,"n",1)==0 || strncasecmp(rcvd_msg,"no",2)==0)|| 
			(strncasecmp(rcvd_msg,"y",1)==0 || strncasecmp(rcvd_msg,"yes",3)==0))//ch=='y'|| ch=='n') 
			break;
		snd_msg="Please answer the question.\n";
		write(new_fd,snd_msg,strlen(snd_msg));
		//printf("Please answer the question.\n");
		
	}
	if (result==TRUE) mspeak(y);
	if (result==FALSE) mspeak(z);
	return(result);
}

/* FILE *inbuf,*outbuf; */

char *inptr;                            /* Pointer into virtual disk    */

int outsw = 0;				/* putting stuff to data file?  */

char iotape[] = "Ax3F'\003tt$8h\315qer*h\017nGKrX\207:!l";
char *tape = iotape;			/* pointer to encryption tape   */

int next()                                  /* next virtual char, bump adr  */
{
	int ch;

	ch=(*inptr ^ random()) & 0xFF;  /* Decrypt input data           */
	if (outsw)                      /* putting data in tmp file     */
	{   if (*tape==0) tape=iotape;  /* rewind encryption tape       */
	    *inptr = ch ^ *tape++;      /* re-encrypt and replace value */
	}
	inptr++;
	return(ch);
}

char breakch;                           /* tell which char ended rnum   */

void rdata()                                 /* "read" data from virtual file*/
{   int sect;
	char ch;
	inptr = data_file;              /* Pointer to virtual data file */
	srandom(SEED);                  /* which is lightly encrypted.  */

	clsses=1;
	for (;;)                        /* read data sections           */
	{ 
		sect=next()-'0';        /* 1st digit of section number  */
#ifdef VERBOSE
		write(new_fd, "section "+sect+'0',strlen("section "+sect+'0'));//write_socket;
		//printf("Section %c",sect+'0');
#endif
		if ((ch=next())!=LF)    /* is there a second digit?     */
		{
			FLUSHLF; //read_file;
#ifdef VERBOSE
			putchar(ch);
#endif
			sect=10*sect+ch-'0';
		}
#ifdef VERBOSE
		putchar('\n');
#endif
		switch(sect)
		{   case 0:             /* finished reading database    */
			return;
		    case 1:             /* long form descriptions       */
			rdesc(1);
			break;
		    case 2:             /* short form descriptions      */
			rdesc(2);
			break;
		    case 3:             /* travel table                 */
			rtrav();   break;
		    case 4:             /* vocabulary                   */
			rvoc();
			break;
		    case 5:             /* object descriptions          */
			rdesc(5);
			break;
		    case 6:             /* arbitrary messages           */
			rdesc(6);
			break;
		    case 7:             /* object locations             */
			rlocs();   break;
		    case 8:             /* action defaults              */
			rdflt();   break;
		    case 9:             /* liquid assets                */
			rliq();    break;
		    case 10:            /* class messages               */
			rdesc(10);
			break;
		    case 11:            /* hints                        */
			rhints();  break;
		    case 12:            /* magic messages               */
			rdesc(12);
			break;
		    default:
			printf("Invalid data section number: %d\n",sect);
			for (;;) putchar(next());
		}
		if (breakch!=LF)        /* routines return after "-1"   */
			FLUSHLF;
	}
}

char nbf[12];


rnum()                                  /* read initial location num    */
{       register char *s;
	tape = iotape;                  /* restart encryption tape      */
	for (s=nbf,*s=0;; s++)
		if ((*s=next())==TAB || *s=='\n' || *s==LF)
			break;
	breakch= *s;                    /* save char for rtrav()        */
	*s=0;                           /* got the number as ascii      */
	if (nbf[0]=='-') return(-1);    /* end of data                  */
	return(atoi(nbf));              /* convert it to integer        */
}

char *seekhere;

rdesc(sect)                             /* read description-format msgs */
int sect;
{       register char *s,*t;
	register int locc;
	char *seekstart, *maystart, *adrstart;
	char *entry;

	seekhere = inptr;               /* Where are we in virtual file?*/
	outsw=1;                        /* these msgs go into tmp file  */
	for (oldloc= -1, seekstart=seekhere;;)
	{       maystart=inptr;         /* maybe starting new entry     */
		if ((locc=rnum())!=oldloc && oldloc>=0  /* finished msg */
		    && ! (sect==5 && (locc==0 || locc>=100)))/* unless sect 5*/
		{       switch(sect)    /* now put it into right table  */
			{   case 1:     /* long descriptions            */
				ltext[oldloc].seekadr=seekhere;
				ltext[oldloc].txtlen=maystart-seekstart;
				break;
			    case 2:     /* short descriptions           */
				stext[oldloc].seekadr=seekhere;
				stext[oldloc].txtlen=maystart-seekstart;
				break;
			    case 5:     /* object descriptions          */
				ptext[oldloc].seekadr=seekhere;
				ptext[oldloc].txtlen=maystart-seekstart;
				break;
			    case 6:     /* random messages              */
				if (oldloc>RTXSIZ)
				{    
					printf("Too many random msgs\n");
					exit(0);
				}
				rtext[oldloc].seekadr=seekhere;
				rtext[oldloc].txtlen=maystart-seekstart;
				break;
			    case 10:    /* class messages               */
				ctext[clsses].seekadr=seekhere;
				ctext[clsses].txtlen=maystart-seekstart;
				cval[clsses++]=oldloc;
				break;
			    case 12:    /* magic messages               */
				if (oldloc>MAGSIZ)
				{       printf("Too many magic msgs\n");
					exit(0);
				}
				mtext[oldloc].seekadr=seekhere;
				mtext[oldloc].txtlen=maystart-seekstart;
				break;
			    default:
				printf("rdesc called with bad section\n");
				exit(0);
			}
			seekhere += maystart-seekstart;
		}
		if (locc<0)
		{       outsw=0;        /* turn off output              */
			seekhere += 3;  /* -1<delimiter>                */
			return;
		}
		if (sect!=5 || (locc>0 && locc<100))
		{       if (oldloc!=locc)/* starting a new message       */
				seekstart=maystart;
			oldloc=locc;
		}
		FLUSHLF;                /* scan the line                */
	}
}


rtrav()                                 /* read travel table            */
{       register int locc;
	register struct travlist *t;
	register char *s;
	char buf[12];
	int len,m,n,entries;
	for (oldloc= -1;;)              /* get another line             */
	{       if ((locc=rnum())!=oldloc && oldloc>=0) /* end of entry */
		{
			t->next = 0;    /* terminate the old entry      */
		/*      printf("%d:%d entries\n",oldloc,entries);       */
		/*      twrite(oldloc);                                 */
		}
		if (locc== -1) return;
		if (locc!=oldloc)        /* getting a new entry         */
		{       t=travel[locc]=(struct travlist *) malloc(sizeof (struct travlist));
		/*      printf("New travel list for %d\n",locc);        */
			entries=0;
			oldloc=locc;
		}
		for (s=buf;; *s++)      /* get the newloc number /ASCII */
			if ((*s=next())==TAB || *s==LF) break;
		*s=0;
		len=length(buf)-1;      /* quad long number handling    */
	/*      printf("Newloc: %s (%d chars)\n",buf,len);              */
		if (len<4)              /* no "m" conditions            */
		{       m=0;
			n=atoi(buf);    /* newloc mod 1000 = newloc     */
		}
		else                    /* a long integer               */
		{       n=atoi(buf+len-3);
			buf[len-3]=0;   /* terminate newloc/1000        */
			m=atoi(buf);
		}
		while (breakch!=LF)     /* only do one line at a time   */
		{       if (entries++) t=t->next=(struct travlist *) malloc(sizeof (struct travlist));
			t->tverb=rnum();/* get verb from the file       */
			t->tloc=n;      /* table entry mod 1000         */
			t->conditions=m;/* table entry / 1000           */
		/*      printf("entry %d for %d\n",entries,locc);       */
		}
	}
}

#ifdef DEBUG

twrite(loq)                             /* travel options from this loc */
int loq;
{   struct travlist *t;
	printf("If");
	speak(&ltext[loq]);
	printf("then\n");
	for (t=travel[loq]; t!=0; t=t->next)
	{       printf("verb %d takes you to ",t->tverb);
		if (t->tloc<=300)
			speak(&ltext[t->tloc]);
		else if (t->tloc<=500)
			printf("special code %d\n",t->tloc-300);
		else
			rspeak(t->tloc-500);
		printf("under conditions %d\n",t->conditions);
	}
}

#endif

void rvoc()
{   char *s;               /* read the vocabulary          */
	int index;
	char buf[6];
	for (;;)
	{   index=rnum();
		if (index<0) break;
		for (s=buf,*s=0;; s++)  /* get the word                 */
			if ((*s=next())==TAB || *s=='\n' || *s==LF
				|| *s==' ') break;
			/* terminate word with newline, LF, tab, blank  */
		if (*s!='\n' && *s!=LF) FLUSHLF;  /* can be comments    */
		*s=0;
	/*      printf("\"%s\"=%d\n",buf,index);*/
		vocab(buf,-2,index);
	}
/*	prht();	*/
}


void rlocs()                                 /* initial object locations     */
{	for (;;)
	{       if ((obj=rnum())<0) break;
		plac[obj]=rnum();       /* initial loc for this obj     */
		if (breakch==TAB)       /* there's another entry        */
			fixd[obj]=rnum();
		else    fixd[obj]=0;
	}
}

void rdflt()                                 /* default verb messages        */
{	for (;;)
	{       if ((verb=rnum())<0) break;
		actspk[verb]=rnum();
	}
}

void rliq()                                  /* liquid assets &c: cond bits  */
{       register int bitnum;
	for (;;)                        /* read new bit list            */
	{       if ((bitnum=rnum())<0) break;
		for (;;)                /* read locs for bits           */
		{       cond[rnum()] |= setbit[bitnum];
			if (breakch==LF) break;
		}
	}
}

void rhints()
{       register int hintnum,i;
	hntmax=0;
	for (;;)
	{       if ((hintnum=rnum())<0) break;
		for (i=1; i<5; i++)
			hints[hintnum][i]=rnum();
		if (hintnum>hntmax) hntmax=hintnum;
	}
}


rspeak(int msg)
{
	if (msg!=0) speak(&rtext[msg]);
}


mspeak(int msg)
{
	if (msg!=0) speak(&mtext[msg]);
}


speak(struct text *msg)    /* read, decrypt, and print a message (not ptext)      */
							/* msg is a pointer to seek address and length of mess */
{
	char *s, nonfirst;
	s = msg->seekadr;
	nonfirst=0;
	char buf[msg->txtlen];
	int i=0;
	//char sndmsg[1024];// =malloc(1024*sizeof(char));
	while (s - msg->seekadr < msg->txtlen)  /* read a line at a time */
	{       tape=iotape;            /* restart decryption tape      */
		while ((*s++ ^ *tape++) != TAB); /* read past loc num       */
		/* assume tape is longer than location number           */
		/*   plus the lookahead put together                    */
		if ((*s ^ *tape) == '>' && (*(s+1) ^ *(tape+1)) == '$' &&(*(s+2) ^ *(tape+2)) == '<') 
			break;
		if (blklin && !nonfirst++) 
		{
			buf[i] = '\n'; ++i; //putchar('\n');
		}
		do
		{  
			if (*tape == 0) tape = iotape;/* rewind decryp tape */
			{
				buf[i]=(*s ^ *tape); //putchar(*s ^ *tape); //write_socket(*s ^ *tape);//strcat(sndmsg,(*s ^ *tape));//
				++i;
			}	
		} while ((*s++ ^ *tape++) != LF);   /* better end with LF   */
	}
	write(new_fd,buf,strlen(buf));
}


void pspeak(int m,int skip) /* read, decrypt an print a ptext message              */
							/* msg is the number of all the p msgs for this place  */
							/* assumes object 1 doesn't have prop 1, obj 2 no prop 2 &c*/
{
	char *s,nonfirst;
	char *numst, save;
	struct text *msg;
	char *tbuf;

	msg = &ptext[m];
	if ((tbuf=(char *) malloc(msg->txtlen) + 1) == 0) bug(108);
	memcpy(tbuf, msg->seekadr, msg->txtlen + 1);   /* Room to null */
	s = tbuf;
	nonfirst=0;
	char sktbuf[msg->txtlen];
	int i=0;
	while (s - tbuf < msg->txtlen) /* read line at a time */
	{       tape=iotape;            /* restart decryption tape      */
		for (numst=s; (*s^= *tape++)!=TAB; s++); /* get number  */

		save = *s; /* Temporarily trash the string (cringe) */
		*s++ = 0; /* decrypting number within the string          */

		if (atoi(numst) != 100 * skip && skip >= 0)
		{       while ((*s++^*tape++)!=LF) /* flush the line    */
				if (*tape==0) tape=iotape;
			continue;
		}
		if ((*s^*tape)=='>' && (*(s+1)^*(tape+1))=='$' &&
			(*(s+2)^*(tape+2))=='<') break;
		if (blklin && ! nonfirst++) 
		{
			sktbuf[i]= '\n'; //putchar('\n');
			++i;
		}
		do
		{   if (*tape==0) tape=iotape;
			sktbuf[i]= (*s^*tape); //putchar(*s^*tape);
			++i;
		} while ((*s++^*tape++)!=LF);   /* better end with LF   */
		if (skip<0) break;
	}
	write(new_fd,sktbuf,strlen(sktbuf));
	//free(tbuf);
}
