// Things to do:
//
//	1) provide +k<text> to specify include escape key
//	2) make include command syntax more user friendly
//  3) Fix ^ mapping

/*
			rdrprep
			Released under QPL 

	Author: James M. Morrison	jmorrison@ameritech.net
					jmm@ensose.com
	Update: Philip Young

	Execution environment: Linux

    This program prepares a deck for submission to a virtual card reader.
    It supports a rudimentary "include" facility which can be used to
    cause additional decks to be embedded into the resulting (combined)
    deck.  Includes are only recognized in ASCII input files, but
	included decks may include other decks up to a maximum level 
	(nested includes) specified by the FILE_DEPTH definition.

	The main input deck (specified on command line) is assumed to be 
	encoded in ASCII.

	The output deck will be in EBCDIC, fixed length (lrecl) records.

	Input lines longer than lrecl will be truncated, shorter lines
	padded out to lrecl length.

	ASCII input files are assumed to be of variable line length,
	EBCDIC input files are assumed to be of fixed (lrecl) length.

	2001-02-07	v 00.00 base release
	2001-04-07	v 00.01 ignore zero length ASCII input records
	2002-12-02	v 00.02 repair ASCII record length = 80 bug
	2020-08-09  v 00.03 Fixed pipe map, truncated record error warning, 
	                    rewrote arg parser, fixed make file, fixed new 
						line bug on ascii files.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

// --------------------------------------------------------------------
// Diagnostics section
// --------------------------------------------------------------------

#define diagflow(x)     \
	if (optflow == '+') \
	printf(x "\n")

// ------- Function prototypes ---------------------------------------

int putrec();
int getrec();
int close_include();
int open_include();
int parse_include();
int getASCIIline();
int getEBCDICline();
int cmdline(int, char *[]);
void printhelp();
void cleanup();
void ebcdic2ascii(void *, int);
void ascii2ebcdic(void *, int);
void data_dump(void *, int);

// -------  GLOBALS --------------------------------------------------

// Debugging

char optflow = '-'; // diagflow printed

// Options

char optabout = '-';	// don't display copyright info
char opthelp = '-';		// don't display general help
char optsyntax = '-';	// don't display syntax help
char optlist = '-';		// list records on stdout
char optdump = '-';		// dump records on stdout
char opttrunc = '+';	// truncate long ASCII lines
static int optdebug;	// debug
static int optverbose;	// verbose
static int opttruncate; // truncate long records
static int optprint;	// print

char *program = "rdrprep"; // program name
char *version = "0.3";
char *notprogram = "       "; // blanks same length as program
int fatal = 0;				  // 1 = abandon execution

FILE *fout = NULL;
char FNout[FILENAME_MAX] = "reader.jcl";
char include_key[20] = "::"; // include line prefix

unsigned char line[255];		 // work buffer
unsigned char ascii_line[255];	 // ASCII conversion of "line"
unsigned char include_line[255]; // include request line
int lrecl = 80;					 // EBCDIC output logical record length
int ascii_count;				 // # ASCII chars in "line"

unsigned char
	ebcdic_to_ascii[] = {
		"\x00\x01\x02\x03\xA6\x09\xA7\x7F\xA9\xB0\xB1\x0B\x0C\x0D\x0E\x0F"
		"\x10\x11\x12\x13\xB2\xB4\x08\xB7\x18\x19\x1A\xB8\xBA\x1D\xBB\x1F"
		"\xBD\xC0\x1C\xC1\xC2\x0A\x17\x1B\xC3\xC4\xC5\xC6\xC7\x05\x06\x07"
		"\xC8\xC9\x16\xCB\xCC\x1E\xCD\x04\xCE\xD0\xD1\xD2\x14\x15\xD3\xFC"
		"\x20\xD4\x83\x84\x85\xA0\xD5\x86\x87\xA4\xD6\x2E\x3C\x28\x2B\xD7"
		"\x26\x82\x88\x89\x8A\xA1\x8C\x8B\x8D\xD8\x21\x24\x2A\x29\x3B\x5E"
		"\x2D\x2F\xD9\x8E\xDB\xDC\xDD\x8F\x80\xA5\x7C\x2C\x25\x5F\x3E\x3F"
		"\xDE\x90\xDF\xE0\xE2\xE3\xE4\xE5\xE6\x60\x3A\x23\x40\x27\x3D\x22"
		"\xE7\x61\x62\x63\x64\x65\x66\x67\x68\x69\xAE\xAF\xE8\xE9\xEA\xEC"
		"\xF0\x6A\x6B\x6C\x6D\x6E\x6F\x70\x71\x72\xF1\xF2\x91\xF3\x92\xF4"
		"\xF5\x7E\x73\x74\x75\x76\x77\x78\x79\x7A\xAD\xA8\xF6\x5B\xF7\xF8"
		"\x9B\x9C\x9D\x9E\x9F\xB5\xB6\xAC\xAB\xB9\xAA\xB3\xBC\x5D\xBE\xBF"
		"\x7B\x41\x42\x43\x44\x45\x46\x47\x48\x49\xCA\x93\x94\x95\xA2\xCF"
		"\x7D\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\xDA\x96\x81\x97\xA3\x98"
		"\x5C\xE1\x53\x54\x55\x56\x57\x58\x59\x5A\xFD\xEB\x99\xED\xEE\xEF"
		"\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\xFE\xFB\x9A\xF9\xFA\xFF"};

unsigned char
	ascii_to_ebcdic[] = {
		"\x00\x01\x02\x03\x37\x2D\x2E\x2F\x16\x05\x25\x0B\x0C\x0D\x0E\x0F"
		"\x10\x11\x12\x13\x3C\x3D\x32\x26\x18\x19\x1A\x27\x22\x1D\x35\x1F"
		"\x40\x5A\x7F\x7B\x5B\x6C\x50\x7D\x4D\x5D\x5C\x4E\x6B\x60\x4B\x61"
		"\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\x7A\x5E\x4C\x7E\x6E\x6F"
		"\x7C\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xD1\xD2\xD3\xD4\xD5\xD6"
		"\xD7\xD8\xD9\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xAD\xE0\xBD\x5F\x6D"
		"\x79\x81\x82\x83\x84\x85\x86\x87\x88\x89\x91\x92\x93\x94\x95\x96"
		"\x97\x98\x99\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xC0\x4F\xD0\xA1\x07"
		"\x68\xDC\x51\x42\x43\x44\x47\x48\x52\x53\x54\x57\x56\x58\x63\x67"
		"\x71\x9C\x9E\xCB\xCC\xCD\xDB\xDD\xDF\xEC\xFC\xB0\xB1\xB2\xB3\xB4"
		"\x45\x55\xCE\xDE\x49\x69\x04\x06\xAB\x08\xBA\xB8\xB7\xAA\x8A\x8B"
		"\x09\x0A\x14\xBB\x15\xB5\xB6\x17\x1B\xB9\x1C\x1E\xBC\x20\xBE\xBF"
		"\x21\x23\x24\x28\x29\x2A\x2B\x2C\x30\x31\xCA\x33\x34\x36\x38\xCF"
		"\x39\x3A\x3B\x3E\x41\x46\x4A\x4F\x59\x62\xDA\x64\x65\x66\x70\x72"
		"\x73\xE1\x74\x75\x76\x77\x78\x80\x8C\x8D\x8E\xEB\x8F\xED\xEE\xEF"
		"\x90\x9A\x9B\x9D\x9F\xA0\xAC\xAE\xAF\xFD\xFE\xFB\x3F\xEA\xFA\xFF"};

int include_level = 0; // base input = 0
					   // index into FILE_STACK

typedef struct _FILE_INC
{							  // Included file
	char FNinc[FILENAME_MAX]; // filename
	FILE *finc;				  // file ptr
	char FMODEinc[20];		  // open mode string
	char FCHARSETinc;		  // A=ASCII, E=EBCDIC
} FILE_INC;

#define FILE_DEPTH 10			 // max include stacking depth
FILE_INC FILE_STACK[FILE_DEPTH]; // array of FILE_INCs

// --------------------------------------------------------------------
// Executable code
// --------------------------------------------------------------------

int main(int argc, char *argv[])
{
	int rc = 0;
	int eof_flag = 0;

	diagflow("enter main");
	rc = cmdline(argc, argv);
	if ((opthelp == '+') || (rc) || (fatal))
	{
		cleanup();
		return rc;
	}
	getrec();
	while ((include_level > -1) && !(eof_flag) && !(fatal))
	{
		putrec();
		if (!fatal)
			eof_flag = getrec();
	}
	cleanup();
	diagflow("exit main");
	return rc;
} /* main */

