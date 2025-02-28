/* File        : LOCALE.C
   Module      : TEST
   System      : None
   Description : Tests the use of "locale.h".
   Modified    : 03/19/91 DWP Created.
*/

#include <locale.h>
#include <stdio.h>
#include <string.h>

/* Procedure   : main
   Description : Tests the use of "locale.h".
   Expects     : Nothing.
   Returns     : Nothing.
   Modified    : 03/19/91 DWP Initial coding.
   Notes       :
*/
void main(void) {
   struct lconv ll;
   struct lconv *conv = &ll;

   conv = localeconv();

   printf("Decimal Point                  : %s\n", conv->decimal_point);
   printf("Thousands Separator            : %s\n", conv->thousands_sep);
   printf("Grouping                       : %s\n", conv->grouping);
   printf("International Currency symbol  : %s\n", conv->int_curr_symbol);
   printf("$ thousands separator          : %s\n", conv->mon_thousands_sep);
   printf("$ grouping                     : %s\n", conv->mon_grouping);
   printf("Positive sign                  : %s\n", conv->positive_sign);
   printf("Negative sign                  : %s\n", conv->negative_sign);
   printf("International fraction digits  : %d\n", conv->int_frac_digits);
   printf("Fraction digits                : %d\n", conv->frac_digits);
   printf("Positive $ symbol precedes     : %d\n", conv->p_cs_precedes);
   printf("Positive sign space separation : %d\n", conv->p_sep_by_space);
   printf("Negative $ symbol precedes     : %d\n", conv->n_cs_precedes);
   printf("Negative sign space separation : %d\n", conv->n_sep_by_space);
   printf("Positive sign position         : %d\n", conv->p_sign_posn);
   printf("Negative sign position         : %d\n", conv->n_sign_posn);

   strcpy(conv->thousands_sep, ",");

   printf("%lu", 123456789L);

}