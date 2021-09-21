/***********************************************************
 * Author: Wen Li
 * Date  : 7/24/2020
 * Describe: DynTrace.c  
 * History:
   <1> 7/24/2020 , create
************************************************************/
#include <sys/syscall.h>
#include "Queue.h"


#ifdef __cplusplus
extern "C"{
#endif

static int gFullTraceFlag = 0;


void TRC_trace0 (ULONG EventId, const char* Msg)
{
    if (gFullTraceFlag)
    {
        printf("%s\r\n", Msg);
        return;
    }

    QNode *Node = InQueue ();
    if (Node == NULL)
    {
        printf ("Queue Full\r\n");
        exit (0);
    }

    strncpy (Node->QBuf, Msg, sizeof(Node->QBuf));
    Node->ThreadId = pthread_self ();
    Node->EventId  = EventId;
    Node->Flag     = TRUE;

    assert (strlen(Node->QBuf) < BUF_SIZE);
    DEBUG ("[TRC_trace0][T:%u]%lx:[%u]%s\r\n", Node->ThreadId, EventId, (unsigned)strlen(Node->QBuf), Node->QBuf);

    return;   
}


void TRC_trace (ULONG EventId, const char* Format, ...)
{
    va_list ap;

    if (gFullTraceFlag)
    {
        char Msg[1024];
        va_start(ap, Format);
        (void)vsnprintf (Msg, sizeof(Msg), Format, ap);
        va_end(ap);
        printf("%s\r\n", Msg);
        return;
    }

    QNode *Node = InQueue ();
    if (Node == NULL)
    {
        printf ("Queue Full\r\n");
        exit (0);
    }

    va_start(ap, Format);
    (void)vsnprintf (Node->QBuf, sizeof(Node->QBuf), Format, ap);
    va_end(ap);

    //Node->ThreadId = syscall(SYS_gettid);
    Node->ThreadId = pthread_self ();
    Node->EventId  = EventId;
    Node->Flag     = TRUE;

    assert (strlen(Node->QBuf) < BUF_SIZE);
    DEBUG ("[TRC_trace][T:%u]%lx:[%u]%s\r\n", Node->ThreadId, EventId, (unsigned)strlen(Node->QBuf), Node->QBuf);

    return;   
}


void TRC_thread (ULONG EventId, char* ThreadEntry, ULONG *ThrId,  char *ThrPara)
{
	va_list ap;
	
	QNode *Node = InQueue ();
    if (Node == NULL)
    {
        printf ("Queue Full\r\n");
        exit (0);
    }

    (void)snprintf (Node->QBuf, sizeof(Node->QBuf), "{%X:%s:%lX}", *((DWORD*)ThrId), ThreadEntry, (ULONG)ThrPara);
    Node->ThreadId = pthread_self ();
    Node->EventId  = EventId;
    Node->Flag     = TRUE;

    DEBUG ("[TRC_thread][T:%X]%lx:%s\r\n", Node->ThreadId, EventId, Node->QBuf);

    return;   
}


void TRC_init ()
{
    char *FullInstm = getenv ("FULL_INSTRUMENTATION");
    if (FullInstm != NULL)
    {
        gFullTraceFlag = 1;
    }
    
    return;
}

void TRC_exit ()
{
    QueueSetExit ();
}

#ifdef __cplusplus
}
#endif


