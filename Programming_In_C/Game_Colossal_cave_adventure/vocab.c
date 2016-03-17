/*=====================================================================================
 * This Colossal Cave Adventure Game is developed based on the orginal Fortran version.
 * Purpose: Part of course Assignment (programming in the Unix Environment)
 * 
 * Author: Tewelle Gerechaal
 * 		   Blekinge Institute of Technology, BTH, Sweden
 *======================================================================================*/ 

# include "definition.h"

void dstroy(int object)
{       
	move(object,0);
}

juggle(int object)
{   
	int i,j;
	i=place[object];
	j=fixed[object];
	move(object,i);
	move(object+100,j);
}


move(int object,int where)
{   
	int from;
	if (object<=100)
		from=place[object];
	else
		from=fixed[object-100];
	if (from>0 && from<=300) carry(object,from);
	drop(object,where);
}


put(int object,int where,int pval)
{
	move(object,where);
	return(-1-pval);
}

carry(int object,int where)
{   
	int temp;
	if (object<=100)
	{     
		if (place[object]== -1) return;
		place[object] = -1;
		holdng++;
	}
	if (atloc[where]==object)
	{       atloc[where]=link2[object];
		return;
	}
	for (temp=atloc[where]; link2[temp]!=object; temp=link2[temp]);
	link2[temp]=link2[object];
}


drop(int object,int where)
{	
	if (object>100) 
		fixed[object-100]=where;
	else
	{     
		if (place[object]== -1) holdng--;
		place[object]=where;
	}
	if (where<=0) return;
		link2[object]=atloc[where];
	atloc[where]=object;
}

/* look up or store a word     
* -2 for store, -1 for user word, 
* >=0 for canned lookup used for storing only        
*/
int vocab(char* word,int type,int value)                  
{   
	int adr;
	char *s,*t;
	int hash, i;
	struct hashtab *h;

	for (hash=0,s=word,i=0; i<5 &&*s; i++)  /* some kind of hash    */
		hash += *s++;           /* add all chars in the word    */
	hash = (hash*3719)&077777;      /* pulled that one out of a hat */
	hash %= HTSIZE;                 /* put it into range of table   */

	for(adr=hash;; adr++)           /* look for entry in table      */
	{       if (adr==HTSIZE) 
				adr=0; /* wrap around                  */
		h = &voc[adr];          /* point at the entry           */
		switch(type)
		{   case -2:            /* fill in entry                */
				if (h->val)     /* already got an entry?        */
					goto exitloop2;
				h->val=value;
				h->atab=malloc(length(word));
				for (s=word,t=h->atab; *s;)
					*t++ = *s++ ^ '=';       /* encrypt slightly to thwart core reader       */
				*t=0^'=';
				
				/// printf("Stored \"%s\" (%d ch) as entry %d\n", word, length(word), adr);    
				return(0);      /* entry unused                 */
		    case -1:            /* looking up user word         */
				if (h->val==0) 
					return(-1);   /* not found    */
				for (s=word, t=h->atab;*t ^ '=';)
					if ((*s++ ^ '=') != *t++)
						goto exitloop2;
						
				if ((*s ^ '=') != *t && s-word<5) goto exitloop2;
				
				/* else the word is found and return it                */				
				return(h->val);
		    default:            /* looking up a registered key-word        */
			if (h->val==0)
			{     
				printf("Unable to find %s in vocab\n",word);
				exit(0);
			}
			//printf("found %s ",word);
			for (s=word, t=h->atab;*t ^ '=';)
				if ((*s++ ^ '=') != *t++) goto exitloop2;
			/* the word found                        */
			if (h->val/1000 != type)  // till type is found
				continue;
			// otherwise return type
			return(h->val%1000);
		}

	    exitloop2:      /* if hashed entry does not match  */            
		if (adr+1==hash || (adr==HTSIZE && hash==0))
		{       printf("Hash table overflow\n");
			exit(0);
		}
		
	}
}

 /* copy one string to another   
copystr(char *w1,char *w2)                         
{
	char *s,*t;
	for (s=w1,t=w2; *s;)
		*t++ = *s++;
	*t=0;
}*/

/* 
 * compare the user entered word (w1) and internal word (w2) 
 * 
 */
int weq(char* w1, char* w2)  
{   char *s,*t;
	int i;
	s=w1;
	t=w2;
	for (i=0; i<5; i++)             /* compare at most 5 chars, the common length     */
	{       
		if (*t==0 && *s==0)
			return(TRUE);
		if (*s++ != *t++) return(FALSE);
	}
	return(TRUE);
}

int length(char* str)                             
{   char *s;
	int n;
	for (n=0,s=str; *s++;) n++;
	return(n+1); /* includes 0 at end */
}

void prht()   /* print hash table             */
{   int i,j,l;
	char *c;
	struct hashtab *h;
	for (i=0; i<HTSIZE/10+1; i++)
	{       
		printf("%4d",i*10);
		for (j=0; j<10; j++)
		{       if (i*10+j>=HTSIZE) break;
			h= &voc[i*10+j];
			putchar(' ');
			if (h->val==0)
			{       printf("-----");
				continue;
			}
			for (l=0, c=h->atab; l<5; l++)
				if ((*c ^ '=')) putchar(*c++ ^ '=');
				else putchar(' ');
		}
		putchar('\n');
	}
}
