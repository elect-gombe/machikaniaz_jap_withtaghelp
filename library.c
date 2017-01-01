/*
   This file is provided under the LGPL license ver 2.1.
   Written by Katsumi.
   http://hp.vector.co.jp/authors/VA016157/
   kmorimatsu@users.sourceforge.jp
*/

#include <xc.h>
#include "main.h"
#include "compiler.h"
#include "api.h"
#include "keyinput.h"
#include "stdlib.h"
#include "math.h"

/*
   Local global variables used for graphic
 */

static int g_gcolor=7;
static int g_prev_x=0;
static int g_prev_y=0;

int lib_read(int mode, unsigned int label){
	unsigned int i,code,code2;
	static unsigned int pos=0;
	static unsigned int in_data=0;
	static unsigned char skip=0;
	if (label) {
		// RESTORE function
		switch(mode){
			case 0:
				// label is label data
				i=(int)search_label(label);
				if (!i) {
					err_data_not_found();
					return 0;
				}
				break;
			case 1:
				// label is pointer
				i=label;
				break;
			case 2:
			default:
				// Reset data/read
				pos=0;
				in_data=0;
				skip=0;
				return 0;
		}
		i-=(int)(&g_object[0]);
		pos=i/4;
		in_data=0;
	}
	// Get data
	if (in_data==0) {
		for(i=pos;i<g_objpos;i++){
			code=g_object[i];
			code2=g_object[i+1];
			if ((code&0xFFFF0000)!=0x04110000) continue;
			// "bgezal zero," assembly found.
			// Check if 0x00000020,0x00000021,0x00000022, or 0x00000023 follows
			if ((code2&0xfffffffc)!=0x00000020) {// add/addu/sub/subu        zero,zero,zero
				// If not, skip following block (it's strig).
				i+=code&0x0000FFFF;
				continue;
			}
			// DATA region found.
			in_data=(code&0x0000FFFF)-1;
			pos=i+2;
			skip=code2&0x03;
			break;
		}
		if (g_objpos<=i) {
			err_data_not_found();
			return 0;
		}
	}
	if (label) {
		// RESTORE function. Return pointer.
		return ((int)&g_object[pos])+skip;
	} else {
		switch(mode){
			case 0:
				// READ() function
				in_data--;
				return g_object[pos++];
			case 1:
			default:
				// CREAD() function
				i=g_object[pos];
				i>>=skip*8;
				i&=0xff;
				if ((++skip)==4) {
					skip=0;
					in_data--;
					pos++;
				}
				return i;
		}
	}
}

void reset_dataread(){
	lib_read(2,1);
}

char* lib_midstr(int var_num, int pos, int len){
	int i;
	char* str;
	char* ret;
	if (0<=pos) {
		// String after "pos" position.
		str=(char*)(g_var_mem[var_num]+pos);
	} else {
		// String right "pos" characters.
		// Determine length
		str=(char*)g_var_mem[var_num];
		for(i=0;str[i];i++);
		if (0<=(i+pos)) {
			str=(char*)(g_var_mem[var_num]+i+pos);
		}
	}
	if (len<0) {
		// Length is not specified.
		// Return the string to the end.
		return str;
	}
	// Length is specified.
	// Construct temporary string containing specified number of characters.
	ret=alloc_memory((len+1+3)/4,-1);
	// Copy string.
	for(i=0;(ret[i]=str[i])&&(i<len);i++);
	ret[len]=0x00;
	return ret;
}

void lib_clear(void){
	int i;
	// All variables will be integer 0
	for(i=0;i<26;i++){
		g_var_mem[i]=0;
	}
	// Clear memory allocation area
	for(i=0;i<ALLOC_BLOCK_NUM;i++){
		g_var_size[i]=0;
	}
	// Cancel PCG
	stopPCG();
	g_pcg_font=0;
}

