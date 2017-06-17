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

//===================================================ԭʼ�����  
/* Table of CRCs of all 8-bit messages. ÿ��Ԫ�ؽ����� һ���ֽ�Ҳ����8λ*/
unsigned long crc_table[256];

/* Flag: has the table been computed? Initially false.
���ȫ�ֱ��������ж��Ƿ���Ѿ���ʼ�����ˣ���������һ���������������͵ĳ������еĶ������棬�����־���Խ�ʡʱ�䲻�ö�γ�ʼ��by datrilla */
int crc_table_computed = 0;

/* Make the table for a fast CRC. ����һ����ʼ��һ��CRC-32���ֽڵĿ��ٲ��ı�
���˺þã���ô���ѭ���������Ǹ�˵��CRC-32�����ϲ�һ����
����������ȥ����edb88320��������˳����
1*x^0+1*x^1+1*x^2+0*x^3+1*x^4+1*x^5+0*x^6+1+x^7+1*x^8����+1*x^32=CRC-32
1110 1101 1011 1000 1000 0011 0010 0000 (1)
EDB88320 (1) �����1������CRC�̶������λҪΪ1.
����crc_table[1]��128��crc-32����������n=0000 0001   ����ֵΪ 1000 0000��
by datrilla*/
void make_crc_table(void)
{
	unsigned long c;
	int n, k;
	/*��Ϊǰ��ע�͵�(1)�����⣬���Դ�[0,255]��������������⣬����1��Ӧ������0000 0001 ��1��ʼ����by datrilla*/
	for (n = 0; n < 256; n++) {
		c = (unsigned long)n;
		for (k = 0; k < 8; k++) {
			if (c & 1)/*�����������λΪ1����Ҫģ�����㣬��crc-32��(1)�϶������¸������У�������ʽ������ֱ��ԭ������by datrilla*/
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
		/*�ʼ������cΪ0xffffffffL���μ��������crc()�������ĵ�һ������
		(c ^ buf[n]) & 0xff ����ǰbuf[n]������c���ֽڰ�λ���
		crc_table[(c ^ buf[n]) & 0xff]�����ֽڱ��ж�ȡ��Ӧ��������
		crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8)���Ѷ�ȡ��������������c�����������ֽڰ�λ��򣬲���ֵ����c*/
	}
	return c;
}

/* Return the CRC of the bytes buf[0..len-1]. */
unsigned long crc(unsigned char *buf, int len)
{
	return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;/*�ѵõ���ֵ�����Ժ���*/
}

#endif