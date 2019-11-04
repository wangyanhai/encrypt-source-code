/************************************************************************/
/* ENCRYPT_EXT:加密算法扩展库  
 * guoqw  2019.11
*/
/************************************************************************/

#ifndef _ENCRYPTEX_H_
#define _ENCRYPTEX_H_
#include <string>

/*
 *	函数功能:    单组加密
 *	plain:	     [IN]明文数据 
 *  return:      密文ASC数据
 */
ENCRYPT_SM_EXPORT std::string EncryptToAsc(unsigned char *plain);


/*
 *	函数功能:    单组解密
 *  cipher:      [IN]ASC密文数据
 *  return:      明文数据
 */
ENCRYPT_SM_EXPORT std::string DecryptFromAsc(unsigned char *cipher);

/*
*	函数功能:    单组解密
*  cipher:      [IN]ASC密文数据
*  return:      明文数据
*/
ENCRYPT_SM_EXPORT char* RetSelf(char* str);

#endif                     