void lib_let_str(char* str, int var_num){
	int begin,end,size;
	// Save pointer
	g_var_mem[var_num]=(int)str;
	// Determine size
	for(size=0;str[size];size++);
	// Check if str is in heap area.
	begin=(int)str;
	end=(int)(&str[size]);
	if (begin<(int)(&g_heap_mem[0]) || (int)(&g_heap_mem[g_max_mem])<=end) {
		// String is not within allcated block
		return;
	}
	// Str is in heap area. Calculate values stored in heap data dimension
	begin-=(int)(&g_heap_mem[0]);
	begin>>=2;
	end-=(int)(&g_heap_mem[0]);
	end>>=2;
	size=end-begin+1;
	g_var_pointer[var_num]=begin;
	g_var_size[var_num]=size;
}

int lib_rnd(){
	int y;
	y=g_rnd_seed;
	y = y ^ (y << 13);
	y = y ^ (y >> 17);
	y = y ^ (y << 5);
	g_rnd_seed=y;
	return y&0x7fff;
}

char* lib_chr(int num){
	char* str;
	str=alloc_memory(1,-1);
	str[0]=num&0x000000FF;
	str[1]=0x00;
	return str;
}

char* lib_dec(int num){
	char* str;
	int i,j,minus;
	char b[12];
	b[11]=0x00;
	if (num<0) {
		minus=1;
		num=0-num;
	} else {
		minus=0;
	}
	for (i=10;0<i;i--) {
		if (num==0 && i<10) break; 
		b[i]='0'+rem10_32(num);
		num=div10_32(num);
	}
	if (minus) {
		b[i]='-';
	} else {
		i++;
	}
	str=alloc_memory(3,-1);
	for(j=0;str[j]=b[i++];j++);
	return str;
}

char* lib_hex(int num, int width){
	char* str;
	int i,j,minus;
	char b[8];
	str=alloc_memory(3,-1);
	for(i=0;i<8;i++){
		b[i]="0123456789ABCDEF"[(num>>(i<<2))&0x0F];
	}
	// Width must be between 0 and 8;
	if (width<0||8<width) width=8;
	if (width==0) {
		// Width not asigned. Use minimum width.
		for(i=7;0<i;i--){
			if ('0'<b[i]) break;
		}
	} else {
		// Constant width
		i=width-1;
	}
	// Copy string to allocated block.
	for(j=0;0<=i;i--){
		str[j++]=b[i];
	}
	str[j]=0x00;
	return str;
}

char* lib_connect_string(char* str1, char* str2){
	int i,j;
	char b;
	char* result;
	// Determine total length
	for(i=0;str1[i];i++);
	for(j=0;str2[j];j++);
	// Allocate a block for new string
	result=alloc_memory((i+j+1+3)/4,-1);
	// Create connected strings 
	for(i=0;b=str1[i];i++) result[i]=b;
	for(j=0;b=str2[j];j++) result[i+j]=b;
	result[i+j]=0x00;
	free_temp_str(str1);
	free_temp_str(str2);
	return result;
}

void lib_string(int mode){
	int i;
	switch(mode){
		case 0:
			// CR
			printchar('\n');
			return;
		case 1:
			// ,
			i=rem10_32((unsigned int)(cursor-TVRAM));
			printstr("          "+i);
			return;
		default:
			return;
	}
}

void* lib_label(unsigned int label){
	// This routine is used to jump to address dynamically determined
	// in the code; for example: "GOTO 100+I"
	unsigned int i,code,search;
	void* ret;  
	if (label&0xFFFF0000) {
		// Label is not supported.
		// Line number must bs less than 65536.
		err_label_not_found();
	} else {
		// Line number
		ret=search_label(label);
		if (ret) return ret;
		// Line number not found.
		err_label_not_found();
	}
}

int lib_keys(int mask){
	int keys;
	// Enable tact switches
	if (inPS2MODE()) {
		buttonmode();
	}

	keys=KEYPORT;
	keys=
		((keys&KEYUP)?    0:1)|
		((keys&KEYDOWN)?  0:2)|
		((keys&KEYLEFT)?  0:4)|
		((keys&KEYRIGHT)? 0:8)|
		((keys&KEYSTART)? 0:16)|
		((keys&KEYFIRE)?  0:32);
	return mask&keys;
}

