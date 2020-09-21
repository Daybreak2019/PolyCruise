/***********************************************************
 * Author: Wen Li
 * Date  : 9/01/2020
 * Describe: DbCore.h - memory database 
 * History:
   <1> 9/01/2020 , create
************************************************************/

#ifndef _DB_H_
#define _DB_H_ 
#include "MacroDef.h"

enum DB_TYPE
{
    DB_TYPE_BEGIN=1,
    DB_TYPE_DIF_NODE=DB_TYPE_BEGIN,
    DB_TYPE_DIF_EDGE,
    DB_TYPE_DIF_FUNC,
    DB_TYPE_DIF_DEF,
    DB_TYPE_END
};

typedef struct tag_DbReq
{
    BYTE* pKeyCtx;
	DWORD dwKeyLen;
	DWORD dwDataType;
	DWORD dwDataId;
}DbReq;

typedef struct tag_DbAck
{
    BYTE* pDataAddr;
	DWORD dwDataId;
	DWORD dwRev;
}DbAck;


DWORD CreateDataByKey(DbReq* ptCreateReq, DbAck* pCreateAck);
DWORD QueryDataByKey(DbReq* ptQueryKey, DbAck* pQueryAck);


DWORD CreateDataNonKey(DbReq* ptCreateReq, DbAck* pCreateAck);
DWORD QueryDataByID(DbReq* ptQueryReq, DbAck* pQueryAck);


DWORD DeleteDataByID(DbReq* ptDelReq);

DWORD DbCreateTable(DWORD dwDataType, DWORD dwDataLen, DWORD dwKeyLen);

VOID DelDb ();


#endif