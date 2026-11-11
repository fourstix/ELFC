..\elfc -L _asctime2.c
..\elfc -L _asctime.c
..\elfc -L _cstime2.c
..\elfc -L _cstime.c
..\elfc -L _ctime2.c
..\elfc -L _ctime.c
..\elfc -L _dow.c
..\elfc -L _doy.c
..\elfc -L gmtime.c
..\elfc -L localtime.c
..\elfc -L mktime.c
..\elfc -L _strftime2.c
..\elfc -L _strftime.c
..\elfc -L systime.c
..\elfc -L time.c
..\elfc -L timegm.c
..\elfc -L _time_t_to_tm.c
..\elfc -L timezone.c
..\elfc -L _tm_to_time_t.c
..\elfc -L _tz_is_dst_active.c
..\elfc -L _tz_parse.c
..\elfc -L tzset_all.c
..\elfc -L tzset_us.c
..\elfc -L utctime.c

type _asctime.prg _asctime2.prg _cstime.prg _cstime2.prg _ctime.prg _ctime2.prg > time.lib
type _dow.prg _doy.prg _strftime.prg _strftime2.prg _time_t_to_tm.prg _tm_to_time_t.prg >> time.lib
type _tz_is_dst_active.prg _tz_parse.prg gmtime.prg localtime.prg mktime.prg systime.prg >> time.lib
type time.prg timegm.prg timezone.prg tzset_all.prg tzset_us.prg utctime.prg >> time.lib

copy time.lib ..\lib\time.lib