//--------------------------------------------------------------------

//* putrec: write EBCDIC record (always "lrecl" bytes) from "line"

int putrec()
{
	int i;

	diagflow("enter putrec");
	for (i = 0; i < lrecl; i++)
	{
		fputc(line[i], fout);
		if (ferror(fout))
		{
			printf("Error writing %s\n", FNout);
			perror("Execution terminated ");
			fatal = 1;
			break;
		}
	}

	if (optlist == '+')
	{
		memset(ascii_line, 0, sizeof(ascii_line));
		memcpy(ascii_line, line, lrecl);
		ebcdic2ascii(ascii_line, lrecl);
		for (i = 0; i < lrecl; i++)
		{ // mask unprintables
			if (!isprint(ascii_line[i]))
				ascii_line[i] = ' ';
		}
		printf("%s\n", ascii_line);
	}
	diagflow("exit putrec");
	return fatal;
} /* putrec */

//--------------------------------------------------------------------

//* getrec: read ASCII or EBCDIC input record
//* returns: EBCDIC line of length "lrecl" in "line"
//*          EOF when command line-specified file hits EOF

int getrec()
{
	int rc;

	diagflow("enter getrec");
	if (feof(FILE_STACK[0].finc))
	{
		if (optdebug)
			printf(">> getrec EOF %s",
				   FILE_STACK[include_level].FNinc);
		return EOF;
	}

	if (optdebug)
		printf(">> getrec %s\n",
			   FILE_STACK[include_level].FNinc);

	if (FILE_STACK[include_level].FCHARSETinc == 'E')
		rc = getEBCDICline();
	else
	{
		for (rc = -100; rc == -100;)
		{ // ignore zero length records
			rc = getASCIIline();
		}
	}
	diagflow("exit getrec");
	return rc;
} /* getrec */

