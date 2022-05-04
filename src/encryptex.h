/************************************************************************/
/* ENCRYPT_EXT:�����㷨��չ��  
 * guoqw  2019.11
*/
/************************************************************************/

#ifndef _ENCRYPTEX_H_
#define _ENCRYPTEX_H_
#include <string>

/*
 *	��������:    �������
 *	plain:	     [IN]�������� 
 *  return:      ����ASC����
 */
ENCRYPT_SM_EXPORT std::string EncryptToAsc(unsigned char *plain);


/*
 *	��������:    �������
 *  cipher:      [IN]ASC��������
 *  return:      ��������
 */
ENCRYPT_SM_EXPORT std::string DecryptFromAsc(unsigned char *cipher);

/*
*	��������:    �������
*  cipher:      [IN]ASC��������
*  return:      ��������
*/
ENCRYPT_SM_EXPORT char* RetSelf(char* str);

#endif                     
