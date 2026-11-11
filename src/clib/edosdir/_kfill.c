#define _ELFCLIB_
#include <stdlib.h>
#include "kdir.h"

/*
 * Read up to dirp->dd_nslots entries of the directory into dd_slot,
 * converting each in place to a struct dirent.  Returns the number of
 * entries read, 0 at the end of the directory, or -1 if the drive can
 * no longer be read.  dd_eof is set when the kernel reaches the end.
 *
 * The kernel has one directory scan, shared by every program and by
 * calls like K_STAT and K_FILE_OPEN, and it reads whichever drive was
 * resolved last.  So the directory's drive is selected by resolving
 * "X:/", then the scan is started, or the position saved by the last
 * fill is restored, which reads the directory sector again.  The
 * entries are read and the position is saved.
 *
 * Each step is a kernel call made in line, on pointers and values the
 * C code puts in local variables, to keep the work per entry small.
 */
int _kfill(DIR *dirp) {
  int result;
  unsigned char *slot;
  char *arg;
  int n;

  /* select the directory's drive */
  arg = dirp->dd_root;
  asm("         gosub s_lget16  ; get the root string variable ");
  asm("           dw -6         ; from local variable stack");
  asm("         copy ra, rf     ; copy path string to buffer pointer");
  _KSAVE
  asm("         call K_PATH_RESOLVE ; select the drive");
  _KRESTORE
  _KRESULT
  asm("         gosub s_lset16  ; set the result variable ");
  asm("           dw -2         ; in the local variable on the stack");
  if (result == EOF)
    return EOF;

  if (dirp->dd_loc == 0) {
    /* start the scan */
    arg = (char *) dirp->dd_clust;
    asm("         gosub s_lget16  ; get the cluster variable ");
    asm("           dw -6         ; from local variable stack");
    asm("         copy ra, rd     ; copy cluster to rd");
    _KSAVE
    asm("         call K_DIR_OPEN ; start the directory scan");
    _KRESTORE
    dirp->dd_loc = 1;
  } else {
    /* restore the position after the last entry read */
    arg = dirp->dd_state;
    asm("         gosub s_lget16  ; get the state buffer variable ");
    asm("           dw -6         ; from local variable stack");
    asm("         copy ra, rf     ; copy state buffer pointer");
    _KSAVE
    asm("         call K_DIR_RESTORE_STATE ; restore the scan position");
    _KRESTORE
    _KRESULT
    asm("         gosub s_lset16  ; set the result variable ");
    asm("           dw -2         ; in the local variable on the stack");
    if (result == EOF)
      return EOF;
  }

  slot = (unsigned char *) dirp->dd_slot;
  for (n = 0; n < dirp->dd_nslots; n++) {
    /*
     * K_DIR_READ takes the buffer in RF.  The SDK guide says RD, but
     * the kernel and the SDK's own file_glob use RF.
     */
    asm("         gosub s_lget16  ; get the slot variable ");
    asm("           dw -4         ; from local variable stack");
    asm("         copy ra, rf     ; copy slot to result pointer");
    _KSAVE
    asm("         call K_DIR_READ ; read the next entry");
    _KRESTORE
    _KRESULT
    asm("         gosub s_lset16  ; set the result variable ");
    asm("           dw -2         ; in the local variable on the stack");
    if (result == EOF) {
      dirp->dd_eof = 1;
      break;
    }

    /*
     * Convert the kernel's big-endian fields after the name to the
     * little-endian struct dirent fields.  They overlap, so they are
     * done from the last to the first, each read before it is written.
     *
     *   kernel  128 attr  129 clust  131 size  135 time  137 date
     *   dirent  128 attr  130 d_ino  132 d_size  136 d_time  138 d_date
     */
    asm("         gosub s_lget16  ; get the slot variable ");
    asm("           dw -4         ; from local variable stack");
    asm("         glo  ra         ; rf = slot + 137, the date");
    asm("         adi  137");
    asm("         plo  rf");
    asm("         ghi  ra");
    asm("         adci 0");
    asm("         phi  rf");
    asm("         lda  rf         ; date msb");
    asm("         phi  rc");
    asm("         ldn  rf         ; date lsb, rf = slot + 138");
    asm("         str  rf         ; d_date lsb");
    asm("         inc  rf");
    asm("         ghi  rc");
    asm("         str  rf         ; d_date msb");
    asm("         glo  ra         ; rf = slot + 135, the time");
    asm("         adi  135");
    asm("         plo  rf");
    asm("         ghi  ra");
    asm("         adci 0");
    asm("         phi  rf");
    asm("         lda  rf         ; time msb");
    asm("         phi  rc");
    asm("         ldn  rf         ; time lsb, rf = slot + 136");
    asm("         plo  rc");
    asm("         glo  rc");
    asm("         str  rf         ; d_time lsb");
    asm("         inc  rf");
    asm("         ghi  rc");
    asm("         str  rf         ; d_time msb, slot + 137");
    asm("         glo  ra         ; rf = slot + 131, the size");
    asm("         adi  131");
    asm("         plo  rf");
    asm("         ghi  ra");
    asm("         adci 0");
    asm("         phi  rf");
    asm("         lda  rf         ; size byte 3, the msb");
    asm("         phi  rc");
    asm("         lda  rf         ; size byte 2");
    asm("         plo  rc");
    asm("         lda  rf         ; size byte 1");
    asm("         phi  rd");
    asm("         ldn  rf         ; size byte 0, rf = slot + 134");
    asm("         plo  rd");
    asm("         dec  rf");
    asm("         dec  rf         ; rf = slot + 132");
    asm("         glo  rd");
    asm("         str  rf         ; d_size.low lsb");
    asm("         inc  rf");
    asm("         ghi  rd");
    asm("         str  rf         ; d_size.low msb");
    asm("         inc  rf");
    asm("         glo  rc");
    asm("         str  rf         ; d_size.high lsb");
    asm("         inc  rf");
    asm("         ghi  rc");
    asm("         str  rf         ; d_size.high msb, slot + 135");
    asm("         glo  ra         ; rf = slot + 129, the cluster");
    asm("         adi  129");
    asm("         plo  rf");
    asm("         ghi  ra");
    asm("         adci 0");
    asm("         phi  rf");
    asm("         lda  rf         ; cluster msb");
    asm("         phi  rc");
    asm("         ldn  rf         ; cluster lsb, rf = slot + 130");
    asm("         str  rf         ; d_ino lsb");
    asm("         inc  rf");
    asm("         ghi  rc");
    asm("         str  rf         ; d_ino msb, slot + 131");
    asm("         dec  rf");
    asm("         dec  rf         ; rf = slot + 129");
    asm("         ldi  0          ; clear the byte after d_attr");
    asm("         str  rf");

    slot += sizeof(struct dirent);
  }

  /* save the position after the last entry read */
  arg = dirp->dd_state;
  asm("         gosub s_lget16  ; get the state buffer variable ");
  asm("           dw -6         ; from local variable stack");
  asm("         copy ra, rf     ; copy state buffer pointer");
  _KSAVE
  asm("         call K_DIR_SAVE_STATE ; save the scan position");
  _KRESTORE

  return n;
}
