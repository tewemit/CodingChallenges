
/*=====================================================================================
 * This Colossal Cave Adventure Game is developed based on the orginal Fortran version.
 * Purpose: Part of course Assignment (programming in the Unix Environment)
 * 
 * Author: Tewelle Gerechaal
 * 		   Blekinge Institute of Technology, BTH, Sweden
 *======================================================================================*/ 
 


#include "definition.h"

int score()                                         /* sort of like 20000   */
{   int scor,i;
	mxscor=scor=0;
	for (i=50; i<=maxtrs; i++)
	{	if (ptext[i].txtlen==0) continue;
		k=12;
		if (i==chest) k=14;
		if (i>chest) k=16;
		if (prop[i]>=0) scor += 2;
		if (place[i]==3&&prop[i]==0) scor += k-2;
		mxscor += k;
	}
	scor += (maxdie-numdie)*10;
	mxscor += maxdie*10;
	if (!(scorng||gaveup)) scor += 4;
	mxscor += 4;
	if (dflag!=0) scor += 25;
	mxscor += 25;
	if (closng) scor += 25;
	mxscor += 25;
	if (closed)
	{   if (bonus==0) scor += 10;
		if (bonus==135) scor += 25;
		if (bonus==134) scor += 30;
		if (bonus==133) scor += 45;
	}
	mxscor += 45;
	if (place[magzin]==108) scor++;
	mxscor++;
	scor += 2;
	mxscor += 2;
	for (i=1; i<=hntmax; i++)
		if (hinted[i]) scor -= hints[i][2];
	return(scor);
}

void done(int entry)     /* entry=1 means goto 13000 */  /* game is over         */
					/* entry=2 means goto 20000 */ /* 3=19000 */
{   int i,sc;
	if (entry==1) mspeak(1);
	if (entry==3) rspeak(136);
	char* temp = "\n\nYou scored ";
	write(new_fd,temp,strlen(temp) );//temp = strcat((strcat(temp,score()+'0')),(strcat(" out of a possible ",mxscor+'0')));
	/*write(new_fd,score()+'0', strlen(score()+'0'));
	write(new_fd," out of maximum ",16);
	write(new_fd,mxscor+'0',strlen(mxscor+'0') );
	/*temp = strcat(temp,(strcat(" using ",turns+'0')," turns \n"));
	
	write(new_fd,temp,strlen(temp));
	*/
	//printf("\n\n\nYou scored %d out of a ",(sc=score()));
	//printf("possible %d using %d turns.\n",mxscor,turns);
	for (i=1; i<=clsses; i++)
		if (cval[i]>=sc)
		{       speak(&ctext[i]);
			if (i==clsses-1)
			{   
				char* tempin = "To accomplish the next higher rating would be tricky!\n\n Gratis!!\n\n";
				write(new_fd,tempin,strlen(tempin));
				//printf("To achieve the next higher rating");
				//printf(" would be a neat trick!\n\n");
				//printf("Congratulations!!\n");
				exit(0);
			}
			k=cval[i]+1-sc;
			char* tempin ="To achieve the next higher rating, you need ";
			write(new_fd,tempin,strlen(tempin));
			write(new_fd,k+'0',strlen(k+'0'));
			write(new_fd," more point",12 );
			
			if (k==1) write(new_fd,".\n",3 );//printf(".\n");
			else write(new_fd,"s.\n", 4);//printf("s.\n");
			exit(0);
		}
	printf("You just went off my scale!!!\n");
	exit(0);
}


int die(int entry)                                      /* label 90             */
{
	int i;
	if (entry != 99)
	{   
		rspeak(23);
		oldlc2=loc;
	}
	if (closng)                             /* 99                   */
	{   
		rspeak(131);
		numdie++;
		done(2);
	}
	yea=yes(81+numdie*2,82+numdie*2,54);
	numdie++;
	if (numdie==maxdie || !yea) done(2);
	place[water]=0;
	place[oil]=0;
	if (toting(lamp)) prop[lamp]=0;
	for (i=100; i>=1; i--)
	{       if (!toting(i)) continue;
		k=oldlc2;
		if (i==lamp) k=1;
		drop(i,k);
	}
	loc=3;
	oldloc=loc;
	return(2000);
}