int lib_val(char* str){
	int i;
	int val=0;
	int sign=1;
	char b;
	// Skip blanc
	for(i=0;0<=str[i] && str[i]<0x21;i++);
	// Skip '+'
	if (str[i]=='+') i++;
	// Check '-'
	if (str[i]=='-') {
		sign=-1;
		i++;
	}
	// Check '0x' or '$'
	if (str[i]=='$' || str[i]=='0' && (str[i+1]=='x' || str[i+1]=='X')) {
		// Hexadecimal
		if (str[i++]=='0') i++;
		while(1) {
			b=str[i++];
			if ('0'<=b && b<='9') {
				val<<=4;
				val+=b-'0';
			} else if ('a'<=b && b<='f') {
				val<<=4;
				val+=b-'a'+10;
			} else if ('A'<=b && b<='F') {
				val<<=4;
				val+=b-'A'+10;
			} else {
				break;
			}
		}
	} else {
		// Decimal
		while(1) {
			b=str[i++];
			if ('0'<=b && b<='9') {
				val*=10;
				val+=b-'0';
			} else {
				break;
			}
		}
	}
	return val*sign;
}

char* lib_input(){
	// Allocate memory for strings with 63 characters
	char *str=calloc_memory((63+1)/4,-1);
	// Enable PS/2 keyboard
	if (!inPS2MODE()) {
		ps2mode();
		ps2init();
	}
	// Clear key buffer
	do ps2readkey();
	while(vkey!=0);
	// Get string as a line
	lineinput(str,63);
	check_break();
	return str;
}

unsigned char lib_inkey(int key){
	int i;
	// Enable PS/2 keyboard
	if (!inPS2MODE()) {
		ps2mode();
		ps2init();
	}
	if (key) {
		return ps2keystatus[key&0xff];
	} else {
		for(i=0;i<256;i++){
			if (ps2keystatus[i]) return i;
		}
		return 0;
	}
}

void lib_usepcg(int mode){
	// Modes; 0: stop PCG, 1: use PCG, 2: reset PCG and use it
	switch(mode){
		case 0:
			// Stop PCG
			stopPCG();
			break;
		case 2:
			// Reset PCG and use it
			if (g_pcg_font) {
				free_temp_str(g_pcg_font);
				g_pcg_font=0;
			}
			// Continue to case 1:
		case 1:
		default:
			// Use PCG
			if (g_pcg_font) {
				startPCG(g_pcg_font,0);
			} else {
				g_pcg_font=alloc_memory(256*8/4,ALLOC_PCG_BLOCK);
				startPCG(g_pcg_font,1);
			}
			break;
	}
}

void lib_pcg(unsigned int ascii,unsigned int fontdata1,unsigned int fontdata2){
	unsigned int* pcg;
	// If USEPCG has not yet executed, do now.
	if (!g_pcg_font) lib_usepcg(1);
	pcg=(unsigned int*)g_pcg_font;
	// 0 <= ascii <= 0xff
	ascii&=0xff;
	// Update font data
	ascii<<=1;
	pcg[ascii]=(fontdata1>>24)|((fontdata1&0xff0000)>>8)|((fontdata1&0xff00)<<8)|(fontdata1<<24);
	pcg[ascii+1]=(fontdata2>>24)|((fontdata2&0xff0000)>>8)|((fontdata2&0xff00)<<8)|(fontdata2<<24);
}

