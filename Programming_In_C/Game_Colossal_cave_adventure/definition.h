
/*=====================================================================================
 * This Colossal Cave Adventure Game is developed based on the orginal Fortran version.
 * Purpose: Part of course Assignment (programming in the Unix Environment)
 * 
 * Author: Tewelle Gerechaal
 * 		   Blekinge Institute of Technology, BTH, Sweden
 *======================================================================================*/ 

// socket variables 
int listening_sockfd, new_fd;  // listen on litening_sock_fd, new connection on new_fd
char rcvd_msg[20];
char* snd_msg;
#define read_input read(new_fd,rcvd_msg,sizeof(rcvd_msg))

// game variables
int datfd;  /* message file descriptor      */
int delhit;
int yea;
extern char data_file[];                /* Virtual data file            */

#define TAB     011
#define LF      012 
#define FLUSHLINE while (getchar()!='\n')
#define FLUSHLF   while (next()!=LF)

int loc,newloc,oldloc,oldlc2,wzdark,gaveup,kq,k,k2;
char *wd1,*wd2;                         /* the complete words           */
int verb,obj,spk;
extern int blklin;
int saved,savet,mxscor,latncy;

#define SHORT 50                        /* How short is a demo game?    */

#define MAXSTR  20                      /* max length of user's words   */

#define HTSIZE  512                     /* max number of vocab words    */
struct hashtab                          /* hash table for vocabulary    */
{   int val;                        /* word type &index (ktab)      */
	char *atab;                     /* pointer to actual string     */
} voc[HTSIZE];

#define SEED 1815622                    /* "Encryption" seed            */

struct text
#ifdef OLDSTUFF
{       int seekadr;                    /* DATFILE must be < 2**16      */
#endif
{       char *seekadr;                  /* Msg start in virtual disk    */
	int txtlen;                     /* length of msg starting here  */
};

#define RTXSIZ  205			/*205 RANDOM MESSAGES (RTEXT, RTXSIZ).*/
struct text rtext[RTXSIZ];              /* random text messages         */

#define MAGSIZ  35		/* 35 MAGIC MESSAGES (MTEXT, MAGSIZ).              */
struct text mtext[MAGSIZ];              

int clsses;
#define CLSMAX  12				/* 12 DIFFERENT PLAYER CLASSIFICATIONS (CTEXT, CVAL, CLSMAX).*/
struct text ctext[CLSMAX];             
int cval[CLSMAX];

struct text ptext[101];                 /* object descriptions          */

#define LOCSIZ  141                     /* number of locations          */
struct text ltext[LOCSIZ];              /* long loc description         */
struct text stext[LOCSIZ];              /* short loc descriptions       */
/* directions & conditions of travel*/ 
struct travlist                        
{   struct travlist *next;          /* points to next list entry       */
	int conditions;                 /*M: condition to be checked before choosing action = (newloc / 1000) */
	int tloc;                       /* N--> a location, goto-label, or a messageto print  = (newloc % 1000) */
	int tverb;                      /* the verb that takes us there*/
} *travel[LOCSIZ],*tkk;                 /* travel is closer to keys(...)*/

int atloc[LOCSIZ];

int  plac[101];                         /* initial object placement     */
int  fixd[101],fixed[101];              /* location fixed?              */

int actspk[35];                         /* rtext msg for verb <n>  35 "ACTION" VERBS (ACTSPK, VRBSIZ).     */

int cond[LOCSIZ];                       /* various condition bits       */

extern int setbit[16];                  /* bit defn masks 1,2,4,...     */

int hntmax;
int hints[20][5];                       /*  hints  information              */
int hinted[20],hintlc[20];

int place[101], prop[101],link2[201];
int abb[LOCSIZ];

int maxtrs,tally,tally2;                /* treasure values              */

#define FALSE   0
#define TRUE    1
// mnemonics numbers
int keys,lamp,grate,cage,rod,rod2,steps,bird,door,pillow,snake,fissur,
	tablet,clam,oyster,magzin,dwarf,knife,food,bottle,water,oil,plant,plant2,axe,mirror,dragon,chasm,troll,
	troll2,bear,messag,vend,batter,nugget,coins,chest,eggs,tridnt,vase,emrald,pyram,pearl,rug,chain,
	spices,back,look,cave,null,entrnc,dprssn,enter, stream, pour,say,lock,throw,find,invent;
 
 /* dwarf stuff                  */
int chloc,chloc2,dseen[7],dloc[7],odloc[7],dflag,daltlc;

int tk[21],stick,dtotal,attack;
/* various flags & counters     */
int turns,lmwarn,iwest,knfloc,detail,   
	abbnum,maxdie,numdie,holdng,dkill,foobar,bonus,clock1,clock2,
	saved,closng,panic,closed,scorng;

int demo,newloc,limit;

//char *malloc();
//char *decr();
unsigned long crc();

/* We need to get a little tricky to avoid strings */
//#define DECR(a,b,c,d,e) decr('a'+'+','b'+'-','c'+'#','d'+'&','e'+'%')