//--------------------------------------------------------------------

//* close_include: close input file at EOF
//*                read next record (if any)
//* returns: EOF or 0 = record read

int close_include()
{
	int rc;

	diagflow("enter close_include");
	if (ferror(FILE_STACK[include_level].finc))
	{
		printf("Error reading %s\n",
			   FILE_STACK[include_level].FNinc);
		perror("Execution terminated ");
		fatal = 1;
		return fatal;
	}
	else
	{
		fclose(FILE_STACK[include_level].finc);
		if (optdebug)
			printf(">> close_include %s\n",
				   FILE_STACK[include_level].FNinc);

		include_level--;
		if (include_level > -1)
			rc = getrec(); // redrive read
		else
			rc = EOF;
	}
	diagflow("exit close_include");
	return rc;
} /* close_include */

//--------------------------------------------------------------------

//* open_include: given "include_key" at beginning of just-read line,
//*               handle opening the specified file
//* returns: EBCDIC line of length "lrecl" in "line" from included file

int open_include()
{
	int rc;

	diagflow("enter open_include");
	include_level++; // next level
	if (include_level >= FILE_DEPTH)
	{
		printf("Include depth exceeds allowed %d\n", FILE_DEPTH);
		fatal = 1;
		return fatal;
	}
	rc = parse_include();
	if (rc != 0)
	{
		include_level--;
		return fatal;
	}
	else
	{
		FILE_STACK[include_level].finc =
			fopen(FILE_STACK[include_level].FNinc, // attempt open
				  FILE_STACK[include_level].FMODEinc);
		if (FILE_STACK[include_level].finc == NULL)
		{
			printf("Error opening input file %s\n",
				   FILE_STACK[include_level].FNinc);
			if (optdebug)
			{
				printf(">> File mode %s\n",
					   FILE_STACK[include_level].FMODEinc);
				printf(">> Character set %c\n",
					   FILE_STACK[include_level].FCHARSETinc);
			}
			fatal = 1;
			return fatal;
		}
		else
		{
			if (optdebug)
			{
				printf(">> Opening %s\n",
					   FILE_STACK[include_level].FNinc);
				printf(">> File mode %s\n",
					   FILE_STACK[include_level].FMODEinc);
				printf(">> Character set %c\n",
					   FILE_STACK[include_level].FCHARSETinc);
			}
		}
		rc = getrec();
	}
	diagflow("exit open_include");
	return rc;
} /* open_include */

