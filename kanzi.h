/* 
 * File:   kanzi.h
 * Author: gombe
 *
 * Created on 2016/12/28, 17:20
 */

#ifndef KANZI_H
#define	KANZI_H

#ifdef	__cplusplus
extern "C" {
#endif

    
BYTE drawKANJI(WORD code);
void initforKANJI(int usehankatakana);
void jresetPCG(int usehankakukatakana);
char *printincludekanzistr_onaline(char *str);

#ifdef	__cplusplus
}
#endif

#endif	/* KANZI_H */

