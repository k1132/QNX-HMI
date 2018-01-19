/**
* \file 
* Socket for reading and writing bytes via TCP.
* 
* Copyright 2008-2014 by Rightware. All rights reserved.
*/
#ifndef KZS_TCP_SOCKET_H
#define KZS_TCP_SOCKET_H


#include <system/kzs_types.h>
#include <system/debug/kzs_error.h>
#include <system/kzs_header.h>


KZ_HEADER_BEGIN


/**
 * \struct KzsTCPSocket
 * TCP socket.
 */
struct KzsTCPSocket;


/**
 * Function type for checking the connection status of custom ipc.
 * Implementor of the callback function should also check the connectionResult for error cases.
 */
typedef kzsError (*kzsTCPSocketConnectionCallback)(const void* userData, kzsError connectionResult);


/**
 * Creates a new TCP server socket connection using specified address and port. This function returns immediately.
 * The server starts listening for a connection in a new thread and notifies with connectionCallback when the socket is connected.
 */
kzsError kzsTCPSocketCreateServer(kzString inetAddress, kzUint port, 
                                  const void* userData, kzsTCPSocketConnectionCallback connectionCallback, 
                                  struct KzsTCPSocket** out_tcpSocket);

/**
 * Creates a new TCP client socket connection using specified address and port. This function returns immediately.
 * The client starts connecting in a new thread and notifies with connectionCallback when the socket is connected.
 */
kzsError kzsTCPSocketCreateClient(kzString inetAddress, kzUint port, 
                                  const void* userData, kzsTCPSocketConnectionCallback connectionCallback,
                                  struct KzsTCPSocket** out_tcpSocket);

/** Deletes and does clean-up for tcp socket. */
kzsError kzsTCPSocketDelete(struct KzsTCPSocket* tcpSocket);

/** 
 * Reads bytes from TCP Socket.
 * The requested byte count is given as parameter and the actual number of bytes read is returned.
 * Negative number is returned, if no data is available.
*/
kzsError kzsTCPSocketReadBytes(const struct KzsTCPSocket* tcpSocket, kzUint byteCount, kzUint* out_bytesReadCount, kzByte* out_bytes);

/**
 * Writes bytes for TCP Socket.
 * The number of bytes to be written is given as parameter and the actual number of bytes written is returned.
 * Negative number is returned, if no bytes can be written.
 */
kzsError kzsTCPSocketWriteBytes(const struct KzsTCPSocket* tcpSocket, kzUint byteCount, const kzByte* bytes, kzUint* out_bytesWrittenCount);

/** Returns if TCP socket is connected. */
kzBool kzsTCPSocketIsConnected(const struct KzsTCPSocket* tcpSocket);


KZ_HEADER_END


#endif
