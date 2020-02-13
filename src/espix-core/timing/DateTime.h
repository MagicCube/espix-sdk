#include <time.h>

struct DateTime {
  DateTime(long ticks, unsigned long offset = 8 * 60 * 60 * 1000) {
    _ticks = ticks;
    time_t rawTime = time(nullptr);
    time_t localTime = rawTime + offset / 1000;
    _localTime = localtime(&localTime);
  }

  DateTime(struct tm *localTime) {
    _localTime = localTime;
  }

  int getFullYear() {
    return _localTime->tm_year + 1900;
  }

  int getMonth() {
    return _localTime->tm_mon;
  }

  int getDate() {
    return _localTime->tm_mday;
  }

  int getDay() {
    return _localTime->tm_wday;
  }

  int getHours() {
    return _localTime->tm_hour;
  }

  int getMinutes() {
    return _localTime->tm_min;
  }

  int getSeconds() {
    return _localTime->tm_sec;
  }

  int getTicks() {
    return _ticks;
  }

  /**
   *
   * 格式化日期。
   *
   * %a	缩写的星期几名称	Sun
   * %A	完整的星期几名称	Sunday
   * %b	缩写的月份名称	Mar
   * %B	完整的月份名称	March
   * %c	日期和时间表示法	Sun Aug 19 02:56:02 2012
   * %d	一月中的第几天（01-31）	19
   * %H	24 小时格式的小时（00-23）	14
   * %I	12 小时格式的小时（01-12）	05
   * %j	一年中的第几天（001-366）	231
   * %m	十进制数表示的月份（01-12）	08
   * %M	分（00-59）	55
   * %p	AM 或 PM 名称	PM
   * %S	秒（00-61）	02
   * %U	一年中的第几周，以第一个星期日作为第一周的第一天（00-53）	33
   * %w	十进制数表示的星期几，星期日表示为 0（0-6）	4
   * %W	一年中的第几周，以第一个星期一作为第一周的第一天（00-53）	34
   * %x	日期表示法	08/19/12
   * %X	时间表示法	02:50:06
   * %y	年份，最后两个数字（00-99）	01
   * %Y	年份	2012
   * %Z	时区的名称或缩写	CDT
   * %%	一个 % 符号	%
  */
  String toString(String format = "%T") {
    char buffer[24];
    strftime(buffer, 9, format.c_str(), _localTime);
    return buffer;
  }

private:
  long _ticks;
  struct tm *_localTime;
};