void lib_scroll30(int x,int y){
	int i,j;
	int vector=y*WIDTH_X1+x;
	if (vector<0) {
		// Copy data from upper address to lower address
		for(i=0-vector;i<WIDTH_X1*WIDTH_Y;i++){
			TVRAM[i+vector]=TVRAM[i];
			TVRAM[WIDTH_X1*WIDTH_Y+i+vector]=TVRAM[WIDTH_X1*WIDTH_Y+i];
		}
	} else if (0<vector) {
		// Copy data from lower address to upper address
		for(i=WIDTH_X1*WIDTH_Y-vector-1;0<=i;i--){
			TVRAM[i+vector]=TVRAM[i];
			TVRAM[WIDTH_X1*WIDTH_Y+i+vector]=TVRAM[WIDTH_X1*WIDTH_Y+i];
		}
	} else {
		return;
	}
	if (x<0) {
		// Fill blanc at right
		for(i=x;i<0;i++){
			for(j=WIDTH_X1+i;j<WIDTH_X1*WIDTH_Y;j+=WIDTH_X1){
				TVRAM[j]=0x00;
				TVRAM[WIDTH_X1*WIDTH_Y+j]=cursorcolor;
			}
		}
	} else if (0<x) {
		// Fill blanc at left
		for(i=0;i<x;i++){
			for(j=i;j<WIDTH_X1*WIDTH_Y;j+=WIDTH_X1){
				TVRAM[j]=0x00;
				TVRAM[WIDTH_X1*WIDTH_Y+j]=cursorcolor;
			}
		}
	}
	if (y<0) {
		// Fill blanc at bottom
		for(i=WIDTH_X1*(WIDTH_Y+y);i<WIDTH_X1*WIDTH_Y;i++){
				TVRAM[i]=0x00;
				TVRAM[WIDTH_X1*WIDTH_Y+i]=cursorcolor;
		}
	} else if (0<y) {
		// Fill blanc at top
		for(i=0;i<WIDTH_X1*y;i++){
				TVRAM[i]=0x00;
				TVRAM[WIDTH_X1*WIDTH_Y+i]=cursorcolor;
		}
	}
}

void lib_scroll40(int x,int y){
	int i,j;
	int vector=y*WIDTH_X2+x;
	if (vector<0) {
		// Copy data from upper address to lower address
		for(i=0-vector;i<WIDTH_X2*WIDTH_Y;i++){
			TVRAM[i+vector]=TVRAM[i];
			TVRAM[WIDTH_X2*WIDTH_Y+i+vector]=TVRAM[WIDTH_X2*WIDTH_Y+i];
		}
	} else if (0<vector) {
		// Copy data from lower address to upper address
		for(i=WIDTH_X2*WIDTH_Y-vector-1;0<=i;i--){
			TVRAM[i+vector]=TVRAM[i];
			TVRAM[WIDTH_X2*WIDTH_Y+i+vector]=TVRAM[WIDTH_X2*WIDTH_Y+i];
		}
	} else {
		return;
	}
	if (x<0) {
		// Fill blanc at right
		for(i=x;i<0;i++){
			for(j=WIDTH_X2+i;j<WIDTH_X2*WIDTH_Y;j+=WIDTH_X2){
				TVRAM[j]=0x00;
				TVRAM[WIDTH_X2*WIDTH_Y+j]=cursorcolor;
			}
		}
	} else if (0<x) {
		// Fill blanc at left
		for(i=0;i<x;i++){
			for(j=i;j<WIDTH_X2*WIDTH_Y;j+=WIDTH_X2){
				TVRAM[j]=0x00;
				TVRAM[WIDTH_X2*WIDTH_Y+j]=cursorcolor;
			}
		}
	}
	if (y<0) {
		// Fill blanc at bottom
		for(i=WIDTH_X2*(WIDTH_Y+y);i<WIDTH_X2*WIDTH_Y;i++){
				TVRAM[i]=0x00;
				TVRAM[WIDTH_X2*WIDTH_Y+i]=cursorcolor;
		}
	} else if (0<y) {
		// Fill blanc at top
		for(i=0;i<WIDTH_X2*y;i++){
				TVRAM[i]=0x00;
				TVRAM[WIDTH_X2*WIDTH_Y+i]=cursorcolor;
		}
	}
}

void lib_wait(int period){
	int i;
	unsigned short dcount;
	for(i=0;i<period;i++){
		dcount=drawcount;
		while(dcount==drawcount){
			asm (WAIT);
			check_break();
		}
	}
}

