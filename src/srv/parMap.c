#include "parMap.h"

InterfaceData_type parMap[PAR_MAP_LENGTH];

void parMapInit()
{
    parMap[0].add[0]=0x30,	    parMap[0].add[1]=0x01;
    parMap[1].add[0]=0x30,	    parMap[1].add[1]=0x02;
    parMap[2].add[0]=0x30,	    parMap[2].add[1]=0x03;
    parMap[3].add[0]=0x30,	    parMap[3].add[1]=0x04;
    parMap[4].add[0]=0x30,	    parMap[4].add[1]=0x05;
    parMap[5].add[0]=0x30,	    parMap[5].add[1]=0x06;
    parMap[6].add[0]=0x30,	    parMap[6].add[1]=0x07;
    parMap[7].add[0]=0x30,	    parMap[7].add[1]=0x08;
    parMap[8].add[0]=0x30,	    parMap[8].add[1]=0x09;
    parMap[9].add[0]=0x30,	    parMap[9].add[1]=0x0A;
    parMap[10].add[0]=0x30,	    parMap[10].add[1]=0x0B;
    parMap[11].add[0]=0x30,	    parMap[11].add[1]=0x0C;
    parMap[12].add[0]=0x30,	    parMap[12].add[1]=0x0D;
    parMap[13].add[0]=0x30,	    parMap[13].add[1]=0x0E;
    parMap[14].add[0]=0x30,	    parMap[14].add[1]=0x0F;
    parMap[15].add[0]=0x30,	    parMap[15].add[1]=0x10;
    parMap[16].add[0]=0x30,	    parMap[16].add[1]=0x11;
    parMap[17].add[0]=0x30,	    parMap[17].add[1]=0x12;
    parMap[18].add[0]=0xF0,	    parMap[18].add[1]=0x01;
    parMap[19].add[0]=0xF0,	    parMap[19].add[1]=0x02;
    parMap[20].add[0]=0xF0,	    parMap[20].add[1]=0x03;
    parMap[21].add[0]=0xF0,	    parMap[21].add[1]=0x04;
    parMap[22].add[0]=0x01,	    parMap[22].add[1]=0x00;
    parMap[23].add[0]=0x01,	    parMap[23].add[1]=0x01;
    parMap[24].add[0]=0x01,	    parMap[24].add[1]=0x02;
    parMap[25].add[0]=0x01,	    parMap[25].add[1]=0x03;
    parMap[26].add[0]=0x01,	    parMap[26].add[1]=0x04;
    parMap[27].add[0]=0x01,	    parMap[27].add[1]=0x05;
    parMap[28].add[0]=0x01,	    parMap[28].add[1]=0x06;
    parMap[29].add[0]=0x01,	    parMap[29].add[1]=0x07;
    parMap[30].add[0]=0x01,	    parMap[30].add[1]=0x08;
    parMap[31].add[0]=0x01,	    parMap[31].add[1]=0x09;
    parMap[32].add[0]=0x01,	    parMap[32].add[1]=0x0A;
    parMap[33].add[0]=0x01,	    parMap[33].add[1]=0x0B;
    parMap[34].add[0]=0x01,	    parMap[34].add[1]=0x0C;
    parMap[35].add[0]=0x01,	    parMap[35].add[1]=0x0D;
    parMap[36].add[0]=0x01,	    parMap[36].add[1]=0x0E;
    parMap[37].add[0]=0x01,	    parMap[37].add[1]=0x1F;
    parMap[38].add[0]=0x01,	    parMap[38].add[1]=0x10;
    parMap[39].add[0]=0x01,	    parMap[39].add[1]=0x11;
    parMap[40].add[0]=0x01,	    parMap[40].add[1]=0x12;
    parMap[41].add[0]=0x01,	    parMap[41].add[1]=0x13;
    parMap[42].add[0]=0x01,	    parMap[42].add[1]=0x14;
    parMap[43].add[0]=0x01,	    parMap[43].add[1]=0x15;
    parMap[44].add[0]=0x01,	    parMap[44].add[1]=0x16;
    parMap[45].add[0]=0x01,	    parMap[45].add[1]=0x17;
    parMap[46].add[0]=0x01,	    parMap[46].add[1]=0x1E;
    parMap[47].add[0]=0x01,	    parMap[47].add[1]=0x1F;
    parMap[48].add[0]=0x01,	    parMap[48].add[1]=0x20;
    parMap[49].add[0]=0x01,	    parMap[49].add[1]=0x21;
    parMap[50].add[0]=0x01,	    parMap[50].add[1]=0x22;
    parMap[51].add[0]=0x01,	    parMap[51].add[1]=0x23;
    parMap[52].add[0]=0x01,	    parMap[52].add[1]=0x24;
    parMap[53].add[0]=0x01,	    parMap[53].add[1]=0x25;
    parMap[54].add[0]=0x01,	    parMap[54].add[1]=0x26;
    parMap[55].add[0]=0x02,	    parMap[55].add[1]=0x00;
    parMap[56].add[0]=0x02,	    parMap[56].add[1]=0x01;
    parMap[57].add[0]=0x02,	    parMap[57].add[1]=0x02;
    parMap[58].add[0]=0x02,	    parMap[58].add[1]=0x03;
    parMap[59].add[0]=0x02,	    parMap[59].add[1]=0x04;
    parMap[60].add[0]=0x02,	    parMap[60].add[1]=0x05;
    parMap[61].add[0]=0x02,	    parMap[61].add[1]=0x06;
    parMap[62].add[0]=0x02,	    parMap[62].add[1]=0x07;
    parMap[63].add[0]=0x02,	    parMap[63].add[1]=0x08;
    parMap[64].add[0]=0x02,	    parMap[64].add[1]=0x09;
    parMap[65].add[0]=0x02,	    parMap[65].add[1]=0x0A;
    parMap[66].add[0]=0x02,	    parMap[66].add[1]=0x0B;
    parMap[67].add[0]=0x02,	    parMap[67].add[1]=0x0C;
    parMap[68].add[0]=0x02,	    parMap[68].add[1]=0x0D;
    parMap[69].add[0]=0x02,	    parMap[69].add[1]=0x0E;
    parMap[70].add[0]=0x02,	    parMap[70].add[1]=0x0F;
    parMap[71].add[0]=0x02,	    parMap[71].add[1]=0x10;
    parMap[72].add[0]=0x02,	    parMap[72].add[1]=0x11;
    parMap[73].add[0]=0x02,	    parMap[73].add[1]=0x12;
    parMap[74].add[0]=0x02,	    parMap[74].add[1]=0x13;
    parMap[75].add[0]=0x02,	    parMap[75].add[1]=0x14;
    parMap[76].add[0]=0x02,	    parMap[76].add[1]=0x15;
    parMap[77].add[0]=0x02,	    parMap[77].add[1]=0x16;
    parMap[78].add[0]=0x02,	    parMap[78].add[1]=0x17;
    parMap[79].add[0]=0x02,	    parMap[79].add[1]=0x18;
    parMap[80].add[0]=0x02,	    parMap[80].add[1]=0x19;
    parMap[81].add[0]=0x02,	    parMap[81].add[1]=0x1A;
    parMap[82].add[0]=0x02,	    parMap[82].add[1]=0x1B;
    parMap[83].add[0]=0x02,	    parMap[83].add[1]=0x1C;
    parMap[84].add[0]=0x02,	    parMap[84].add[1]=0x1D;
    parMap[85].add[0]=0x02,	    parMap[85].add[1]=0x1E;
    parMap[86].add[0]=0x02,	    parMap[86].add[1]=0x1F;
    parMap[87].add[0]=0x02,	    parMap[87].add[1]=0x20;
    parMap[88].add[0]=0x02,	    parMap[88].add[1]=0x21;
    parMap[89].add[0]=0x02,	    parMap[89].add[1]=0x22;
    parMap[90].add[0]=0x02,	    parMap[90].add[1]=0x23;
    parMap[91].add[0]=0x02,	    parMap[91].add[1]=0x24;
    parMap[92].add[0]=0x02,	    parMap[92].add[1]=0x25;
    parMap[93].add[0]=0x02,	    parMap[93].add[1]=0x26;
    parMap[94].add[0]=0x02,	    parMap[94].add[1]=0x27;
    parMap[95].add[0]=0x02,	    parMap[95].add[1]=0x28;
    parMap[96].add[0]=0x02,	    parMap[96].add[1]=0x29;
    parMap[97].add[0]=0x02,	    parMap[97].add[1]=0x2A;
    parMap[98].add[0]=0x02,	    parMap[98].add[1]=0x2B;
    parMap[99].add[0]=0x02,	    parMap[99].add[1]=0x2C;
    parMap[100].add[0]=0x03,	parMap[100].add[1]=0x00;
    parMap[101].add[0]=0x03,	parMap[101].add[1]=0x01;
    parMap[102].add[0]=0x03,	parMap[102].add[1]=0x02;
    parMap[103].add[0]=0x03,	parMap[103].add[1]=0x03;
    parMap[104].add[0]=0x03,	parMap[104].add[1]=0x04;
    parMap[105].add[0]=0x03,	parMap[105].add[1]=0x05;
    parMap[106].add[0]=0x03,	parMap[106].add[1]=0x06;
    parMap[107].add[0]=0x03,	parMap[107].add[1]=0x07;
    parMap[108].add[0]=0x04,	parMap[108].add[1]=0x00;
    parMap[109].add[0]=0x04,	parMap[109].add[1]=0x01;
    parMap[110].add[0]=0x04,	parMap[110].add[1]=0x02;
    parMap[111].add[0]=0x04,	parMap[111].add[1]=0x03;
    parMap[112].add[0]=0x04,	parMap[112].add[1]=0x04;
    parMap[113].add[0]=0x04,	parMap[113].add[1]=0x05;
    parMap[114].add[0]=0x04,	parMap[114].add[1]=0x06;
    parMap[115].add[0]=0x04,	parMap[115].add[1]=0x07;
    parMap[116].add[0]=0x04,	parMap[116].add[1]=0x08;
    parMap[117].add[0]=0x04,	parMap[117].add[1]=0x09;
    parMap[118].add[0]=0x04,	parMap[118].add[1]=0x0A;
}

void parMapWrite(unsigned char addH, unsigned char addL, unsigned char Hdata, unsigned char Ldata)
{
    unsigned char i = 0;
    for(i = 0; i < PAR_MAP_LENGTH; i ++)
    {
        if((parMap[i].add[0] == addH) && (parMap[i].add[1] == addL))
        {
            parMap[i].opData[0] = Hdata;
            parMap[i].opData[1] = Ldata;
        }
        else
        {

        }
    }
}

void parMapRead(unsigned char addH, unsigned char addL, unsigned char *Hdata, unsigned char *Ldata)
{
    unsigned char i = 0;
    for(i = 0; i < PAR_MAP_LENGTH; i ++)
    {
        if((parMap[i].add[0] == addH) && (parMap[i].add[1] == addL))
        {
            *Hdata = parMap[i].opData[0];
            *Ldata = parMap[i].opData[1];
        }
        else
        {
            /* code */
        }
        
    }
}