/**
 * @file ccn/ccnd.h
 * 
 * Definitions pertaining to the CCN daemon
 *
 */
/*-
 * Copyright 2008, 2009 Palo Alto Research Center, Inc. All rights reserved.
 */

#ifndef CCN_CCND_DEFINED
#define CCN_CCND_DEFINED

#define CCN_DEFAULT_LOCAL_SOCKNAME "/tmp/.ccnd.sock"
#define CCN_LOCAL_PORT_ENVNAME "CCN_LOCAL_PORT"

#define CCN_DEFAULT_UNICAST_PORT "4485"

/* link adapters sign on by sending this greeting to ccnd */
#define CCN_EMPTY_PDU "CCN\202\000"
#define CCN_EMPTY_PDU_LENGTH 5
#endif
