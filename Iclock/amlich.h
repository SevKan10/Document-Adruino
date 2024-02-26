#ifndef _AMLICH_H
#define _ANLICH_H
signed char dayd, monthd, yeard;
unsigned char lunar_day, lunar_month, lunar_year;

struct MONTH_INFO
{
    unsigned int N_AL_DT_DL : 5;
    unsigned int T_AL_DT_DL : 4;
    unsigned int SN_CT_AL : 1;
    unsigned int TN_B_THT : 1;
    unsigned int SN_CT_DL : 2;
};

union LUNAR_RECORD
{
    unsigned int Word;
    struct MONTH_INFO Info;
};

// Lunar Calendar Lookup Table
// From 1/1/2020 to 31/12/2039
#define BEGINNING_YEAR 20

const long int LUNAR_CALENDAR_LOOKUP_TABLE[] = {
    //2020
    0x1B87,
    0x0828,
    0x1A48,
    0x1269,
    0x1A89,
    0x108A,
    0x1AAB,
    0x18CC,
    0x10EE,
    0x1B0F,
    0x1130,
    0x1951,
    //2021
    0x1B73,
    0x0394,
    0x1832,
    0x1254,
    0x1A74,
    0x1095,
    0x1AB6,
    0x18D7,
    0x12F9,
    0x1919,
    0x133B,
    0x195B,
    //2022
    0x1B7D,
    0x0021,
    0x1A3D,
    0x1061,
    0x1A81,
    0x12A3,
    0x1AC3,
    0x18E4,
    0x1306,
    0x1926,
    0x1348,
    0x1968,
    //2023
    0x1B8A,
    0x002B,
    0x1A4A,
    0x104B,
    0x186C,
    0x128E,
    0x1AAE,
    0x18CF,
    0x12F1,
    0x1B11,
    0x1132,
    0x1B53,
    //2024
    0x1974,
    0x0B96,
    0x1835,
    0x1257,
    0x1877,
    0x1099,
    0x1ABA,
    0x18DB,
    0x12FD,
    0x1B1D,
    0x1141,
    0x1B61,
    //2025
    0x1982,
    0x0224,
    0x1842,
    0x1264,
    0x1884,
    0x10A6,
    0x1AC7,
    0x18C8,
    0x12EA,
    0x190A,
    0x132C,
    0x1B4C,
    //2026
    0x1B6D,
    0x018E,
    0x1A2D,
    0x104E,
    0x1A6F,
    0x1090,
    0x18B1,
    0x1AD3,
    0x10F4,
    0x1915,
    0x1337,
    0x1B57,
    //2027
    0x1B78,
    0x0199,
    0x1A38,
    0x1259,
    0x1879,
    0x129B,
    0x18BB,
    0x18DD,
    0x1301,
    0x1922,
    0x1344,
    0x1B64,
    //2028
    0x1985,
    0x0A27,
    0x1A46,
    0x1267,
    0x1887,
    0x12A9,
    0x18A9,
    0x18CB,
    0x12ED,
    0x190D,
    0x112F,
    0x1B50,
    //2029
    0x1B71,
    0x0192,
    0x1A31,
    0x1252,
    0x1872,
    0x1294,
    0x18B4,
    0x1AD6,
    0x10F7,
    0x1B18,
    0x1139,
    0x195A,
    //2030
    0x1B7C,
    0x019D,
    0x1A3C,
    0x125D,
    0x187D,
    0x12A1,
    0x1AC1,
    0x1AE3,
    0x1104,
    0x1B25,
    0x1146,
    0x1B67,
    //2031
    0x1988,
    0x002A,
    0x1A49,
    0x106A,
    0x1A6B,
    0x128C,
    0x18AC,
    0x1ACE,
    0x12EF,
    0x190F,
    0x1331,
    0x1951,
    //2032
    0x1B73,
    0x0994,
    0x1834,
    0x1256,
    0x1876,
    0x1298,
    0x18B8,
    0x1ADA,
    0x12FB,
    0x191B,
    0x133D,
    0x1B5D,
    //2033
    0x1981,
    0x0022,
    0x1841,
    0x1062,
    0x1883,
    0x12A5,
    0x18C5,
    0x1AE7,
    0x1108,
    0x1B29,
    0x134A,
    0x1B6A,
    //2034
    0x196B,
    0x038D,
    0x182B,
    0x124D,
    0x186D,
    0x108F,
    0x1AB0,
    0x18D1,
    0x10F3,
    0x1B14,
    0x1335,
    0x1B55,
    //2035
    0x1976,
    0x0398,
    0x1A36,
    0x1057,
    0x1A78,
    0x1099,
    0x18BA,
    0x1ADC,
    0x10FD,
    0x1921,
    0x1342,
    0x1962,
    //2036
    0x1B84,
    0x0A25,
    0x1A44,
    0x1065,
    0x1A86,
    0x10A7,
    0x18C8,
    0x1ACA,
    0x10EB,
    0x190C,
    0x132E,
    0x194E,
    //2037
    0x1B70,
    0x0391,
    0x1A2F,
    0x1050,
    0x1A71,
    0x1292,
    0x18B2,
    0x18D4,
    0x12F6,
    0x1916,
    0x1138,
    0x1B59,
    //2038
    0x197A,
    0x039C,
    0x1A3A,
    0x105B,
    0x1A7C,
    0x129D,
    0x18BD,
    0x1AE1,
    0x1303,
    0x1923,
    0x1145,
    0x1B66,
    //2039
    0x1987,
    0x0229,
    0x1A47,
    0x1068,
    0x1A89,
    0x12AA,
    0x18AA,
    0x1ACC,
    0x10ED,
    0x1B0E,
    0x112F,
    0x1950,
};
void settingAmLich(unsigned char SolarDate, unsigned char SolarMonth, unsigned char SolarYear)
{
    unsigned char N_AL_DT_DL;
    unsigned char T_AL_DT_DL;
    unsigned char SN_CT_AL;
    unsigned char TN_B_THT;
    unsigned char N_AL_DT_DL_TT;
    unsigned char T_AL_DT_DL_TT;

    union LUNAR_RECORD lr;

    lr.Word = LUNAR_CALENDAR_LOOKUP_TABLE[(SolarYear - BEGINNING_YEAR) * 12 + SolarMonth - 1];
    N_AL_DT_DL = lr.Info.N_AL_DT_DL;
    T_AL_DT_DL = lr.Info.T_AL_DT_DL;
    SN_CT_AL = lr.Info.SN_CT_AL + 29;
    TN_B_THT = lr.Info.TN_B_THT;

    lr.Word = LUNAR_CALENDAR_LOOKUP_TABLE[(SolarYear - BEGINNING_YEAR) * 12 + SolarMonth];
    N_AL_DT_DL_TT = lr.Info.N_AL_DT_DL;
    T_AL_DT_DL_TT = lr.Info.T_AL_DT_DL;

    // Tinh ngay & thang
    if (N_AL_DT_DL == SN_CT_AL && N_AL_DT_DL_TT == 2)
    {
        if (SolarDate == 1)
        {
            (lunar_day) = N_AL_DT_DL;
            (lunar_month) = T_AL_DT_DL;
        }
        else if (SolarDate == 31)
        {
            (lunar_day) = 1;
            (lunar_month) = T_AL_DT_DL_TT;
        }
        else
        {
            (lunar_day) = SolarDate - 1;
            if (TN_B_THT)
            {
                (lunar_month) = T_AL_DT_DL;
            }
            else
            {
                (lunar_month) = T_AL_DT_DL == 12 ? 1 : (T_AL_DT_DL + 1);
            }
        }
    }
    else
    {
        (lunar_day) = SolarDate + N_AL_DT_DL - 1;
        if ((lunar_day) <= SN_CT_AL)
        {
            (lunar_month) = T_AL_DT_DL;
        }
        else
        {
            (lunar_day) -= SN_CT_AL;

            (lunar_month) = T_AL_DT_DL + 1 - TN_B_THT;
            if ((lunar_month) == 13)
                (lunar_month) = 1;
        }
    }

    // Tinh Nam
    if (SolarMonth >= (lunar_month))
    {
        (lunar_year) = SolarYear;
    }
    else
    {
        (lunar_year) = SolarYear - 1;
    }
}
#endif