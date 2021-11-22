#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chinese-calendar.h"

unsigned int LunarCalendarTable[199] = {
    0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A,/*1901-1910*/
    0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754,/*1911-1920*/
    0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E,/*1921-1930*/
    0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48,/*1931-1940*/
    0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51,/*1941-1950*/
    0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x6AD53C,/*1951-1960*/
    0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46,/*1961-1970*/
    0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50,/*1971-1980*/
    0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB,/*1981-1990*/
    0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645,/*1991-2000*/
    0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E,/*2001-2010*/
    0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9,/*2011-2020*/
    0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43,/*2021-2030*/
    0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C,/*2031-2040*/
    0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37,/*2041-2050*/
    0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42,/*2051-2060*/
    0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B,/*2061-2070*/
    0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6,/*2071-2080*/
    0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E,/*2081-2090*/
    0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5          /*2091-2099*/
};
int MonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

int LunarCalendar(int year, int month, int day, unsigned int* LunarCalendarDay) {
    int Spring_NY,Sun_NY,StaticDayCount;
    int index,flag;
    //Spring_NY 记录春节离当年元旦的天数。
    //Sun_NY 记录阳历日离当年元旦的天数。
    if ( ((LunarCalendarTable[year-1901] & 0x0060) >> 5) == 1)
        Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1;
    else
        Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1 + 31;
    Sun_NY = MonthAdd[month-1] + day - 1;
    if ( (!(year % 4)) && (month > 2))
        Sun_NY++;
    //StaticDayCount记录大小月的天数 29 或30
    //index 记录从哪个月开始来计算。
    //flag 是用来对闰月的特殊处理。
    //判断阳历日在春节前还是春节后
    if (Sun_NY >= Spring_NY)//阳历日在春节后（含春节那天）
    {
        Sun_NY -= Spring_NY;
        month = 1;
        index = 1;
        flag = 0;
        if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            StaticDayCount = 29;
        else
            StaticDayCount = 30;
        while (Sun_NY >= StaticDayCount)
        {
            Sun_NY -= StaticDayCount;
            index++;
            if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) )
            {
                flag = ~flag;
                if (flag == 0)
                    month++;
            }
            else
                month++;
            if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                StaticDayCount=29;
            else
                StaticDayCount=30;
        }
        day = Sun_NY + 1;
    }
    else //阳历日在春节前
    {
        Spring_NY -= Sun_NY;
        year--;
        month = 12;
        if ( ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) == 0)
            index = 12;
        else
            index = 13;
        flag = 0;
        if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
            StaticDayCount = 29;
        else
            StaticDayCount = 30;
        while (Spring_NY > StaticDayCount)
        {
            Spring_NY -= StaticDayCount;
            index--;
            if (flag == 0)
                month--;
            if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
                flag = ~flag;
            if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                StaticDayCount = 29;
            else
                StaticDayCount = 30;
        }
        day = StaticDayCount - Spring_NY + 1;
    }
    *LunarCalendarDay |= day;
    *LunarCalendarDay |= (month << 6);
    return (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20)) ? 1 : 0;
}

const char* CHINESE_DAY[] = {"*","初一","初二","初三","初四","初五",
                                 "初六","初七","初八","初九","初十",
                                 "十一","十二","十三","十四","十五",
                                 "十六","十七","十八","十九","二十",
                                 "廿一","廿二","廿三","廿四","廿五",
                                 "廿六","廿七","廿八","廿九","三十"
                            };
const char* CHINESE_MONTH[] = {"*","正","二","三","四","五","六","七","八","九","十","十一","腊"};


/* 将阳历转换为阴历
 * year  阳历的年
 * month 阳历的月
 * day   阳历的日
 */
char* solar2lunar(int year, int month, int day) {
    char *str = (char*)calloc(13, sizeof(char));

    unsigned int LunarCalendarDay = 0;

    if (LunarCalendar(year, month, day, &LunarCalendarDay)) {
        strcat(str, "闰");
    }
    strcat(str, CHINESE_MONTH[(LunarCalendarDay & 0x3C0) >> 6]);
    strcat(str, "月");
    strcat(str, CHINESE_DAY[LunarCalendarDay & 0x3F]);

    return str;
}

static char* jieRi(const char *str) {
    char *p = (char*)calloc(strlen(str) + 1, sizeof(char));
    strcpy(p, str);
    return p;
}

/* 如果指定的阳历日期是某个节日，返回该节日，否则返回NULL
 * year  阳历的年
 * month 阳历的月
 * day   阳历的日
 */
