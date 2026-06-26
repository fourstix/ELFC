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
..\elfc -L _tz_is_dst_active.prg
..\elfc -L _tz_parse.prg
..\elfc -L tzset_all.prg
..\elfc -L tzset_us.prg
..\elfc -L utctime.c

type _asctime2.prg _asctime.prg _cstime2.prg _cstime.prg > time.lib
type _ctime2.prg _ctime.prg _dow.prg _doy.prg gmtime.prg >> time.lib
type localtime.prg mktime.prg _strftime2.prg _strftime.prg >> time.lib
type systime.prg time.prg timegm.prg _time_t_to_tm.prg timezone.prg >> time.lib
type _tm_to_time_t.prg _tz_is_dst_active.prg _tz_parse.prg >> time.lib
type tzset_all.prg tzset_us.prg utctime.prg >> time.lib

copy time.lib ..\lib\time.lib