//--------------------------------------------------------------------

//* parse_include: parse include request lying in "include_line"
//* returns: FNinc, FMODEinc, FCHARSETinc

int parse_include()
{
	int i, j, rc = 0, valid;
	char charset_spec;

	diagflow("enter parse_include");
	valid = 0;
	i = strlen(include_key);
	charset_spec = include_line[i];
	charset_spec = toupper(charset_spec); // uppercase
	if (charset_spec == 'E')
	{
		strcpy(FILE_STACK[include_level].FMODEinc, "rb"); // EBCDIC mode
		FILE_STACK[include_level].FCHARSETinc = 'E';	  // EBCDIC charset
		i++;
		valid = 1;
	}
	if (charset_spec == 'A')
	{
		strcpy(FILE_STACK[include_level].FMODEinc, "r"); // ASCII mode
		FILE_STACK[include_level].FCHARSETinc = 'A';	 // ASCII charset
		i++;
		valid = 1;
	}
	if (valid)
	{
		memset(FILE_STACK[include_level].FNinc, 0, sizeof(FILE_STACK[include_level].FNinc));
		for (j = 0, i++; i < sizeof(line); i++, j++)
		{
			if (include_line[i] == 0x00)
				break;
			if (include_line[i] != ' ')
				FILE_STACK[include_level].FNinc[j] = include_line[i];
		}
		if (optdebug)
			printf("Parsed %s\n", FILE_STACK[include_level].FNinc);
	}
	else
	{
		printf("Error parsing include statement:\n");
		printf("%s\n", include_line);
		fatal = 1;
		return fatal;
	}
	diagflow("exit parse_include");
	return rc;
} /* parse_include */

//--------------------------------------------------------------------

//* getASCIIline: read line from newline-terminated ASCII file
//*               of variable length,
//*               Provides support for "include", honors opttrunc.

//* returns: EBCDIC line of length "lrecl" in "line"
//*          lines shorter than "lrecl" are padded with x'40'
//*          (EBCDIC blank)
//*          Sets ascii_count
//* returns EOF, 0 = record read, or -100 = record of length zero

