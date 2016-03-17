/* Code for Producer/Consumer problem using mutex and condition variables */
/* To compile me for Unix, type:  gcc -o filename filename.c -lpthread */

#include <pthread.h>
#include <stdio.h>

#define BUFFER_SIZE 10 
#define NO_PRODUCERS 16
#define NO_CONSUMERS 32
#define KILO 1024
#define MEGA (KILO*KILO)
#define ITEMS_TO_SEND 8*MEGA /* number of items to pass through the buffer */

//#define ITEMS_TO_SEND 32
static int items_sent = 0;
static int items_recieved = 0;
typedef struct {
  char buf[BUFFER_SIZE];
  int items_onBuffer;
  int in, out;
  pthread_mutex_t mutex;
  pthread_cond_t add;
  pthread_cond_t take;
} buffer_t;

buffer_t buff;

void * producer(void *);
void * consumer(void *);



init_buffer(void)
{
    buff.in = 0;
    buff.out = 0;
    buff.items_onBuffer = 0;
}
main( int argc, char *argv[] )
{
  long i;

  pthread_cond_init(&(buff.add), NULL);
  pthread_cond_init(&(buff.take), NULL);



    pthread_t prod_thrs[NO_PRODUCERS];
    pthread_t cons_thrs[NO_CONSUMERS];
    pthread_attr_t attr;


    pthread_attr_init (&attr);

    printf("Buffer size = %d, items to send = %d\n",
       BUFFER_SIZE, ITEMS_TO_SEND);
       printf("\n The System is working....\n");
    /* create the producer and consumer threads */
    for(i = 0; i < NO_PRODUCERS; i++)
    pthread_create(&prod_thrs[i], &attr, producer, (void *)i);
    for(i = 0; i < NO_CONSUMERS; i++)
    pthread_create(&cons_thrs[i], &attr, consumer, (void *)i);

    //printf("CHERESEKU");
    pthread_attr_destroy(&attr);

    /* wait for all threads to terminate */
    for (i = 0; i < NO_PRODUCERS; i++)
    pthread_join(prod_thrs[i], NULL);
    for (i = 0; i < NO_CONSUMERS; i++)
    pthread_join(cons_thrs[i], NULL);


  printf("\nmain() reporting that all %d threads have terminated\n", i);

}  /* main */



void * producer(void *thr_id)
{
  int item;
  int i;
  int pquite=0;

  //printf("producer started.\n");
while(!pquite)
{
  if(items_sent<ITEMS_TO_SEND)
    { /* produce an item, one character from item[] */
      //printf("items_sent %d\n",items_sent);
      pthread_mutex_lock(&(buff.mutex));

      if (buff.items_onBuffer == BUFFER_SIZE)
       //printf("producer in waiting state.\n");
      while (buff.items_onBuffer == BUFFER_SIZE)
       pthread_cond_wait(&(buff.take), &(buff.mutex) );
      //printf("producer executing.\n");
      item=items_sent++;
      buff.buf[buff.in++] = item;
      buff.in = (buff.in+1)%BUFFER_SIZE;
      buff.items_onBuffer++;


     }
    else
     pquite=1;
     pthread_cond_signal(&(buff.add));
     pthread_mutex_unlock(&(buff.mutex));
}

  printf("producer exiting.\n");
  pthread_exit(0);
}

void * consumer(void *thr_id)
{
  int item;
  int i;
int c_quit=0;
  //printf("consumer started....\n");
  while(!c_quit) {
  if (items_recieved<ITEMS_TO_SEND)
  {
    //printf("items_recieved %d\n",items_recieved);
    pthread_mutex_lock(&(buff.mutex) );

    if (buff.items_onBuffer == 0)
    //printf("consumer waiting.\n");
    while(buff.items_onBuffer == 0)
    pthread_cond_wait(&(buff.add), &(buff.mutex) );
    //printf("consumer in execution.\n");

  item = buff.buf[buff.out++];
 // printf("%d\n",item);
  buff.out = (buff.out+1)%BUFFER_SIZE;
  buff.items_onBuffer--;
  items_recieved++;

  /* now: either buff.occupied > 0 and buff.nextout is the index
     of the next occupied slot in the buff, or
     buff.occupied == 0 and buff.nextout is the index of the next
     (empty) slot that will be filled by a producer (such as
     buff.nextout == buff.nextin) */

  pthread_cond_signal(&(buff.take));
  pthread_mutex_unlock(&(buff.mutex));
  }
  else
  c_quit=1;
  }
  //printf("consumer exiting.\n");
  pthread_exit(0);
}
