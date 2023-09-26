# Sockets
## Procedure in Client-Server Communication
- Socket: Create a new communication
- Bind: Attach a local address to a socket
- Listen: Announce willingness to accept connections
- Accept: Block caller until a connection request arrives
- Connect: Actively attempt to establish a connection
- Send: Send some data over a connection
- Receive: Receive some data over a connection
- Close: Release the connection


![socket_state_diagram](https://github.com/NULL-Term1nat0r/webserv/assets/96915676/445fdf4a-2b55-4606-a227-6f29d9f0eacd)


## Datagram Socket Operations
This section describes how to use communication styles that don't use connections (styles SOCK_DGRAM and SOCK_RDM). Using these styles, you group data into packets and each packet is an independent communication. You specify the destination for each packet individually.
The listen and accept functions are not allowed for sockets using connectionless communication styles.
