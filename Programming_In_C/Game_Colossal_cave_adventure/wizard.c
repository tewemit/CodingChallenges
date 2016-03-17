

# include "definition.h"
#include <string.h>

void datime(int *d,int *t)
{
	int tvec[2],*tptr;
	int *localtime();

	time(tvec);
	tptr=localtime(tvec);
	*d=tptr[7]+365*(tptr[5]-77);    /* day since 1977  (mod leap)   */
	/* bug: this will overflow in the year 2066 AD                  */
	/* it will be attributed to Wm the C's millenial celebration    */
	*t=tptr[2]*60+tptr[1];          /* and minutes since midnite    */
}                                       /* pretty painless              */


char magic[6];

void poof()
{
	strncpy(magic, "dwarf",sizeof(magic));
	latncy = 45;
}

int Start(n)
{      
	int d,t,delay;

	datime(&d,&t);
	delay=(d-saved)*1440+(t-savet); /* good for about a month     */

	if (delay >= latncy)
	{       saved = -1;
		return(FALSE);
	}
	printf("This adventure was suspended a mere %d minute%s ago.",
		delay, delay == 1? "" : "s");
	if (delay <= latncy/3)
	{       
		mspeak(2);
		exit(0);
	}
	mspeak(8);
	if (!wizard())
	{      
		mspeak(9);
		exit(0);
	}
	saved = -1;
	return(FALSE);
}

int wizard()                /* not as complex as advent/10 (for now)        */
{    
	int wiz;
	char *word,*x;
	if (!yesm(16,0,7)) return(FALSE);
	mspeak(17);
	getin(&word,&x);
	if (!weq(word,magic))
	{       mspeak(20);
		return(FALSE);
	}
	mspeak(19);
	return(TRUE);
}

void hejda(char* cmdfile)
{ 
	char *c;
	char fname[80];
	
	printf("What would you like to call the saved version?\n");
	for (c=fname;; c++)
		if ((*c=getchar())=='\n') break;
	*c=0;
	if (save(fname) != 0) return;           /* Save failed */
	printf("To resume, say \"adventure %s\".\n", fname);
	printf("\"With these rooms I might now have been familiarly acquainted.\"\n");
	exit(0);
}


long ran(int range)
{
	long rand(), i;

	i = rand() % range;
	return(i);
}
