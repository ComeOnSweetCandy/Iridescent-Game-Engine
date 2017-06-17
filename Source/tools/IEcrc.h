/***********************************
* name     : IEimage.h
* creater  : cosc
* info     : load images
* date     : 2016/11/20
* version  : 1.0
* remark   : none
************************************/

#ifndef __IE_CRC__
#define __IE_CRC__

#include "../global/IEstdafx.h"

//===================================================原始代码段  
/* Table of CRCs of all 8-bit messages. 每个元素仅代表： 一个字节也就是8位*/
unsigned long crc_table[256];

/* Flag: has the table been computed? Initially false.
这个全局变量用来判断是否表已经初始化过了，单次运行一般就那样，如果大型的持续运行的东东里面，这个标志可以节省时间不用多次初始化by datrilla */
int crc_table_computed = 0;

/* Make the table for a fast CRC. 就是一个初始化一个CRC-32按字节的快速查阅表
想了好久，怎么这个循环检测码和那个说的CRC-32和书上不一样，
后来颠来倒去发现edb88320他，他的顺序是
1*x^0+1*x^1+1*x^2+0*x^3+1*x^4+1*x^5+0*x^6+1+x^7+1*x^8……+1*x^32=CRC-32
1110 1101 1011 1000 1000 0011 0010 0000 (1)
EDB88320 (1) 后面的1是所有CRC固定的最高位要为1.
比如crc_table[1]是128的crc-32的余数【即n=0000 0001   代表值为 1000 0000】
by datrilla*/
void make_crc_table(void)
{
	unsigned long c;
	int n, k;
	/*因为前面注释的(1)的问题，所以从[0,255]的整数从右往左测，比如1对应二进制0000 0001 从1开始往左by datrilla*/
	for (n = 0; n < 256; n++) {
		c = (unsigned long)n;
		for (k = 0; k < 8; k++) {
			if (c & 1)/*若余数的最高位为1，需要模二运算，而crc-32的(1)肯定不再下个余数中，就如下式，否则直接原来不变by datrilla*/
				c = 0xedb88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		crc_table[n] = c;
	}
	crc_table_computed = 1;
}

/* Update a running CRC with the bytes buf[0..len-1]--the CRC
should be initialized to all 1's, and the transmitted value
is the 1's complement of the final running CRC (see the
crc() routine below)). */
unsigned long update_crc(unsigned long crc, unsigned char * buf, int len)
{
	unsigned long c = crc;
	int n;

	if (!crc_table_computed)
		make_crc_table();
	for (n = 0; n < len; n++) {
		c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
		/*最开始的余数c为0xffffffffL；参见从下面的crc()传进来的第一个参数
		(c ^ buf[n]) & 0xff ：当前buf[n]和余数c低字节按位异或，
		crc_table[(c ^ buf[n]) & 0xff]：在字节表中读取对应的余数，
		crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8)：把读取到的余数和余数c的另外三个字节按位异或，并把值赋给c*/
	}
	return c;
}

/* Return the CRC of the bytes buf[0..len-1]. */
unsigned long crc(unsigned char *buf, int len)
{
	return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;/*把得到的值进行以后处理*/
}

#endif