void allocate_graphic_area(){
	if (!g_graphic_area) {
		// Use this pointer like unsigned short GVRAM[G_H_WORD*G_Y_RES] __attribute__ ((aligned (4)));
		g_graphic_area=(unsigned short*)alloc_memory(G_H_WORD*G_Y_RES/2,ALLOC_GRAPHIC_BLOCK);
		// Start graphic and clear screen
		init_graphic(g_graphic_area);
		// Move current point to (0,0)
		g_prev_x=g_prev_y=0;
	}
}

void lib_usegraphic(int mode){
	// Modes; 0: stop GRAPHIC, 1: use GRAPHIC, 2: reset GRAPHIC and use it
	switch(mode){
		case 0:
			if (g_use_graphic){
				// Stop GRAPHIC if used
				set_graphmode(0);
				g_use_graphic=0;
				// Set timer4 for tempo
				PR4=59473;       // 3632*262/16-1
			} else {
				// Prepare GRAPHIC area if not used and not allcated.
				allocate_graphic_area();
			}
			break;
		case 2:
			// Reset GRAPHIC and use it
			g_graphic_area=0;
			// Continue to case 1:
		case 1:
		case 3:
		default:
			// Use GRAPHIC
			allocate_graphic_area();
			// Start showing GRAPHIC with mode 1, but not with mode 3
			if (mode !=3 && !g_use_graphic){
				set_graphmode(1);
				g_use_graphic=1;
				// Set timer4 for tempo
				PR4=55756;       // ~=3405*262/16-1(55755.875)
			}
			break;
	}
}

int lib_graphic(int v0,enum functions func){
	unsigned char b;
	int x1=g_libparams[1];
	int y1=g_libparams[2];
	int x2=g_libparams[3];
	int y2=g_libparams[4];
	// Disable if graphic area is not defined.
	if (!g_graphic_area) return;
	// If C is omitted in parameters, use current color.
	if (v0==-1) {
		v0=g_gcolor;
	}
	// If X1 or Y1 is 0x80000000, use the previous values.
	if (x1==0x80000000) x1=g_prev_x;
	if (y1==0x80000000) y1=g_prev_y;
	switch(func){
		case FUNC_POINT:// X1,Y1
			g_prev_x=x1;
			g_prev_y=y1;
			break;
		case FUNC_PSET:// X1,Y1[,C]
			g_pset(x1,y1,v0&0x0F);
			g_prev_x=x1;
			g_prev_y=y1;
			break;
		case FUNC_LINE:// X1,Y1,X2,Y2[,C]
			if (y1==y2) g_hline(x1,x2,y1,v0&0x0F);
			else g_gline(x1,y1,x2,y2,v0&0x0F);
			g_prev_x=x2;
			g_prev_y=y2;
			break;
		case FUNC_BOXFILL:// X1,Y1,X2,Y2[,C]
			g_boxfill(x1,y1,x2,y2,v0&0x0F);
			g_prev_x=x2;
			g_prev_y=y2;
			break;
		case FUNC_CIRCLE:// X1,Y1,R[,C]
			g_circle(x1,y1,x2,v0&0x0F);
			g_prev_x=x1;
			g_prev_y=y1;
			break;
		case FUNC_CIRCLEFILL:// X1,Y1,R[,C]
			g_circlefill(x1,y1,x2,v0&0x0F);
			g_prev_x=x1;
			g_prev_y=y1;
			break;
		case FUNC_GPRINT:// X1,Y1,C,BC,S$
			g_printstr(x1,y1,x2,y2,(unsigned char*)v0);
			// Move current X,Y according to the string
			while(b=((unsigned char*)v0)[0]){
				v0++;
				if (b==0x0d) {
					x1=0;
					y1+=8;
				} else {
					x1+=8;
				}
			}
			g_prev_x=x1;
			g_prev_y=y1;
			break;
		case FUNC_PUTBMP2:// X1,Y1,M,N,BMP(label)
			// Search CDATA
			// It starts from either 0x00000020,0x00000021,0x00000022, or 0x00000023.
			while((((unsigned int*)v0)[0]&0xfffffffc)!=0x00000020) v0+=4;
			// CDATA starts from next word.
			// MLB 3 bytes show skip byte(s).
			v0+=4+(((unsigned int*)v0)[0]&0x03);
			// Contunue to FUNC_PUTBMP.
		case FUNC_PUTBMP:// X1,Y1,M,N,BMP(pointer)
			g_putbmpmn(x1,y1,x2,y2,(const unsigned char*)v0);
			g_prev_x=x1;
			g_prev_y=y1;
			break;
		case FUNC_GCOLOR:// (X1,Y1)
			v0=g_color(x1,y1);
			break;
		default:
			break;
	}
	return v0;
}