int getASCIIline()
{
	int i, rc = 0;
	int oldchar = ' ';

	diagflow("enter getASCIIline");
	if (include_level == -1)
		return EOF;
	ascii_count = 0;
	memset(line, 0x40, lrecl); // EBCDIC blanks
	memset(ascii_line, 0, sizeof(ascii_line));
	for (i = 0; i < lrecl; i++)
	{
		oldchar = fgetc(FILE_STACK[include_level].finc);
		if (oldchar == EOF)
		{
		eof:
			if (ferror(FILE_STACK[include_level].finc))
			{
				printf("Error reading input\n");
				perror("Execution terminated");
				fatal = 1;
				return fatal;
			}
			else
			{
				rc = close_include(); // get EBCDIC line or EOF
				return rc;
			}
		}
		if (oldchar == '\n')
		{ // suppress newline
			if (i == 0)
			{ // include newline if its by itself
				ascii_line[i] = 32;
				ascii_count++;
			}
			break;
		}
		if (oldchar == '\r')
			break;
		ascii_line[i] = oldchar;
		ascii_count++;
	}
	i = 0;
	if (opttrunc == '+')
	{
		while (oldchar != '\n')
		{
			oldchar = fgetc(FILE_STACK[include_level].finc); // discard extraneous ASCII chars
			i++;
			if (oldchar == EOF)
			{
				if (i > 0 && optdump == '+')
					printf("Warning! Truncated %i records!\n", i);
				goto eof;
			}
		}
		if (i > 0 && optdump == '+')
			printf("Warning! Truncated %i records!\n", i);
	}
	if (ascii_count)
	{
		if (!memcmp(ascii_line, include_key, strlen(include_key)))
		{
			memset(include_line, 0, sizeof(include_line));
			memcpy(include_line, ascii_line, ascii_count);
			rc = open_include();
			if (fatal)
				return fatal;
			else
			{
			}
		}
		else
		{
			memcpy(line, ascii_line, ascii_count);
			ascii2ebcdic(line, ascii_count);
			if (optlist == '+')
				printf("getASCIIline %d %s\n", ascii_count, ascii_line);
			if (optdump == '+')
			{
				printf("getASCIIline dump ascii_line\n");
				data_dump(ascii_line, strlen(ascii_line));
				printf("getASCIIline dump line\n");
				data_dump(line, lrecl);
			}
		}
	}
	else
		rc = -100;
	diagflow("exit getASCIIline");
	return rc;
} /* getASCIIline */

//--------------------------------------------------------------------

//* getEBCDICline: read line from fixed lrecl EBCDIC file
//* returns: EBCDIC line of length "lrecl" in "line"

int getEBCDICline()
{
	int i, rc = 0, oldchar;

	diagflow("enter getEBCDICline");
	for (i = 0; i < lrecl; i++)
	{
		oldchar = fgetc(FILE_STACK[include_level].finc);
		if (feof(FILE_STACK[include_level].finc))
		{
			rc = close_include(); // returns record in "line" or EOF
			break;
		}
		if (ferror(FILE_STACK[include_level].finc))
		{
			printf("Error reading input %s\n",
				   FILE_STACK[include_level].FNinc);
			perror("Execution terminated");
			fatal = 1;
			return fatal;
		}
		else
		{
			line[i] = oldchar;
		}
	}
	diagflow("exit getEBCDICline");
	return rc;
} /* getEBCDICline */

//--------------------------------------------------------------------

//* Process command line:
//  setup options,
//  open main input and output files
//  init FILE_STACK

