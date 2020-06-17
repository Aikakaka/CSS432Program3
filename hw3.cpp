#include "Socket.h"
#include <stdlib.h>

using namespace std;

void server( ); 
void client( char ipName[] );
void usage( char progName[] );

Socket *sock;

int main( int argc, char* argv[] ) {
  if ( argc > 1 ) {
    sock = new Socket( atoi( argv[1] ) );
    if ( argc == 2 )
      server( );
    else if ( argc == 3 )
      client( argv[2] );
  }
  else {
    usage( argv[0] );
    return -1;
  }
  return 0;
}

void server( ) {

  // Get a server sd
  int serverSd = sock->getServerSocket( );

  // Exchange data
  char message[1500];

  // data size: 10B, 1450B
  // read from client
  read( serverSd, message, 10 );
  //send to client
  write( serverSd, message, 10 );
  //send FIN and shut off transmissions
  shutdown(serverSd, SHUT_WR);
  // read from client
  read( serverSd, message, 1450);

}

void client( char ipName[] ) {

  // Get a client sd
  int clientSd = sock->getClientSocket( ipName );

  // Exchange data
  char message[1500];

  // senging data size: 10B, 1450B
  // send to server
  write( clientSd, message, 10 );
  // read from server
  read( clientSd, message, 10 );
  // send to sender
  write( clientSd, message, 1450 );

  // Close socket to send FIN.
  close( clientSd );
}

void usage( char progName[] ) {
  cerr << "usage:" << endl;
  cerr << "server invocation: " << progName << " ipPort" << endl;
  cerr << "client invocation: " << progName << " ipPort ipName" << endl;
}