void lib_var_push(int* sp,unsigned int flags){
	unsigned int strflags=0;
	int varnum;
	int stack=0;
	// Store flags in stack
	// Note that sp[1] is used for string return address
	sp[2]=flags;
	for(varnum=0;varnum<26;varnum++){
		if (flags&1) {
			sp[(stack++)+4]=g_var_mem[varnum];
			if (g_var_size[varnum] && g_var_mem[varnum]==(int)(&g_var_pointer[varnum])) {
				// strflags change using varnum
				strflags|=1<<varnum;
				// Copy to VAR_BLOCK
				move_to_perm_block(varnum);
			}
			// Clear variable
			g_var_mem[varnum]=0;
		}
		flags>>=1;
	}
	sp[3]=strflags;
}
void lib_var_pop(int* sp){
	// Note that sp is 4 bytes larger than that in lib_var_push
	unsigned int flags;
	unsigned int strflags;
	int varnum;
	int stack=0;
	flags=sp[1];
	strflags=sp[2];
	for(varnum=0;varnum<26;varnum++){
		if (flags&1) {
			g_var_mem[varnum]=sp[(stack++)+3];
			if (strflags&1) {
				// Restore from VAR_BLOCK
				move_from_perm_block(varnum);
			}
		}
		flags>>=1;
		strflags>>=1;
	}
}

int lib_system(int a0,int v0){
	switch(a0){
		// Version info
		case 0: return (int)SYSVER1;
		case 1: return (int)SYSVER2;
		case 2: return (int)BASVER;
		case 3: return (int)FILENAME_FLASH_ADDRESS;
		// Display info
		case 20: return twidth;
		case 21: return WIDTH_Y;
		case 22: return G_X_RES;
		case 23: return G_Y_RES;
		case 24: return cursorcolor;
		case 25: return g_gcolor;
		case 26: return ((int)(cursor-TVRAM))%twidth;
		case 27: return ((int)(cursor-TVRAM))/twidth;
		case 28: return g_prev_x;
		case 29: return g_prev_y;
		// Keyboard info
		case 40: return (int)inPS2MODE();
		case 41: return (int)vkey;
		case 42: return (int)lockkey;
		case 43: return (int)keytype;
		// Pointers to gloval variables
		case 100: return (int)&g_var_mem[0];
		case 101: return (int)&g_rnd_seed;
		case 102: return (int)&TVRAM[0];
		case 103: return (int)&FontData[0];
		case 104: return (int)g_var_mem[ALLOC_PCG_BLOCK];
		case 105: return (int)g_var_mem[ALLOC_GRAPHIC_BLOCK];
		// Change system settings
		case 200:
			// ON/OFF monitor
			if (v0) {
				start_composite();
			} else {
				stop_composite();
			}
			break;
		default:
			break;
	}
	return 0;
}

char* lib_sprintf(char* format, int data){
	char* str;
	int i;
	char temp[4];
	if (!format) format="%g";
	i=snprintf((char*)(&temp[0]),4,format,data)+1;
	str=alloc_memory((i+3)/4,-1);
	snprintf(str,i,format,data);
	return str;
}

