#ifndef CHINESE_CALENDAR_H
#define CHINESE_CALENDAR_H

    #ifdef __cplusplus
        extern "C" {
    #endif

            /* 将阳历转换为阴历
             * year  阳历的年
             * month 阳历的月
             * day   阳历的日
             */
            char* solar2lunar(int year, int month, int day);

            /* 如果指定的阳历日期是某个节日，返回该节日，否则返回NULL
             * year  阳历的年
             * month 阳历的月
             * day   阳历的日
             */
            char* jieri(int year, int month, int day, const char *lunarMonthAndDay);
 
            /* 如果指定的阳历日期是某个节气，返回该节气，否则返回NULL
             * year  阳历的年
             * month 阳历的月
             * day   阳历的日
             */
            char* jieqi(int year, int month, int day);

            /* 得到指定年的全部节气和对应阳历日期
             * year  阳历的年
             * month 阳历的月
             * day   阳历的日
             */
            char** jieqi_list(int year);

    #ifdef __cplusplus
        }
    #endif
#endif
