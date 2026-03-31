#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math32.h>

#pragma             extrn Cerrno
#pragma             extrn Clseek32
#pragma             extrn Cto_int32
#pragma             extrn Ccmp32
#pragma .link .library math32.lib

int fsetpos(FILE *f, pos_t *pos) {
    off_t new_pos;
    off_t error;
    off_t tmp;

    if (f == NULL || pos == NULL) {
        errno = EINVAL;
        return -1;
    }

    /* can't set position of a system IO stream */
    if (f->mode == _IOSYS) {
        errno = EBADF;
        return -1;
    }

    /* setting position wipes out character push-back buffer and clears EOF */
    f->ch = EOF;
    f->iom &= ~_FEOF;

    /* temporary workaround for error in deref pointer argument */
    tmp = *pos;
    new_pos = lseek32(f->fd, tmp, SEEK_SET);

    error = to_int32(-1);
    if (cmp32(new_pos, error) == 0) {
        return -1;
    }

    return 0;
}