int cmdline(int argc, char *argv[])
{
	int argnum;
	int lenarg;
	int arghit;
	int opthit;
	char optchar;
	char *arg;
	int c;

	diagflow("enter cmdline");

	while (1)
	{
		int option_index = 0;
		static struct option long_options[] =
			{
				{"help", no_argument, NULL, 'h'},
				{"verbose", no_argument, &optverbose, 1},	   //optflow
				{"debug", no_argument, &optdebug, 1},		   //optdump
				{"no-truncate", no_argument, &opttruncate, 1}, //opttrunc
				{"print", no_argument, &optprint, 1},		   //optlist
				{"lrecl", required_argument, NULL, 'l'},
				{"version", no_argument, NULL, 'v'},
				{NULL, 0, NULL, 0}};

		c = getopt_long(argc, argv, "hl:", long_options, &option_index);
		if (c == -1)
			break;
		switch (c)
		{
		case 'h':
			//printf("Printing Help\n");
			printhelp();
			exit(0);
			break;
		case 'l':
			lrecl = atoi(optarg);
			break;
		case 'v':
			printf("rdrprep version: %s built: %s\n", version, __TIMESTAMP__);
			exit(1);
			break;
		case '?':
			printf("Unknown option %c\n", optopt);
			exit(1);
			break;
		case ':':
			printf("Option --lrecl/-l requires a record length.\n");
			break;
		}
	}

	if (argc - optind <= 0)
	{
		printhelp();
		exit(1);
	}

	if (optdebug)
	{
		optdump = '+';
		optflow = '+';
	}
	if (optverbose)
		optflow = '+';
	if (opttruncate)
		opttrunc = '-';
	if (optprint)
		optlist = '+';

	if (argc > optind)
	{ // argument = input filename
		memset(&FILE_STACK[include_level], 0, sizeof(FILE_INC));
		strcpy(FILE_STACK[include_level].FNinc, argv[optind]);
		strcpy(FILE_STACK[include_level].FMODEinc, "r");
		FILE_STACK[include_level].FCHARSETinc = 'A';
		optind++;

		FILE_STACK[include_level].finc =
			fopen(FILE_STACK[include_level].FNinc, // open cmdline input file
				  FILE_STACK[include_level].FMODEinc);
		if (FILE_STACK[include_level].finc == NULL)
		{
			printf("Error opening input file %s\n",
				   FILE_STACK[include_level].FNinc);
			fatal = 1;
			return fatal;
		}
	}

	if (argc > optind)
	{ // argument = output filename
		memset(FNout, 0, sizeof(FNout));
		strcpy(FNout, argv[optind]);
		optind++;
		fout = fopen(FNout, "wb");
	}
	else
	{
		fout = fopen(FNout, "wb");
	}

	if (fout == NULL)
	{
		printf("Error opening output file %s\n", FNout);
		fatal = 1;
		return fatal;
	}

	if (fatal)
	{
		printf("Execution terminated\n");
		return fatal;
	}
	diagflow("exit cmdline");
	return 0;
} /* cmdline */

//--------------------------------------------------------------------

//* Print syntax help

void printhelp()
{

	diagflow("enter printhelp");
	printf("rdrprep\n");
	printf("Copyright 2001-2002, James M. Morrison\n");
	printf("Version: %s \nBuilt:   %s\n", version, __TIMESTAMP__);
	printf("\n"
		   "This program prepares an ASCII file for submission to a Hercules virtual\n"
		   "card reader.  It reads the input file, and provides a mechanism to include\n"
		   "other (ASCII or EBCDIC) files.  Files are included by specifying an 'include' \n"
		   "statement (beginning in column 1) whose format is:\n"
		   "	::C [path]filename\n"
		   "where:\n"
		   "	:: 		are the include escape characters\n"
		   "	C 		either E (EBCDIC) or A (ASCII) for the included file's\n"
		   "			character set.  The case of E or A is not significant.\n"
		   "	[path]filename 	specifies the filename and optional path of the file\n"
		   "			to be included.\n"
		   "\n"
		   "The main input file (specified on the command line) is assumed to be in\n"
		   "ASCII.  ASCII files are assumed to be of variable line lengths, EBCDIC\n"
		   "files are assumed to be of fixed length.  All input lines are translated\n"
		   "to EBCDIC (if necessary), and blank padded or truncated to %d characters\n"
		   "(subject to the trunc option).  Include statements are only recognized \n"
		   "in ASCII input files.\n"
		   "\n",
		   lrecl);

	printf("\n");
	printf("Syntax: %s [options...] input [output]\n", program);
	printf("\n");
	printf(" input     input filename\n");
	printf(" output    output filename (default %s)\n", FNout);
	printf("\n"
		   "Options:\n"
		   "--help/-h		this help message\n"
		   "--version      prints version and build date\n"
		   "--verbose      be verbose\n"
		   "--debug        print debug information\n"
		   "--no-truncate  disable truncating after %d records\n"
		   "--print        print output in ASCII\n"
		   "--lrecl/-l     custom record length (default %d)"
		   "\n",
		   lrecl);

	diagflow("exit printhelp");
	return;
} /* printhelp */

