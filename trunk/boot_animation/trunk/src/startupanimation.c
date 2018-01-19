#include"stdio.h"
#include <unistd.h>
#include <stdlib.h>

int main ( void )
{
  int i = 1;
  char cmd[255];
  //printf ( "Start animation.\n" );
  system ( "display_image -zorder=1 -noinit=1 -display=1 -size=1200x1920 -file=/extra/Hinge_Apps/boot_animation/images/Splash_0.png &" );
  for ( i = 1; i <= 17; i++ ) {
    sprintf ( cmd, "display_image -zorder=1 -noinit=1 -display=1 -pos=0,735 -size=1200x450 -file=/extra/Hinge_Apps/boot_animation/images/Splash_%d.png &", i );
    system ( cmd );
    usleep ( 90000 );
  }

  system ( "slay -f display_image" );
  system ( "display_image -zorder=1 -noinit=1 -display=1 -size=1200x1920 -file=/extra/Hinge_Apps/boot_animation/images/Splash_41.png &" );

  return 0;
}
