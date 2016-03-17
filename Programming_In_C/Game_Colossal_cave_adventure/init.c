
/*=====================================================================================
 * This Colossal Cave Adventure Game is developed based on the orginal Fortran version.
 * Purpose: Part of course Assignment (programming in the Unix Environment)
 * 
 * Author: Tewelle Gerechaal
 * 		   Blekinge Institute of Technology, BTH, Sweden
 *======================================================================================*/ 
 
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include "definition.h"

int blklin = TRUE;

int setbit[16] = {1,2,4,010,020,040,0100,0200,0400,01000,02000,04000,
		  010000,020000,040000,0100000};


void init(char* command)                           /* everything for 1st time run  */
                        /* command we were called with  */
{
	rdata();                        /* read data from orig. file    */
	linkdata();
	poof();
	prht();
	snd_msg="\nInitialization completed.\n";
	write(new_fd,snd_msg,strlen(snd_msg));//printf("Initialization succeeded\n");
}

/*char *decr(a,b,c,d,e)
char a,b,c,d,e;
{
	static char buf[6];
	
	buf[0] = a-'+';
	buf[1] = b-'-';
	buf[2] = c-'#';
	buf[3] = d-'&';
	buf[4] = e-'%';
	buf[5] = 0;
	printf("%s",buf);
	return buf;
	
} */

linkdata()                              /*  secondary data manipulation */
{      
	int i,j;

	/*      array linkages          */
	for (i=1; i<=LOCSIZ; i++)
		if (ltext[i].seekadr!=0 && travel[i] != 0)
			if ((travel[i]->tverb)==1) cond[i]=2;
	for (j=100; j>0; j--)
		if (fixd[j]>0)
		{       drop(j+100,fixd[j]);
			drop(j,plac[j]);
		}
	for (j=100; j>0; j--)
	{       fixed[j]=fixd[j];
		if (plac[j]!=0 && fixd[j]<=0) drop(j,plac[j]);
	}

	maxtrs=79;
	tally=0;
	tally2=0;

	for (i=50; i<=maxtrs; i++)
	{       if (ptext[i].seekadr!=0) prop[i] = -1;
		tally -= prop[i];
	}
	//printf("Defining mnemonics\n");
	/* DEFINE SOME HANDY MNEMONICS.  THESE CORRESPOND TO OBJECT NUMBERS. */
	keys = vocab("keys\0", 1);
	lamp = vocab("lamp\0", 1);
	grate = vocab("grate", 1);
	cage  = vocab("cage\0",1);
	rod   = vocab("rod\0\0",1);
	rod2=rod+1;
	steps=vocab("steps",1);
	bird  = vocab("bird\0",1);
	door  = vocab("door\0",1);
	pillow= vocab("pillo", 1);
	snake = vocab("snake", 1);
	fissur= vocab("fissu", 1);
	tablet= vocab("table", 1);
	clam  = vocab("clam\0",1);
	oyster= vocab("oyste", 1);
	magzin= vocab("magaz", 1);
	dwarf = vocab("dwarf", 1);
	knife = vocab("knife", 1);
	food  = vocab("food\0",1);
	bottle= vocab("bottl", 1);
	water = vocab("water", 1);
	oil   = vocab("oil\0\0",1);
	plant = vocab("plant", 1);
	plant2=plant+1;
	axe   = vocab("axe\0\0",1);
	mirror= vocab("mirro", 1);
	dragon= vocab("drago", 1);
	chasm = vocab("chasm", 1);
	troll = vocab("troll", 1);
	troll2=troll+1;
	bear  = vocab("bear\0",1);
	messag= vocab("messa", 1);
	vend  = vocab("vendi", 1);
	batter= vocab("batte", 1);

	nugget= vocab("gold\0",1);
	coins = vocab("coins", 1);
	chest = vocab("chest", 1);
	eggs  = vocab("eggs\0",1);
	tridnt= vocab("tride", 1);
	vase  = vocab("vase\0",1);
	emrald= vocab("emera", 1);
	pyram = vocab("pyram", 1);
	pearl = vocab("pearl", 1);
	rug   = vocab("rug\0\0",1);
	chain = vocab("chain", 1);

	back  = vocab("back\0",0);
	look  = vocab("look\0",0);
	cave  = vocab("cave\0",0);
	null  = vocab("null\0",0);
	entrnc= vocab("entra", 0);
	dprssn= vocab("depre", 0);
	enter = vocab("enter", 0);

	pour  = vocab("pour\0", 2);
	say   = vocab("say\0\0",2);
	lock  = vocab("lock\0",2);
	throw = vocab("throw", 2);
	find  = vocab("find\0",2);
	invent= vocab("inven", 2);
	//printf("Mnemonics finished\n");
	/* initialize dwarves */
	chloc=114;
	chloc2=140;
	for (i=1; i<=6; i++)
		dseen[i]=FALSE;
	dflag=0;
	dloc[1]=19;
	dloc[2]=27;
	dloc[3]=33;
	dloc[4]=44;
	dloc[5]=64;
	dloc[6]=chloc;
	daltlc=18;

	/* random flags & ctrs */
	turns=0;
	lmwarn=FALSE;
	iwest=0;
	knfloc=0;
	detail=0;
	abbnum=5;
	for (i=0; i<=4; i++)
		if (rtext[2*i+81].seekadr!=0) maxdie=i+1;
	numdie=holdng=dkill=foobar=bonus=0;
	clock1=30;
	clock2=50;
	saved=0;
	closng=panic=closed=scorng=FALSE;
}



void trapdel()                               /* come here if he hits escape   */
{	delhit++;			/* will be used by main to check, treats as stopage  */
	signal(SIGINT,trapdel);		/* catch subsequent quites (turns)        */
}

startup()
{
	time_t time();

	demo=Start(0);
	srand((int)(time((time_t *)NULL)));	/* random seed */
	/* srand(371);				/* non-random seed */
	hinted[3]=yes(65,1,0);
	newloc=1;
	delhit = 0;
	limit=330;
	if (hinted[3]) 
		limit=1000;      /* better batteries if instrucs */
}