char* jieri(int year, int month, int day, const char *lunarMonthAndDay) {
    if (month == 1 && day == 1) {
        return jieRi("元旦");
    } else if (month == 2 && day == 14) {
        return jieRi("情人节");
    } else if (month == 3 && day == 8) {
        return jieRi("妇女节");
    } else if (month == 3 && day == 12) {
        return jieRi("植树节");
    } else if (month == 3 && day == 15) {
        return jieRi("消费者权益日");
    } else if (month == 4 && day == 1) {
        return jieRi("愚人节");
    } else if (month == 5 && day == 1) {
        return jieRi("劳动节");
    } else if (month == 5 && day == 4) {
        return jieRi("青年节");
    } else if (month == 5 && day == 12) {
        return jieRi("护士节");
    } else if (month == 5 && day == 18) {
        return jieRi("博物馆日");
    } else if (month == 6 && day == 1) {
        return jieRi("儿童节");
    } else if (month == 7 && day == 1) {
        return jieRi("建党节");
    } else if (month == 8 && day == 1) {
        return jieRi("建军节");
    } else if (month == 9 && day == 10) {
        return jieRi("教师节");
    } else if (month == 10 && day == 1) {
        return jieRi("国庆节");
    } else if (month == 12 && day == 25) {
        return jieRi("圣诞节");
    } else if (NULL == lunarMonthAndDay) {
        return NULL;
    } else {
        if (strcmp(lunarMonthAndDay, "正月初一") == 0) {
            return jieRi("春节");
        } else if (strcmp(lunarMonthAndDay, "正月初七") == 0) {
            return jieRi("小年");
        } else if (strcmp(lunarMonthAndDay, "正月十五") == 0) {
            return jieRi("元宵节");
        } else if (strcmp(lunarMonthAndDay, "二月初二") == 0) {
            return jieRi("龙抬头");
        } else if (strcmp(lunarMonthAndDay, "五月初五") == 0) {
            return jieRi("端午节");
        } else if (strcmp(lunarMonthAndDay, "七月初七") == 0) {
            return jieRi("七夕情人节");
        } else if (strcmp(lunarMonthAndDay, "七月十五") == 0) {
            return jieRi("中元节");
        } else if (strcmp(lunarMonthAndDay, "八月十五") == 0) {
            return jieRi("中秋节");
        } else if (strcmp(lunarMonthAndDay, "九月初九") == 0) {
            return jieRi("重阳节");
        } else if (strcmp(lunarMonthAndDay, "腊月初八") == 0) {
            return jieRi("腊八节");
        }
        return NULL;
    }
}

static const double x_1900_1_6_2_5 = 693966.08680556;

static const int termInfo[] = {
    0      ,21208 ,42467 ,63836 ,85337 ,107014,
    128867,150921,173149,195551,218072,240693,
    263343,285989,308563,331033,353350,375494,
    397447,419210,440795,462224,483532,504758
};

static const char* solar_term_name[] = {
    "小寒","大寒","立春","雨水",
    "惊蛰","春分","清明","谷雨",
    "立夏","小满","芒种","夏至",
    "小暑","大暑","立秋","处暑",
    "白露","秋分","寒露","霜降",
    "立冬","小雪","大雪","冬至"
};

static double get_solar_term(int year, int n) {
    return x_1900_1_6_2_5 + 365.2422 * (year - 1900) + termInfo[n] / (60. * 24);
}

static int format_date(unsigned _days, char* result) {
    static const int mdays[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int y , m , d , diff;
    unsigned days;
    days = 100 * (_days - _days/(3652425L/(3652425L-3652400L)) );
    y    = days / 36524; days %= 36524;
    m    = 1 + days/3044;        /* [1..12] */
    d    = 1 + (days%3044)/100;    /* [1..31] */
    diff =y*365+y/4-y/100+y/400+mdays[m-1]+d-((m<=2&&((y&3)==0)&&((y%100)!=0||y%400==0))) - _days;
    if( diff > 0 && diff >= d )    /* ~0.5% */
    {
        if( m == 1 ) {
            --y; m = 12;
            d = 31 - ( diff - d );
        } else {
            d = mdays[m-1] - ( diff - d );
            if( --m == 2 )
                d += ((y&3)==0) && ((y%100)!=0||y%400==0);
        }
    }
    else
    {
        if( (d -= diff) > mdays[m] )    /* ~1.6% */
        {
            if( m == 2 )
            {
                if(((y&3)==0) && ((y%100)!=0||y%400==0))
                {
                    if( d != 29 )
                        m = 3 , d -= 29;
                }
                else
                {
                    m = 3 , d -= 28;
                }
            }
            else
            {
                d -= mdays[m];
                if( m++ == 12 )
                    ++y , m = 1;
            }
        }
    }
    return sprintf(result, "%04d-%02d-%02d", y, m, d);
}

/* 如果指定的阳历日期是某个节气，返回该节气，否则返回NULL
 * year  阳历的年
 * month 阳历的月
 * day   阳历的日
 */
char* jieqi(int year, int month, int day) {
    int n = 2 * (month - 1);
    if (day > 15) {
        n++;
    }

    char str[11] = {0};
    format_date((unsigned)get_solar_term(year, n), str);

    char str2[11] = {0};
    sprintf(str2, "%04d-%02d-%02d", year, month, day);

    if (strcmp(str, str2) == 0) {
        char *p = (char*)calloc(1, sizeof("立春") + 1);
        strcpy(p, solar_term_name[n]);
        return p;
    } else {
        return NULL;
    }
}

/* 得到指定年的全部节气和对应阳历日期
 * year  阳历的年
 * month 阳历的月
 * day   阳历的日
 */
char** jieqi_list(int year) {
    size_t y = 12 + sizeof("立春");
    char** list = malloc(sizeof(char*) * 24);
    for(int i = 0; i < 24; ++i) {
        char date[11] = {0};
        format_date((unsigned)get_solar_term(year, i), date);
        list[i] = calloc(1, y);
        sprintf(list[i], "%s %s", solar_term_name[i], date);
    }
    return list;
}
