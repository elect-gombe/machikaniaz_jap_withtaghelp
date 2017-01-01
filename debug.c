/*
   This file is provided under the LGPL license ver 2.1.
   Written by K.Tanaka & Katsumi
   http://www.ze.em-net.ne.jp/~kenken/index.html
   http://hp.vector.co.jp/authors/VA016157/
*/

#ifdef __DEBUG

#include <xc.h>
#include "api.h"
#include "main.h"
#include "compiler.h"

/*
	Enable following line when debugging binary object.
*/
//#include "debugdump.h"


// Pseudo reading config setting for debug mode
unsigned int g_DEVCFG1=0xFF7F4DDB;

// Construct jump assembly in boot area.
const unsigned int _debug_boot[] __attribute__((address(0xBFC00000))) ={
	0x0B401C00,//   j           0x9d007000
	0x00000000,//   nop         
};

// Use DEBUG.HEX as file name of this program.
const unsigned char _debug_filename[] __attribute__((address(FILENAME_FLASH_ADDRESS))) ="DEBUG.HEX";

static const char initext[];
static const char bastext[];

static char* readtext;
static int filepos;

/*
	Debug dump
	In debugdump.h:
		__DEBUGDUMP is defined.
		__DEBUGDUMP_FREEAREA is defined as start address of free area (1st argument of set_free_area() function)
		const unsigned char dump[] is initialized.
*/
#ifdef __DEBUGDUMP
int debugDump(){
	int i;
	for(i=0;i<sizeof dump;i++){
		RAM[i]=dump[i];
	}

	g_objpos=(__DEBUGDUMP_FREEAREA-(unsigned int)g_object)/4;

	// Initialize parameters
	g_pcg_font=0;
	g_use_graphic=0;
	g_graphic_area=0;
	clearscreen();
	setcursor(0,0,7);	

	printstr("BASIC "BASVER"\n");
	wait60thsec(15);
	// Initialize music
	init_music();

	printstr("Compiling...");

	// Initialize the other parameters
	// Random seed
	g_rnd_seed=2463534242;
	// Clear variables
	for(i=0;i<ALLOC_BLOCK_NUM;i++){
		g_var_mem[i]=0;
		g_var_size[i]=0;
	}
	// Clear key input buffer
	for(i=0;i<256;i++){
		ps2keystatus[i]=0;
	}
	// Reset data/read.
	reset_dataread();

	// Assign memory
	set_free_area((void*)(g_object+g_objpos),(void*)(&RAM[RAMSIZE]));
	// Execute program
	// Start program from the beginning of RAM.
	// Work area (used for A-Z values) is next to the object code area.
	start_program((void*)(&(RAM[0])),(void*)(&g_var_mem[0]));
	printstr("\nOK\n");
	set_graphmode(0);
	g_use_graphic=0;

	return 1;
}
#else
int debugDump(){
	return 0;
}
#endif

/*
    Override libsdfsio functions.
    Here, don't use SD card, but the vertual files 
    (initext[] and bastext[]) are used. 
*/

FSFILE fsfile;

size_t FSfread(void *ptr, size_t size, size_t n, FSFILE *stream){
	char b;
	size_t ret=0;
	if (!readtext) return 0;
	while(b=readtext[filepos]){
		filepos++;
		((char*)ptr)[ret]=b;
		ret++;
		if (n<=ret) break;
	}
	return ret;
}
FSFILE* FSfopen(const char * fileName, const char *mode){
	int i;
	for(i=0;i<13;i++){
		if (fileName[i]=='.') break;
	}
	if (i==13) {
		// Unknown file name
		// Force BAS file
		readtext=(char*)&bastext[0];
	} else if (fileName[i+1]=='I' && fileName[i+2]=='N' && fileName[i+3]=='I') {
		// INI file
		readtext=(char*)&initext[0];
	} else if (fileName[i+1]=='B' && fileName[i+2]=='A' && fileName[i+3]=='S') {
		// BAS file
		readtext=(char*)&bastext[0];
		// Try debugDump.
		if (debugDump()) return 0;
	} else {
		readtext=0;
		return 0;
	}
	filepos=0;
	return &fsfile;
}
int FSfeof( FSFILE * stream ){
	return readtext[filepos]?1:0;
}
int FSfclose(FSFILE *fo){
	return 0;
}
int FSInit(void){
	return 1;
}
int FSremove (const char * fileName){
	return 0;
}
size_t FSfwrite(const void *ptr, size_t size, size_t n, FSFILE *stream){
	return 0;
}

