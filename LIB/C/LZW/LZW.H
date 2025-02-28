/* File        : LZW.H
   Module      : LZW
   System      : None
   Description : The header file for the LZW module.
   Modified    : 09/28/90 DWP Created.
*/

#ifndef LZW_MODULE
#define LZW_MODULE

#include <dir.h>
#include <stdio.h>

#define MAX_CODE_LENGTH  12
#define TABLE_SIZE       5021
#define CODE_ARRAY_SIZE  TABLE_SIZE * (sizeof(lzw_code_data))
#define STRING_OFFSET    2
#define CHARACTER_OFFSET 4
#define STRING_SIZE      4096

#define LZW_COMPRESS_MEMORY_ALLOCATION_ERROR 100
#define LZW_EXPAND_MEMORY_ALLOCATION_ERROR   101
#define LZW_EXPAND_STACK_OVERFLOW_ERROR      102

#define LZW_ABORT                            103
#define LZW_RETRY                            104
#define LZW_CONTINUE                         105

#define LZW_UNABLE_TO_ACCESS_DISK 0
#define LZW_UNABLE_TO_ACCESS_FILE 1
#define LZW_UNABLE_TO_READ_FILE   2
#define LZW_UNABLE_TO_WRITE_FILE  3
#define LZW_INSERT_NEXT_DISK      4
#define LZW_DISPLAY_STATISTICS    5

typedef struct lzw_code_data_type {
   unsigned int code;
   unsigned int string;
   unsigned char ch;
} lzw_code_data;

typedef struct lzw_source_buffer_header_rec_type {
   size_t buffer_size;
} lzw_source_buffer_header_rec;

typedef struct lzw_destination_buffer_header_rec_type {
   size_t        buffer_size;
   unsigned char code;
} lzw_destination_buffer_header_rec;

typedef struct lzw_archive_rec_type {
   long          record_identifier;
   char          attribute;
   char          file_name[MAXPATH];
   unsigned long size;
   unsigned int  creation_date;
   unsigned int  creation_time;
   unsigned long original_size;
   unsigned long compressed_size;
   unsigned int  start_disk;
   unsigned int  end_disk;
} lzw_archive_rec;

/* LZW0.C */

extern size_t _lzw_buffer_size;

/* LZW1.C */

pascal lzw_compress(unsigned char *source, unsigned char *dest);

/* LZW2.C */

pascal lzw_expand(unsigned char *source, unsigned char *dest);

/* LZW3.C */

int lzw_compress_file(char *source_file_name, char *dest_file_name);

/* LZW4.C */

int lzw_uncompress_file(char *source_file_name, char *dest_file_name);

/* LZW5.C */

int lzw_archive_files(char **file_list, int file_attribute, int include_subdirectories_flag, unsigned int dest_drive, int (*interface_function)(int type, lzw_archive_rec *rec, int error_code));

#endif
