/*
 * File:   document.c
 * Author: gombe
 *
 * Created on 2016/12/27, 19:30
 */


#include <xc.h>
#include "api.h"
#include "SDFSIO.h"
#include "compiler.h"
#include "editor.h"
#include <stdlib.h>
#include <ctype.h>
#include "kanzi.h"
#include "colortext32.h"
#define SCR_WIDTH 256
#define SCR_HEIGHT 224
#define SIZEOF_DOC_BUFF 20000
#define MAX_TAG_SIZE 100
unsigned char *buff_doc;

const unsigned char **tags;
unsigned int notag;

void initforDocument(void){
    freeall();
//    init_graphic(malloc_nonfree(256*224/2));
    tags = malloc_nonfree(MAX_TAG_SIZE);
//    set_graphmode(1);
    buff_doc = malloc_nonfree(SIZEOF_DOC_BUFF);
}

int document(const char *path) {
    FSFILE *fp;
    fp = FSfopen(path,"r");
    unsigned char *ptr,tok=0;

    jresetPCG(0);
    notag = 0;
    
    if(fp==NULL){
        printincludekanzistr("ファイルが開けません\n");
        return EXIT_FAILURE;
    }
    ptr = buff_doc;
    FSfread(ptr,SIZEOF_DOC_BUFF,1,fp);
    
    ptr = buff_doc;
    
    while(*ptr){
        if(strncmp("# ",ptr,2)==0){
            if(tok){
                ptr[-1]=0;
            }
            tok=1;
            tags[notag] = ptr+2;
            notag++;
            while(*ptr!='\n'){
                *ptr++;
            }
            *ptr++=0;
        }
        ptr++;
    }

    if(notag==0){
        printincludekanzistr("tag not found,filename is");
        printincludekanzistr(path);
        printincludekanzistr(".\n");
        goto quit;
    }
    cls();
    setcursorcolor(6);
    printincludekanzistr("tag-based document viewer");
    setcursorcolor(7);
    int i;
    setcursorcolor(5);
    printstr("\nnumber of tag:");
    printnum(notag);
    printstr("\n");
    setcursorcolor(7);
    while(1){
    for(i=0;i<notag;i++){
        printchar(i+'a');
        printstr(":");
        printincludekanzistr(tags[i]);
        printstr("\n");
    }
    printincludekanzistr("\npress 'q' to quit\ntag:");
    
    char key = 0;
    do{
        key = 0;
        while(!isalpha(key)){
            key = ps2readkey();
        }
        key = tolower(key);

        printchar(key);
        if(key=='q'){
            goto quit;
        }
        if(key-'a'>=notag){
            printincludekanzistr("cannot jump to tag`");
            printchar(key);
            printincludekanzistr("'\n");
            continue;
        }
        printincludekanzistr(" key pressed\njump to");
        printincludekanzistr(tags[key-'a']);
        break;
    }while(1);
    wait60thsec(60);
    cls();

    ptr = tags[key-'a'];
    
    setcursorcolor(6);
    printincludekanzistr("@");
    printincludekanzistr(ptr);
    printincludekanzistr("\n");
    
    setcursorcolor(7);
    while(*ptr++);
    for(i=0;i<27-2;i++){
        ptr = printincludekanzistr_onaline(ptr);
    }
    int breakflag = 0;
    while(*ptr){
        ptr = printincludekanzistr_onaline(ptr);
        if(tolower(inputchar())=='q'){
            breakflag = 1;
            break;
        }
        if((vkey&0xff)==VK_ESCAPE)goto quit;
    }
    if(breakflag == 1){
        cls();
        continue;
    }
    
     setcursorcolor(6);
    printincludekanzistr("\npress `q` to continue");
    setcursorcolor(7);
    while(1){
        if(tolower(inputchar())=='q')break;
        if((vkey&0xff)==VK_ESCAPE)goto quit;
    }
    cls();
    }
quit:
    cls();
    FSfclose(fp);
}
