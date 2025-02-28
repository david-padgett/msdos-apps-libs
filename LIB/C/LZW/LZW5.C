/* File        : LZW5.C
   Module      : LZW
   System      : None
   Description : A method for archiving one or more files.
   Modified    : 10/05/90 DWP Created
*/

#include <alloc.h>
#include <dos.h>
#include <errno.h>
#include <mem.h>
#include <stdio.h>
#include <string.h>

#include "lzw.h"
#include "Standard\standard.h"
#include "disk\disk.h"
#include "kb\kb.h"

/* Function    : _lzw_open_file
   Description : Opens the file specified by rec.file_name using the
                 specified mode.
   Expects     :
   Returns     :
   Modified    :
   Notes       :
*/


/* Function    : lzw_archive_files
   Description : Archives the specified files to the specified disk drive.
                 If the disk does not contain enough room, the interactive
                 user is prompted to insert a blank disk.  This allows large
                 files to be compressed and then archived to floppy disk.
   Expects     : file_list          =
                 dest_drive         =
                 interface_function =
   Returns     : The result of the operation.
   Modified    : 10/05/90 DWP Initial coding.
   Notes       :
*/
int lzw_archive_files(char **file_list, int file_attribute, int include_subdirectories_flag, unsigned int dest_drive, int (*interface_function)(int type, lzw_archive_rec *rec, int error_code)) {
   FILE            *source_fp, *dest_fp = NULL;
   struct date     cd;
   struct time     ct;
   struct ffblk    file_rec;
   size_t          bytes_written, write_buffer_size = (size_t) 65535L, write_buffer_offset;
   lzw_archive_rec rec;
   char            source_file_dir[MAXDIR], dest_file_path[MAXPATH], dest_file_name[MAXFILE];
   char            str[MAXPATH];
   unsigned char   *source_buffer, *dest_buffer, *write_buffer;
   unsigned long   free_space;
   unsigned int    time_checksum;
   int             i, disk_number = 0;
   int             file_completed_flag, write_file_header_flag;
   int             result = EZERO;

   /* If any of the parameters are invalid, exit. */

   if (file_list != NULL) {

      /* Allocate the read and write buffers. */

      source_buffer = malloc(_lzw_buffer_size + sizeof(lzw_source_buffer_header_rec));
      dest_buffer = malloc(_lzw_buffer_size + sizeof(lzw_destination_buffer_header_rec));
      write_buffer = malloc(write_buffer_size);

      if (source_buffer != NULL && dest_buffer != NULL && write_buffer != NULL) {

         /* Construct a unique destination file name.  The name relies upon
            the date and a hexadecimal number calculated from the current
            time. */

         getdate(&cd);
         gettime(&ct);

         sprintf(str, "%02u%02u%02u", ct.ti_hour, ct.ti_min, ct.ti_sec);

         /* Calculate a checksum for the time. */

         for (i = 0, time_checksum = 0; i < strlen(str); i++) {
            time_checksum += (str[i] - '0') * (i + 1);
         }

         sprintf(dest_file_name, "%02u%02u%02u%02x", cd.da_year % 100, cd.da_mon, cd.da_day, time_checksum);

         /* Loop until there are no more files to process. */

         free_space = 0L;

         for (i = 0; strlen(file_list[i]) > 0 && result == EZERO; i++) {

            if (!findfirst(file_list[i], &(file_rec), file_attribute)) {

               fnsplit(file_list[i], str, source_file_dir, str, str);

               do {
                  rec.record_identifier = 0L;
                  rec.attribute = file_rec.ff_attrib;
                  setmem(rec.file_name, sizeof(rec.file_name), ' ');
                  sprintf(rec.file_name, "%s%s", source_file_dir, file_rec.ff_name);
                  rec.size = file_rec.ff_fsize;
                  rec.creation_date = file_rec.ff_fdate;
                  rec.creation_time = file_rec.ff_ftime;
                  rec.original_size = 0L;
                  rec.compressed_size = 0L;
                  rec.start_disk = disk_number + 1;

                  /* Open the next source file. */

                  do {
                     if ((source_fp = fopen(rec.file_name, "rb")) != NULL) {
                        break;
                     }
                     if ((result = interface_function(LZW_UNABLE_TO_ACCESS_FILE, &rec, errno)) != EZERO) {
                        break;
                     }
                  } while (TRUE);

                  write_buffer_offset = 0;
                  write_file_header_flag = TRUE;

                  /* Loop until the entire file has been read in. */

                  for (file_completed_flag = FALSE; !file_completed_flag && (result == EZERO);) {

                     /* Loop until the next block has successfully been read into
                        memory or the interactive-user aborts the process. */

                     do {
                        if ((((lzw_source_buffer_header_rec *) source_buffer)->buffer_size = fread(source_buffer + sizeof(lzw_source_buffer_header_rec), 1, _lzw_buffer_size, source_fp)) != 0) {
                           rec.original_size += (long) ((lzw_source_buffer_header_rec *) source_buffer)->buffer_size;
                           break;
                        }

                        /* Determine if the current file has been completely read
                           into memory. */

                        if (rec.original_size == rec.size) {
                           file_completed_flag = TRUE;
                           break;
                        }

                        if ((result = interface_function(LZW_UNABLE_TO_ACCESS_FILE, &rec, errno)) != EZERO) {
                           break;
                        }
                     } while (TRUE);

                     if (result != EZERO) {
                        break;
                     }

                     /* Compress the data.  If an error occurs during compression,
                        then exit. */

                     setmem(dest_buffer, _lzw_buffer_size + sizeof(lzw_destination_buffer_header_rec), 0);
                     if ((result = lzw_compress(source_buffer, dest_buffer)) != EZERO) {
                        break;
                     }

                     /* If the output buffer is not large enough to hold the
                        compressed data, or if the entire file has been read in,
                        write the buffer to disk. */

                     if (((long) write_buffer_offset + (long) ((lzw_destination_buffer_header_rec *) dest_buffer)->buffer_size > (long) write_buffer_size) || file_completed_flag) {

                        /* Loop until there is enough space available on the
                           current disk. */

                        do {

                           /* Determine the amount of disk space left on the
                              destination disk, exit if an error occurs. */

                           if (!disk_get_free_space((char) dest_drive, &free_space)) {
                              result = interface_function(LZW_UNABLE_TO_ACCESS_DISK, &rec, EINVDRV);
                           }

                           if (free_space > 2048L) {
                              if (dest_fp == NULL) {
                                 sprintf(dest_file_path, "%c:\\%s.%03u", 'A' + dest_drive, dest_file_name, disk_number);
                                 if ((dest_fp = fopen(dest_file_path, "wb")) == NULL) {
                                    result = interface_function(LZW_UNABLE_TO_ACCESS_DISK, &rec, errno);
                                 }
                                 else {
                                    write_file_header_flag = TRUE;
                                    disk_number++;
                                    rec.end_disk = disk_number;
                                 }
                              }
                              else {

                                 if (write_file_header_flag) {
                                    if ((bytes_written = fwrite(&rec, 1, sizeof(rec), dest_fp)) == 0) {
                                       result = interface_function(LZW_UNABLE_TO_ACCESS_DISK, &rec, errno);
                                    }
                                    else {
                                       rec.compressed_size += (unsigned long) bytes_written;
                                       write_file_header_flag = FALSE;
                                    }
                                 }

                                 if (!write_file_header_flag) {

                                    /* Write output buffer to disk. */

                                    if ((bytes_written = fwrite(write_buffer, 1, (free_space > (unsigned long) write_buffer_offset + 2048L) ? write_buffer_offset : (size_t) free_space - 1024, dest_fp)) == 0) {
                                       result = interface_function(LZW_UNABLE_TO_ACCESS_DISK, &rec, errno);
                                    }
                                    else {

                                       fflush(dest_fp);
                                       rec.compressed_size += (unsigned long) bytes_written;

                                       /* Re-initialize the write buffer offset. */

                                       if (bytes_written == write_buffer_offset) {
                                          write_buffer_offset = 0;
                                       }
                                       else {

                                          /* If the entire write buffer wasn't written
                                             to disk, move the unwritten portion of
                                             the write buffer to the beginning of the
                                             buffer.  Reset the write buffer offset
                                             to point to the first available byte. */

                                          write_buffer_offset -= bytes_written;
                                          memmove(write_buffer, write_buffer + bytes_written, write_buffer_offset);
                                       }

                                       result = interface_function(LZW_DISPLAY_STATISTICS, &rec, EZERO);
                                       break;
                                    }
                                 }
                              }
                           }
                           else {

                              /* If the destination file is open, close it. */

                              if ((dest_fp != NULL) && fclose(dest_fp)) {
                                 result = interface_function(LZW_UNABLE_TO_ACCESS_DISK, &rec, errno);
                              }
                              else {

                                 /* If no errors occured while closing the last
                                    destination file, inform user that a new disk
                                    is needed. */

                                 dest_fp = NULL;
                                 result = interface_function(LZW_INSERT_NEXT_DISK, &rec, disk_number + 1);
                              }
                           }
                        } while (result == EZERO);
                     }

                     /* Copy the compressed data to the output buffer. */

                     memcpy(write_buffer + write_buffer_offset, dest_buffer, ((lzw_destination_buffer_header_rec *) dest_buffer)->buffer_size);
                     write_buffer_offset += ((lzw_destination_buffer_header_rec *) dest_buffer)->buffer_size;
                  }
               } while (!findnext(&(file_rec)));
            }
         }

         /* If the destination file is still open, close it. */

         if ((dest_fp != NULL) && fclose(dest_fp)) {
            result = interface_function(LZW_UNABLE_TO_ACCESS_DISK, &rec, errno);
         }
      }
      else {
         result = errno;
      }

      /* Return buffer memory to the heap. */

      if (write_buffer != NULL) {
         free(write_buffer);
      }

      if (dest_buffer != NULL) {
         free(dest_buffer);
      }

      if (source_buffer != NULL) {
         free(dest_buffer);
      }
   }
   else {
      result = EINVDAT;
   }

   return (result);
}