int lib_floatfuncs(int ia0,int iv0,enum functions a1){
	volatile float a0,v0;
	((int*)(&a0))[0]=ia0;
	((int*)(&v0))[0]=iv0;
	switch(a1){
		case FUNC_FLOAT:
			v0=(float)iv0;
			break;
		case FUNC_INT:
			return (int)v0;
		case FUNC_VALSHARP:
			v0=strtof((const char*)iv0,0);
			break;
		case FUNC_SIN:
			v0=sinf(v0);
			break;
		case FUNC_COS:
			v0=cosf(v0);
			break;
		case FUNC_TAN:
			v0=tanf(v0);
			break;
		case FUNC_ASIN:
			v0=asinf(v0);
			break;
		case FUNC_ACOS:
			v0=acosf(v0);
			break;
		case FUNC_ATAN:
			v0=atanf(v0);
			break;
		case FUNC_ATAN2:
			v0=atan2f(v0,a0);
			break;
		case FUNC_SINH:
			v0=sinhf(v0);
			break;
		case FUNC_COSH:
			v0=coshf(v0);
			break;
		case FUNC_TANH:
			v0=tanhf(v0);
			break;
		case FUNC_EXP:
			v0=expf(v0);
			break;
		case FUNC_LOG:
			v0=logf(v0);
			break;
		case FUNC_LOG10:
			v0=log10f(v0);
			break;
		case FUNC_POW:
			v0=powf(v0,a0);
			break;
		case FUNC_SQRT:
			v0=sqrtf(v0);
			break;
		case FUNC_CEIL:
			v0=ceilf(v0);
			break;
		case FUNC_FLOOR:
			v0=floorf(v0);
			break;
		case FUNC_FABS:
			v0=fabsf(v0);
			break;
		case FUNC_MODF:
			v0=modff(v0,(void*)&a0);
			break;
		case FUNC_FMOD:
			v0=fmodf(v0,a0);
			break;
		default:
			err_unknown();
			break;
	}
	return ((int*)(&v0))[0];
};

int* lib_dim(int varnum, int argsnum, int* sp){
	int i,j;
	static int* heap;
	// Calculate total length.
	int len=0;  // Total length
	int size=1; // Size of current block
	for(i=1;i<=argsnum;i++){
		size*=sp[i]+1;
		len+=size;
	}
	// Allocate memory
	heap=calloc_memory(len,varnum);
	// Construct pointers
	len=0;
	size=1;
	for(i=1;i<argsnum;i++){
		size*=sp[i]+1;
		for(j=0;j<size;j++){
			heap[len+j]=(int)&heap[len+size+(sp[i+1]+1)*j];
		}
		len+=size;
	}
	return heap;
};

void lib_width(int width){
	switch(width){
		case 30:
			if (twidth!=30) set_width(0);
			break;
		case 40:
			if (twidth!=40) set_width(1);
			break;
		default:
			break;
	}
}

int _call_library(int a0,int a1,int a2,enum libs a3);

void call_library(void){
	// Store s6 in g_s6
	asm volatile("la $a2,%0"::"i"(&g_s6));
	asm volatile("sw $s6,0($a2)");
	// Copy $v0 to $a2 as 3rd argument of function
	asm volatile("addu $a2,$v0,$zero");
	// Store sp in g_libparams
	asm volatile("la $v0,%0"::"i"(&g_libparams));
	asm volatile("sw $sp,0($v0)");
	// Jump to main routine
	asm volatile("j _call_library");
}

