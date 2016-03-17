
/*=====================================================================================
 * This Colossal Cave Adventure Game is developed based on the orginal Fortran version.
 * Purpose: Part of course Assignment (programming in the Unix Environment)
 * 
 * Author: Tewelle Gerechaal
 * 		   Blekinge Institute of Technology, BTH, Sweden
 *======================================================================================*/ 


#include <stdio.h>
#include "definition.h"        /* SEED lives in there; keep them coordinated. */

#define USAGE "Usage: setup file > data.c (file is typically glorkz)\n"

#define YES 1
#define NO  0

void fatal();

#define LINE 10         /* How many values do we get on a line? */

main(argc, argv)
int argc;
char *argv[];
{
	FILE *infile;
	int c, count, linestart;

	if (argc != 2) fatal(USAGE);

	if ((infile = fopen(argv[1], "r")) == NULL)
		fatal("Can't read file %s.\n", argv[1]);
	puts("/*\n * data.c: created by tewayne from the ascii data file.");
	
	puts(" */");
	printf("\n\nchar data_file[] =\n{");
	srandom(SEED);
	count = 0;
	linestart = YES;

	while ((c = getc(infile)) != EOF)
	{
		if (linestart && c == ' ') /* Convert first spaces to tab */
		{
			printf("0x%02x,", ('\t' ^ random()) & 0xFF);
			while ((c = getc(infile)) == ' ' && c != EOF);
			/* Drop the non-whitespace character through */
			linestart = NO;
		}
		switch(c)
		{
		    case '\t':
			linestart = NO; /* Don't need to convert spaces */
			break;
		    case '\n':
			linestart = YES; /* Ready to convert spaces again */
			break;
		}
		if (count++ % LINE == 0)   /* Finished a line? */
			printf("\n\t");
		printf("0x%02x,", (c ^ random()) & 0xFF);
	}
	puts("\n\t0\n};");
	fclose(infile);
	exit(0);
}

void fatal(format, arg)
char *format;
{
	fprintf(stderr, format, arg);
	exit(1);
}