int FindFirst (const char * fileName, unsigned int attr, SearchRec * rec){
	return 0;
}
int FindNext (SearchRec * rec){
	return 0;
}

/*
    ps2init() is not called.
    Instead, not_ps2init_but_init_Timer1() is called.
    Timer1 is used to update drawcount and drawing gloval variables.
*/

int not_ps2init_but_init_Timer1(){
	PR1=0x0FFF;
	TMR1=0;
	IFS0bits.T1IF=0;
	T1CON=0x8000;
	// Timer1 interrupt: priority 4
	IPC1bits.T1IP=4;
	IPC1bits.T1IS=0;
	IEC0bits.T1IE=1;

	return 0;
}

#pragma interrupt timer1Int IPL4SOFT vector 4

void timer1Int(){
	IFS0bits.T1IF=0;
	if (drawing) {
		drawing=0;
		drawcount++;
	} else {
		drawing=1;
	}
}

/*
    initext[] and bastext[] are vertual files 
    as "MACHIKAN.INI" and "DEBUG.BAS".
*/


static const char initext[]=
"#PRINT\n"
"#PRINT\n";


static const char bastext[]=
"REM SPACE AILEN GAME\n"
"REM  for MachiKania type Z\n"
"REM   Programmed by KENKEN\n"
"\n"
"GOSUB INIT1\n"
"WHILE 1\n"
" GOSUB INITGM\n"
" DO\n"
"  GOSUB NXTSTG\n"
"  DO\n"
"   WAIT 1\n"
"   GOSUB CLCHAR\n"
"   GOSUB BUTTON\n"
"   GOSUB FIRE\n"
"   GOSUB MVCANN\n"
"   GOSUB MVALIN\n"
"   GOSUB MVUFO\n"
"   GOSUB MVMISL\n"
"   GOSUB CKCLSN\n"
"   GOSUB PTMISL\n"
"   GOSUB PTALIN\n"
"   GOSUB PTUFO\n"
"   GOSUB PTCANN\n"
"   GOSUB PTSCOR\n"
"   S=GOSUB(CKGAME)\n"
"  LOOP WHILE S=0\n"
" LOOP WHILE S=1\n"
" GOSUB GAMEOV\n"
"WEND\n"
"END\n"
"\n"
"REM FIRST TIME INIT\n"
"LABEL INIT1\n"
"USEPCG\n"
"USEGRAPHIC\n"
"GOSUB SETPCG\n"
"DIM V(10,4),X(1),Y(1)\n"
"H=0\n"
"RETURN\n"
"\n"
"REM INIT FOR EVERY GAME\n"
"LABEL INITGM\n"
"GPRINT 40,80,7,0,\"SPACE ALIEN\"\n"
"GPRINT 24,110,7,0,\"PUSH START BUTTON\"\n"
"WHILE KEYS(16)=0:WAIT 1:P=RND():WEND\n"
"P=0:R=0:L=3\n"
"GCLS\n"
"RETURN\n"
"\n"
"REM INIT FOR NEXT STAGE\n"
"LABEL NXTSTG\n"
"VAR I,X,S$\n"
"P=P+1\n"
"IF P>=2 THEN\n"
" GPRINT 30,60,6,0,\"CONGRATULATIONS!\"\n"
" WAIT 60\n"
" GPRINT 50,85,6,0,\"NEXT STAGE\" WAIT 120\n"
"ENDIF\n"
"GCLS\n"
"S$=DEC$(P)\n"
"GPRINT 216,0,6,0,\"SPACE\"\n"
"GPRINT 216,8,6,0,\"ALIEN\"\n"
"GPRINT 216,48,7,0,\"HIGH-\"\n"
"GPRINT 216,56,7,0,\"SCORE\"\n"
"GPRINT 216,104,7,0,\"SCORE\"\n"
"GPRINT 216,152,7,0,\"STAGE\"\n"
"GPRINT (32-LEN(S$))*8,168,7,0,S$\n"
"GOSUB PTSCOR\n"
"GPRINT 216,200,5,0,\"\\XA0\\XA1\"\n"
"GPRINT 248,200,7,0,DEC$(L)\n"
"FOR I=0 TO 10:V(I,0)=3:NEXT\n"
"FOR I=0 TO 10:V(I,1)=2:NEXT\n"
"FOR I=0 TO 10:V(I,2)=2:NEXT\n"
"FOR I=0 TO 10:V(I,3)=1:NEXT\n"
"FOR I=0 TO 10:V(I,4)=1:NEXT\n"
"BOXFILL 0,206,215,207,2\n"
"X=21\n"
"FOR I=1 TO 4\n"
"GPRINT X,160,2,0,\"\\XF0\\XF1\\XF2\"\n"
"GPRINT X,168,2,0,\"\\XF3\\XF4\\XF5\"\n"
"X=X+48\n"
"NEXT\n"
"GPRINT 60,100,4,0,\"STAGE \"\n"
"GPRINT ,4,0,S$\n"
"WAIT 180\n"
"BOXFILL 60,100,150,107,0\n"
"E=16:F=((P-1)%8)*8+32:D=2\n"
"W=8:A=-1:Q=0:N=1:M=0:B=0:T=0\n"
"G=0:U=55:Y(0)=0:Y(1)=0:Z=50\n"
"K=KEYS()\n"
"RETURN\n"
"\n"
"REM GAMEOVER\n"
"LABEL GAMEOV\n"
"GPRINT 50,130,4,0,\"GAME OVER\"\n"
"WAIT 240\n"
"RETURN\n"
"\n"
"REM ERASE CHARACTERS\n"
"LABEL CLCHAR\n"
"IF B>0 THEN\n"
" BOXFILL C,B,C+1,B+3,0\n"
"ELSEIF B=-1 THEN\n"
" BOXFILL C-3,0,C+4,7,0\n"
"ENDIF\n"
"IF Y(0)>0 THEN\n"
" BOXFILL X(0),Y(0),X(0)+1,Y(0)+3,0\n"
"ELSEIF Y(0)=-1 THEN\n"
" BOXFILL X(0)-2,198,X(0)+3,205,0:Y(0)=0\n"
"ENDIF\n"
"IF Y(1)>0 THEN\n"
" BOXFILL X(1),Y(1),X(1)+1,Y(1)+3,0\n"
"ELSEIF Y(1)=-1 THEN\n"
" BOXFILL X(1)-2,198,X(1)+3,205,0:Y(1)=0\n"
"ENDIF\n"
"RETURN\n"
"\n"
"REM READ BUTTONS\n"
"LABEL BUTTON\n"
"J=K\n"
"K=KEYS()\n"
"I=(J XOR 63) AND K\n"
"RETURN\n"
"\n"
"REM FIRE MISSILE\n"
"LABEL FIRE\n"
"VAR P,Q\n"
"IF M>0 THEN RETURN\n"
"IF B=0 AND (I AND 32)!=0 THEN\n"
"\n"
" P=RND()\n"
" B=180:C=W+8\n"
" SOUND SOUND1\n"
"ENDIF\n"
"IF Z>0 THEN Z=Z-1\n"
"IF Z=0 AND (Y(0)=0 OR Y(1)=0) THEN\n"
" P=RND()%11\n"
" Q=4\n"
" WHILE Q>=0\n"
"  IF V(P,Q)>0 THEN BREAK\n"
"  Q=Q-1\n"
" WEND\n"
" IF Q<0 OR F+Q*16>=176 THEN RETURN\n"
" IF Y(0)=0 THEN\n"
"  X(0)=E+P*16+7\n"
"  Y(0)=F+Q*16+8\n"
" ELSE\n"
"  X(1)=E+P*16+7\n"
"  Y(1)=F+Q*16+8\n"
" ENDIF\n"
" Z=50\n"
"ENDIF\n"
"RETURN\n"
"\n"
"REM MOVE CANNON\n"
"LABEL MVCANN\n"
"IF M>0 THEN\n"
" M=M-1\n"
" IF M=0 THEN\n"
"  GPRINT 248,200,7,0,DEC$(L)\n"
"  BOXFILL W,184,W+15,191,0\n"
"  W=8\n"
" ENDIF\n"
" RETURN\n"
"ENDIF\n"
"IF W>0 AND (K AND 12)=4 THEN W=W-1\n"
"IF W<192 AND (K AND 12)=8 THEN W=W+1\n"
"RETURN\n"
"\n"
"REM MOVE ALIEN\n"
"LABEL MVALIN\n"
"VAR A,I,S\n"
"IF M>0 THEN RETURN\n"
"G=G+1\n"
"IF (U>=20 AND G<20) OR (U>=12 AND G<10) OR (U>=6 AND G<6) OR (U>=3 AND G<2) OR G<1 THEN RETURN\n"
"G=0\n"
"E=E+D:S=0:T=1-T\n"
"IF D>0 AND E>32 THEN\n"
" A=12-E/16\n"
" FOR I=0 TO 4:S=S+V(A,I):NEXT\n"
" IF S>0 THEN E=E-D:F=F+8:D=-D\n"
"ELSEIF E<0 THEN\n"
" A=-E/16\n"
" FOR I=0 TO 4:S=S+V(A,I):NEXT\n"
" IF S>0 THEN E=E-D:F=F+8:D=-D\n"
"ENDIF\n"
"IF S>0 THEN\n"
" GOSUB CLRAL,E,F-8\n"
"ENDIF\n"
"RETURN\n"
"\n"
"REM MOVE UFO\n"
"LABEL MVUFO\n"
"Q=Q+1\n"
"IF A>=0 THEN\n"
" IF Q>0 AND (Q AND 1)=0 THEN A=A+N\n"
" IF Q=6 THEN Q=0:IF M=0 THEN SOUND SOUND3\n"
" IF A<0 OR A>184 OR Q=-1 THEN\n"
"  BOXFILL A,8,A+23,15,0\n"
"  A=-1\n"
"  N=-N\n"
"  Q=0\n"
" ENDIF\n"
"ELSE\n"
" IF Q>=1500 AND U>7 THEN\n"
"  Q=0\n"
"  IF N>0 THEN A=0 ELSE A=184\n"
"  SOUND SOUND3\n"
" ENDIF\n"
"ENDIF\n"
"RETURN\n"
"\n"
"REM MOVE MISSILE\n"
"LABEL MVMISL\n"
"IF B>0 THEN\n"
" B=B-4\n"
" IF B<=0 THEN B=-3\n"
"ELSEIF B<0 THEN\n"
" B=B+1\n"
"ENDIF\n"
"IF Y(0) THEN\n"
" Y(0)=Y(0)+1\n"
" IF Y(0)>=200 THEN Y(0)=-3\n"
"ENDIF\n"
"IF Y(1) THEN\n"
" Y(1)=Y(1)+1\n"
" IF Y(1)>=200 THEN Y(1)=-3\n"
"ENDIF\n"
"RETURN\n"
"\n"
"REM COLISION CHECK\n"
"LABEL CKCLSN\n"
"VAR S,I,J\n"
"\n"
"REM CHECK MISSILE AND ALIENS\n"
"IF B>0 THEN GOSUB CKHIT\n"
"\n"
"REM CHECK MISSILE AND UFO\n"
"IF B>=8 AND B<16 AND A>=0 AND Q>=0 THEN\n"
" IF C>=A+4 AND C<A+19 THEN\n"
"  B=0\n"
"  SOUND SOUND2\n"
"  Q=-25\n"
"  O=((RND() AND 3)+2)*50\n"
"  IF O=250 THEN O=300\n"
"  GOSUB ADDSCR,O\n"
" ENDIF\n"
"ENDIF\n"
"\n"
"REM CHECK MISSILE AND MISSILE\n"
"IF B>0 THEN\n"
" IF C=X(0) AND B>=Y(0) AND B<Y(0)+4 THEN B=0:Y(0)=0:SOUND SOUND2\n"
" IF C=X(1) AND B>=Y(1) AND B<Y(1)+4 THEN B=0:Y(1)=0:SOUND SOUND2\n"
"ENDIF\n"
"\n"
"REM CHECK CANNON AND MISSILE\n"
"IF M=0 THEN\n"
" IF Y(0)>181 AND Y(0)<192 AND X(0)>=W+2 AND X(0)<=W+14 THEN\n"
"  M=120\n"
"  SOUND SOUND5\n"
" ELSEIF Y(1)>181 AND Y(1)<192 AND X(1)>=W+2 AND X(1)<=W+14 THEN\n"
"  M=120\n"
"  SOUND SOUND5\n"
" ENDIF\n"
"ENDIF\n"
"\n"
"REM CHECK MISSILE AND SHIELD\n"
"IF B>=160 THEN\n"
" S=GCOLOR(C,B)+GCOLOR(C,B+1)+GCOLOR(C,B+2)+GCOLOR(C,B+3)\n"
" IF S THEN BOXFILL C-1,B,C+1,B+3,0:B=0\n"
"ENDIF\n"
"IF Y(0)>=160 THEN\n"
" I=X(0):J=Y(0)\n"
" S=GCOLOR(I,J)+GCOLOR(I,J+1)+GCOLOR(I,J+2)+GCOLOR(I,J+3)\n"
" IF S THEN Y(0)=0:BOXFILL I-1,J-1,I+2,J+5,0\n"
"ENDIF\n"
"IF Y(1)>=160 THEN\n"
" I=X(1):J=Y(1)\n"
" S=GCOLOR(I,J)+GCOLOR(I,J+1)+GCOLOR(I,J+2)+GCOLOR(I,J+3)\n"
" IF S THEN Y(1)=0:BOXFILL I-1,J-1,I+2,J+5,0\n"
"ENDIF\n"
"\n"
"RETURN\n"
"\n"
"REM CHECK MISSILE HIT ALIEN\n"
"LABEL CKHIT\n"
"VAR X,Y\n"
"IF C<E THEN RETURN\n"
"IF C>=E+176 THEN RETURN\n"
"IF B<F THEN RETURN\n"
"IF B>=F+72 THEN RETURN\n"
"X=(C-E)/16:Y=(B-F)/16\n"
"IF (E+X*16+ 2)>C THEN RETURN\n"
"IF (E+X*16+13)<C THEN RETURN\n"
"IF (F+Y*16   )>B THEN RETURN\n"
"IF (F+Y*16+15)<B THEN RETURN\n"
"IF V(X,Y)<=0 THEN RETURN\n"
"IF M=0 THEN SOUND SOUND2\n"
"GOSUB ADDSCR,V(X,Y)*10\n"
"V(X,Y)=-4:U=U-1:G=-3:B=0\n"
"RETURN\n"
"\n"
"REM DRAW ALIENS\n"
"LABEL PTALIN\n"
"VAR X,Y,I,J,W,N\n"
"X=E:Y=F\n"
"FOR J=0 TO 4\n"
"W=X\n"
"FOR I=0 TO 10\n"
"N=V(I,J)\n"
"IF N THEN GOSUB PALIEN,W,Y,N\n"
"IF N<0 THEN V(I,J)=N+1\n"
"W=W+16\n"
"NEXT\n"
"Y=Y+16\n"
"NEXT\n"
"RETURN\n"
"\n"
"REM DRAW UFO\n"
"LABEL PTUFO\n"
"IF A<0 THEN RETURN\n"
"IF Q>=0 THEN\n"
" GPRINT A,8,3,0,\"\\XB0\\XB1\\XB2\"\n"
"ELSEIF Q=-24 THEN\n"
" GPRINT A,8,3,0,\"\\XB3\\XB4\\XB5\"\n"
" SOUND SOUND2\n"
"ELSEIF Q=-18 THEN\n"
" GPRINT A,8,3,0,DEC$(O)\n"
" SOUND SOUND4\n"
"ENDIF\n"
"RETURN\n"
"\n"
"REM DRAW CANNON\n"
"LABEL PTCANN\n"
"IF M=0 THEN\n"
" GPRINT W,184,5,0,\"\\XA0\\XA1\"\n"
"ELSE\n"
" IF (M AND 2) THEN\n"
"  GPRINT W,184,2,0,\"\\XA2\\XA3\"\n"
" ELSE\n"
"  GPRINT W,184,2,0,\"\\XA4\\XA5\"\n"
" ENDIF\n"
"ENDIF\n"
"RETURN\n"
"\n"
"REM DRAW MISSILE\n"
"LABEL PTMISL\n"
"IF B>0 THEN\n"
" PUTBMP C,B,1,4,BMPMSL\n"
"ELSEIF B<=-2 THEN\n"
" GPRINT C-3,0,2,0,\"\\X90\"\n"
"ENDIF\n"
"IF Y(0)>0 THEN PUTBMP X(0),Y(0),2,4,BMPMS2\n"
"IF Y(1)>0 THEN PUTBMP X(1),Y(1),2,4,BMPMS2\n"
"IF Y(0)<0 THEN GPRINT X(0)-2,198,2,0,\"\\X91\"\n"
"IF Y(1)<0 THEN GPRINT X(1)-2,198,2,0,\"\\X91\"\n"
"RETURN\n"
"\n"
"REM DRAW SCORE\n"
"LABEL PTSCOR\n"
"VAR S$\n"
"S$=DEC$(R)\n"
"GPRINT (32-LEN(S$))*8,120,7,0,S$\n"
"S$=DEC$(H)\n"
"GPRINT (32-LEN(S$))*8,72,7,0,S$\n"
"RETURN\n"
"\n"
"REM CHECK GAME STATUS\n"
"LABEL CKGAME\n"
"VAR A,I,S\n"
"IF M=120 THEN\n"
" IF L=0 THEN RETURN 2\n"
" L=L-1\n"
"ENDIF\n"
"IF U=0 THEN RETURN 1\n"
"IF F>=120 THEN\n"
" S=0:A=11-(F-8)/16\n"
" FOR I=0 TO 10:S=S+V(I,A):NEXT\n"
" IF S>0 THEN RETURN 2\n"
"ENDIF\n"
"RETURN 0\n"
"\n"
"REM ERASE ALIEN\n"
"LABEL CLRAL\n"
"VAR X,Y,I,J,W\n"
"X=ARGS(1):Y=ARGS(2)\n"
"FOR J=0 TO 4\n"
"W=X\n"
"FOR I=0 TO 10\n"
"IF V(I,J) THEN BOXFILL W,Y,W+15,Y+7,0\n"
"W=W+16\n"
"NEXT\n"
"Y=Y+16\n"
"NEXT\n"
"RETURN\n"
"\n"
"REM DRAW AN ALIEN\n"
"LABEL PALIEN\n"
"VAR X,Y,C,N,P\n"
"X=ARGS(1):Y=ARGS(2):N=ARGS(3)\n"
"IF N=-1 THEN BOXFILL X,Y,X+15,Y+7,0:RETURN\n"
"IF G>0 THEN RETURN\n"
"IF N<0 THEN\n"
" P=$8C\n"
"ELSE\n"
" P=$80+(N-1)*4+T*2\n"
"ENDIF\n"
"IF Y<8 THEN\n"
" C=2\n"
"ELSEIF Y<32 THEN\n"
" C=3\n"
"ELSEIF Y<64 THEN\n"
" C=4\n"
"ELSEIF Y<96 THEN\n"
" C=5\n"
"ELSEIF Y<128 THEN\n"
" C=3\n"
"ELSEIF Y<160 THEN\n"
" C=6\n"
"ELSE\n"
" C=2\n"
"ENDIF\n"
"GPRINT X,Y,C,0,CHR$(P)+CHR$(P+1)\n"
"RETURN\n"
"\n"
"REM ADD SCORES\n"
"LABEL ADDSCR\n"
"R=R+ARGS(1)\n"
"IF R>=99999 THEN R=99999\n"
"IF R>H THEN H=R\n"
"RETURN\n"
"\n"
"REM SET CHARACTERS FONTS\n"
"LABEL SETPCG\n"
"VAR N\n"
"RESTORE PCGDAT\n"
"WHILE 1\n"
" N=READ()\n"
" IF N=$100 THEN BREAK\n"
" PCG N,READ(),READ()\n"
"WEND\n"
"RETURN\n"
"\n"
"LABEL PCGDAT\n"
"REM ALIEN1\n"
"DATA $80,$031F3F39,$3F060D30\n"
"DATA $81,$C0F8FC9C,$FC60B00C\n"
"DATA $82,$031F3F39,$3F0E190C\n"
"DATA $83,$C0F8FC9C,$FC709830\n"
"\n"
"REM ALIEN2\n"
"DATA $84,$0812171D,$1F0F0408\n"
"DATA $85,$1024F4DC,$FCF81008\n"
"DATA $86,$0402070D,$1F171403\n"
"DATA $87,$1020F0D8,$FCF41460\n"
"\n"
"REM ALIEN3\n"
"DATA $88,$0103070D,$0F02050A\n"
"DATA $89,$80C0E0B0,$F040A050\n"
"DATA $8A,$0103070D,$0F050804\n"
"DATA $8B,$80C0E0B0,$F0A01020\n"
"\n"
"REM ALIEN EXPLODE\n"
"DATA $8C,$04221008,$60081224\n"
"DATA $8D,$40881020,$0C209048\n"
"\n"
"REM SHOT EXPLODE\n"
"DATA $90,$89227EFF,$FF7E2491\n"
"\n"
"REM ALIEN SHOT EXPLODE\n"
"DATA $91,$20883478,$BC7CBC54\n"
"\n"
"REM CANNON\n"
"DATA $A0,$0001011F,$3F3F3F3F\n"
"DATA $A1,$80C0C0FC,$FEFEFEFE\n"
"\n"
"REM CANNON EXPLODE\n"
"DATA $A2,$02000212,$01451F3F\n"
"DATA $A3,$0010A000,$B0A8E4F5\n"
"DATA $A4,$10821002,$4B211F37\n"
"DATA $A5,$0419C002,$31C4F0F2\n"
"\n"
"REM UFO\n"
"DATA $B0,$00000103,$060F0302\n"
"DATA $B1,$007EFFFF,$DBFF9900\n"
"DATA $B2,$000080C0,$60F0C080\n"
"\n"
"REM UFO EXPLODE\n"
"DATA $B3,$12085103,$07114011\n"
"DATA $B4,$8106E3F9,$54F1A310\n"
"DATA $B5,$48100088,$E4801080\n"
"\n"
"REM SHIELD\n"
"DATA $F0,$0F1F3F7F,$FFFFFFFF\n"
"DATA $F1,$FFFFFFFF,$FFFFFFFF\n"
"DATA $F2,$C0E0F0F8,$FCFCFCFC\n"
"DATA $F3,$FFFFFFFF,$FEFCF8F8\n"
"DATA $F4,$FFFFFFFF,$03010000\n"
"DATA $F5,$FCFCFCFC,$FCFCFCFC\n"
"\n"
"DATA $100\n"
"\n"
"LABEL BMPMSL\n"
"CDATA 6,6,6,6\n"
"\n"
"LABEL BMPMS2\n"
"CDATA 5,0,0,5,5,0,0,5\n"
"\n"
"REM SOUND DATA\n"
"\n"
"REM FIRE\n"
"LABEL SOUND1\n"
"DATA $000A02D0,1\n"
"\n"
"REM AILEN EXPLOSION\n"
"LABEL SOUND2\n"
"DATA $00020600,$00080300,1\n"
"\n"
"REM UFO MOVING\n"
"LABEL SOUND3\n"
"DATA $00030680,$00030635,1\n"
"\n"
"REM UFO SCORE\n"
"LABEL SOUND4\n"
"DATA $00040780,$00020000,3\n"
"\n"
"REM CANNON EXPLOSION\n"
"LABEL SOUND5\n"
"DATA $00032000,$00010000,20\n"
"\n"
"\n";

/*
    Test function for constructing assemblies from C codes.
*/

int _debug_test(int a0, int a1, int a2, int a3, int param4, int param5){
//	if (a0<0xa0008192) return 0xa0000000;
	asm volatile("lw $v1,0($v1)");
	return a2+a3;
}

/*
	Break point used for debugging object code.

g_object[g_objpos++]=0x0000000d;// break 0x0

*/

#endif // __DEBUG