int _call_library(int a0,int a1,int v0,enum libs a3){
	// usage: call_lib_code(LIB_XXXX);
	// Above code takes 2 words.
	check_break();
	switch(a3 & LIB_MASK){
		case LIB_FLOAT:
			return lib_float(a0,v0,(enum operator)(a3 & OP_MASK)); // see operator.c
		case LIB_FLOATFUNCS:
			return lib_floatfuncs(a0,v0,(enum functions)(a3 & FUNC_MASK));
		case LIB_STRNCMP:
			return strncmp((char*)g_libparams[1],(char*)g_libparams[2],v0);
		case LIB_MIDSTR:
			return (int)lib_midstr(a1,v0,a0);
		case LIB_RND:
			return (int)lib_rnd();
		case LIB_DEC:
			return (int)lib_dec(v0);
		case LIB_HEX:
			return (int)lib_hex(v0,a0);
		case LIB_CHR:
			return (int)lib_chr(v0);
		case LIB_VAL:
			return lib_val((char*)v0);
		case LIB_LETSTR:
			lib_let_str((char*)v0,a0);
			return;
		case LIB_CONNECT_STRING:
			return (int)lib_connect_string((char*)a0, (char*)v0);
		case LIB_STRING:
			lib_string(a0);
			return v0;
		case LIB_PRINTSTR:
			printstr((char*)v0);
			return v0;
		case LIB_GRAPHIC:
			return lib_graphic(v0, (enum functions)(a3 & FUNC_MASK));
		case LIB_SPRINTF:
			return (int)lib_sprintf((char*)v0,a0);
		case LIB_VAR_PUSH:
			lib_var_push(g_libparams,a0);
			return v0;
		case LIB_VAR_POP:
			lib_var_pop(g_libparams);
			return v0;
		case LIB_SCROLL:
			if (twidth==30) lib_scroll30(g_libparams[1],v0);
			else if (twidth==40) lib_scroll40(g_libparams[1],v0);
			return v0;
		case LIB_KEYS:
			return lib_keys(v0);
		case LIB_INKEY:
			return (int)lib_inkey(v0);
		case LIB_CURSOR:
			setcursor(g_libparams[1],v0,cursorcolor);
			return v0;
		case LIB_SOUND:
			set_sound((unsigned long*)v0);
			return v0;
		case LIB_MUSICFUNC:
			return musicRemaining();
		case LIB_MUSIC:
			set_music((char*)v0);
			return v0;
		case LIB_SETDRAWCOUNT:
			drawcount=(v0&0x0000FFFF);
			return v0;
		case LIB_DRAWCOUNT:
			return drawcount;
		case LIB_SYSTEM:
			return lib_system(a0,v0);
		case LIB_RESTORE:
			return lib_read(0,v0);
		case LIB_RESTORE2:
			return lib_read(1,v0);
		case LIB_READ:
			return lib_read(0,0);
		case LIB_CREAD:
			return lib_read(1,0);
		case LIB_LABEL:
			return (int)lib_label(v0);
		case LIB_INPUT:
			return (int)lib_input();
		case LIB_USEGRAPHIC:
			lib_usegraphic(v0);
			return v0;
		case LIB_USEPCG:
			lib_usepcg(v0);
			return v0;
		case LIB_PCG:
			lib_pcg(g_libparams[1],g_libparams[2],v0);
			return v0;
		case LIB_BGCOLOR: // BGCOLOR R,G,B
			set_bgcolor(v0,g_libparams[1],g_libparams[2]); //set_bgcolor(b,r,g);
			return v0;
		case LIB_PALETTE: // PALETTE N,R,G,B
			set_palette(g_libparams[1],v0,g_libparams[2],g_libparams[3]); // set_palette(n,b,r,g);
			return v0;
		case LIB_GPALETTE:// GPALETTE N,R,G,B
			if (g_graphic_area) g_set_palette(g_libparams[1],v0,g_libparams[2],g_libparams[3]); // g_set_palette(n,b,r,g);
			return v0;
		case LIB_CLS:
			clearscreen();
			return v0;
		case LIB_GCLS:
			if (g_graphic_area) g_clearscreen();
			g_prev_x=g_prev_y=0;
			return v0;
		case LIB_WIDTH:
			lib_width(v0);
			return v0;
		case LIB_COLOR:
			setcursorcolor(v0);
			return v0;
		case LIB_GCOLOR:
			g_gcolor=v0;
			return v0;
		case LIB_WAIT:
			lib_wait(v0);
			return v0;
		case LIB_CLEAR:
			lib_clear();
			return v0;
		case LIB_DIM:
			return (int)lib_dim(a0,a1,(int*)v0);
#ifdef __DEBUG
		case LIB_DEBUG:
			asm volatile("nop");
			return v0;
#endif
		case LIB_DIV0:
			err_div_zero();
			return v0;
		default:
			err_unknown();
			return v0;
	}
}