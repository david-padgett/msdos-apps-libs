/* File        : CRT.H
   Description : The header file for CRT.ASM.
   Modified    : 05/23/90 DWP Created.
*/

#ifndef CRT
#define CRT

/* definitions for crt_scroll */

#define SCROLL_UP    0
#define SCROLL_DOWN  1
#define SCROLL_LEFT  2
#define SCROLL_RIGHT 3

/* definitions for the windowing procedures */

#define WN_NOPOPUP   0
#define WN_POPUP     1

#define WN_NOSHADOW  0
#define WN_SHADOW    1

extern void far pascal crt_print_char(int ch);
extern void far pascal crt_print_str(char *str);
extern void far pascal crt_scroll(int direction);
extern void far pascal crt_clrscr(void);
extern int  far pascal crt_wherex(void);
extern int  far pascal crt_wherey(void);
extern void far pascal crt_gotoxy(int x, int y);
extern void far pascal crt_init(void);

extern void far pascal crt_modify_attr(int row, int col, int x_len, int y_len, int attr);

#endif

#ifndef __COLORS
#define __COLORS

/* text colors (CGA, EGA, VGA) */

enum COLORS {BLACK,
             BLUE,
             GREEN,
             CYAN,
             RED,
             MAGENTA,
             BROWN,
             LIGHTGRAY,
             DARKGRAY,
             LIGHTBLUE,
             LIGHTGREEN,
             LIGHTCYAN,
             LIGHTRED,
             LIGHTMAGENTA,
             YELLOW,
             WHITE};
#endif