/* Function    :
   Description :
   Expects     :
   Returns     :
   Modified    :
   Notes       :
*/
int lzw_restore_files(char *source_file_path, int (*interface_function)(int type, lzw_archive_rec *rec, int error_code)) {
   FILE            *source_fp, *dest_fp;
   size_t          read_buffer_size = (size_t) 65535L, write_buffer_size = (size_t) 65535L, write_buffer_offset;
   lzw_archive_rec *rec;
   char            *read_buffer, *write_buffer, *dest_buffer;
   char            source_file_drive[MAXDRIVE], source_file_dir[MAXDIR], source_file_name[MAXFILE], source_file_ext[MAXEXT], dest_file_path[MAXPATH];
   char            str[MAXPATH];
   long            source_file_position, source_file_size, bytes_read;
   int             result;

   read_buffer = malloc(read_buffer_size);
   write_buffer = malloc(write_buffer_size);
   dest_buffer = malloc(_lzw_buffer_size + sizeof(lzw_destination_buffer_header_rec));

   if (read_buffer != NULL && write_buffer != NULL && dest_buffer != NULL) {

      fnsplit(source_file_path, source_file_drive, source_file_dir, source_file_name, source_file_ext);

      read_buffer_offset = 0;
      write_buffer_offset = 0;

      /* Loop until there are no more archive files to process. */

      do {

         /* Loop until the next archive file has successfully been opened or
            the interactive user aborts the process. */

         do {
            if (((source_fp = fopen(source_file_path, "rb")) != NULL) && (source_file_size = filelength(fileno(source_fp)) != -1)) {
               break;
            }
            if (fclose(source_fp) == EOF) {
               result = LZW_ABORT;
               break;
            }
            if ((result = interface_function(LZW_UNABLE_TO_ACCESS_FILE, &rec, errno)) != EZERO) {
               break;
            }
         } while (TRUE);

         /* Loop until the contents of the entire archive file have been
            read, decompressed, and then written to disk. */

         for (file_completed_flag = FALSE; !file_completed_flag && (result == EZERO);) {

            /* Loop until the next block of data has successfully been read
               into memory or the interactive user aborts the process. */

            do {

               /* Attempt to read in the next block of data.  If no errors
                  occur, exit the loop and continue processing. */

               if ((bytes_read = fread(read_buffer + read_buffer_offset, 1, read_buffer_size - read_buffer_offset, source_fp)) != 0) {
                  source_file_position += bytes_read;
                  break;
               }

               /* Reposition the file pointer to where it was just before
                  the above read, if an error occurs, abort the process,
                  otherwise, inform interactive user of the problem.  Exit
                  if the interactive user does not wish to continue. */

               if (fseek(source_fp, source_file_position, SEEK_SET)) {
                  result = LZW_ABORT;
               }
               if ((result = interface_function(LZW_UNABLE_TO_READ_FILE, &rec, errno)) != LZW_RETRY) {
                  break;
               }
            } while (TRUE);

            for (; result == EZERO;) {

               rec = (lzw_archive_rec *) (read_buffer + read_buffer_offset);
               read_buffer_offset += sizeof(lzw_archive_rec);

               while (read_buffer_offset != read_buffer_size - 1) {

                  if ((result = lzw_expand(read_buffer + read_buffer_offset, dest_buffer)) != EZERO) {
                     break;
                  }

                  if (


               }
            }
         }

      } while (result == EZERO);
   }

   if (write_buffer) {
      free(write_buffer);
   }
   if (read_buffer) {
      free(read_buffer);
   }
   if (dest_buffer) {
      free(dest_buffer);
   }

   return (result);
}

void display_current_file(lzw_archive_rec *rec) {
   int j;

   printf("%-15s %10lu %10lu %10lu ", rec->file_name, rec->size, rec->original_size, rec->compressed_size);
   for (j = 0; j < 8; j++) {
      printf("%c", (rec->attribute & (1 < j)) ? '*' : '-');
   }
   printf("\n");
}

int display(int type, lzw_archive_rec *rec, int code) {

   switch (type) {
      case LZW_UNABLE_TO_ACCESS_DISK : printf("Unable to access disk.");
                                       break;
      case LZW_UNABLE_TO_ACCESS_FILE : printf("Unable to access file.");
                                       break;
      case LZW_INSERT_NEXT_DISK      : printf("Insert next disk.");
                                       break;
      case LZW_DISPLAY_STATISTICS    : display_current_file(rec);
                                       break;
   }
   if (type != LZW_DISPLAY_STATISTICS) {
      printf("\nPress ENTER to continue.\n");
      while (kb_read() != KB_ENTER);
   }

   return (0);
}

void main(void) {
   char *list[] = {"\\tc*.*", ""};

   lzw_archive_files(list, 0, TRUE, 1, display);
}
