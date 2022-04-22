#ifndef CHINESE_CALENDAR_H
#define CHINESE_CALENDAR_H

    #ifdef __cplusplus
        extern "C" {
    #endif

            /* 将阳历转换为阴历
             * solarYear  阳历的年
             * solarMonth 阳历的月
             * solarDay   阳历的日
             * return 示例: 正月初一, 二月初二, 腊月初八
             */
            char* get_chinese_lunar_date(int solarYear, int solarMonth, int solarDay);

            /* 获得中国节日，以中国汉字输出
             * solarYear  阳历的年
             * solarMonth 阳历的月
             * solarDay   阳历的日
             */
            char* get_chinese_festival1(int solarYear, int solarMonth, int solarDay);

            /* 获得中国节日，以中国汉字输出
             * chineseLunarDate 阴历的月日: 示例: 正月初一, 二月初二, 腊月初八
             */
            char* get_chinese_festival2(const char *chineseLunarDate);

            /* 获得中国节日，以中国汉字输出
             * solarYear  阳历的年
             * solarMonth 阳历的月
             * solarDay   阳历的日
             * lunarMonthAndDay 阴历的月日: 示例: 正月初一, 二月初二, 腊月初八
             */
            char* get_chinese_festival3(int solarYear, int solarMonth, int solarDay, const char *chineseLunarDate);

            /* 如果给定的阳历日期是某个节气，返回该节气，否则返回NULL
             * solarYear  阳历的年
             * solarMonth 阳历的月
             * solarDay   阳历的日
             */
            char* get_chinese_jieqi(int solarYear, int solarMonth, int solarDay);

            /* 得到给定的阳历年的全部节气和对应阳历日期
             * solarYear  阳历的年
             */
            char** get_chinese_jieqi_list(int solarYear);

    #ifdef __cplusplus
        }
    #endif
#endif