//--------------------------------------------------------------------

//* Clean up prior to exiting

void cleanup()
{

	diagflow("enter cleanup");
	if (fout)
		fclose(fout);

	for (; include_level >= 0; include_level--)
	{
		if (FILE_STACK[include_level].finc)
			fclose(FILE_STACK[include_level].finc);
	}
	diagflow("exit cleanup");
	return;
} /* cleanup */

//--------------------------------------------------------------------
// Convert ASCII to EBCDIC
//--------------------------------------------------------------------

void ascii2ebcdic(void *in, int len)
{
	char *ptr;
	int i;
	unsigned char oldchar;
	unsigned char newchar;

	for (i = 0; i < len; i++)
	{
		ptr = &((char *)in)[i];
		oldchar = *ptr;
		newchar = ascii_to_ebcdic[oldchar];
		((unsigned char *)in)[i] = newchar;
	}
	return;
} /* ascii2ebcdic */

//--------------------------------------------------------------------
// Convert EBCDIC to ASCII
//--------------------------------------------------------------------

void ebcdic2ascii(void *in, int len)
{
	char *ptr;
	int i;
	unsigned char oldchar;
	unsigned char newchar;

	for (i = 0; i < len; i++)
	{
		ptr = &((char *)in)[i];
		oldchar = *ptr;
		newchar = ebcdic_to_ascii[oldchar];
		((unsigned char *)in)[i] = newchar;
	}
	return;
} /* ebcdic2ascii */

// Copied from dasdutil.c with minor mods to avoid finding BYTE
// and SPACE definitions:
/*-------------------------------------------------------------------*/
/* Subroutine to print a data block in hex and character format.     */
/*-------------------------------------------------------------------*/
void data_dump(void *addr, int len)
{
	unsigned int maxlen = 2048;
	unsigned int i, xi, offset, startoff = 0;
	unsigned char c;
	unsigned char *pchar;
	unsigned char print_chars[17];
	unsigned char hex_chars[64];
	unsigned char prev_hex[64] = "";
	int firstsame = 0;
	int lastsame = 0;

	pchar = (unsigned char *)addr;

	for (offset = 0;;)
	{
		if (offset >= maxlen && offset <= len - maxlen)
		{
			offset += 16;
			pchar += 16;
			prev_hex[0] = '\0';
			continue;
		}
		if (offset > 0)
		{
			if (strcmp(hex_chars, prev_hex) == 0)
			{
				if (firstsame == 0)
					firstsame = startoff;
				lastsame = startoff;
			}
			else
			{
				if (firstsame != 0)
				{
					if (lastsame == firstsame)
						printf("Line %4.4X same as above\n",
							   firstsame);
					else
						printf("Lines %4.4X to %4.4X same as above\n",
							   firstsame, lastsame);
					firstsame = lastsame = 0;
				}
				printf("+%4.4X %s %s\n",
					   startoff, hex_chars, print_chars);
				strcpy(prev_hex, hex_chars);
			}
		}

		if (offset >= len)
			break;

		memset(print_chars, 0, sizeof(print_chars));
		memset(hex_chars, ' ', sizeof(hex_chars));
		startoff = offset;
		for (xi = 0, i = 0; i < 16; i++)
		{
			c = *pchar++;
			if (offset < len)
			{
				sprintf(hex_chars + xi, "%2.2X", c);
				print_chars[i] = '.';
				if (isprint(c))
					print_chars[i] = c;
				c = ebcdic_to_ascii[c];
				if (isprint(c))
					print_chars[i] = c;
			}
			offset++;
			xi += 2;
			hex_chars[xi] = ' ';
			if ((offset & 3) == 0)
				xi++;
		} /* end for(i) */
		hex_chars[xi] = '\0';

	} /* end for(offset) */

} /* end function data_dump */

// <end>
