#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

  struct complex{
    double re;
    double im;
  };
  struct qtype{
    int x1;
    int x2;
    int y1;
    int y2;
  };
  int pix_calcul (struct complex d){
    struct complex z;
    z.re=0.0;
    z.im=0.0;
    int counter=0, limit=255;
    double square_z_length=0.0, tmp=0.0;
    
    do{
      tmp=z.re*z.re-z.im*z.im+d.re;
      z.im=2*z.re*z.im+d.im;
      z.re=tmp;
      square_z_length=z.re*z.re+z.im*z.im;
      counter++;
    }while((square_z_length<=4.0)&&(counter<limit));
    return counter;
  }


int main(int argc, char *argv[])
{
    const char filename[9]={"apfel.bmp"};
    int width=800;
    int height=700;
    int size=3*width*height;
    char rgb[size];
    struct qtype c;
    c.x1=0;
    c.x2=width;
    c.y1=0;
    c.y2=height;
    int pixcolor=0;
    int y=0;
    int x=0;
    int i=0;
    double min_cx=-2.2;
    double min_cy=-1.4;
    double punkt_abstand=0.004;
    double cx,cy;
    for (y=c.y1;y<c.y2;y++){
      cy=min_cy+y*punkt_abstand;
      for (x=c.x1;(x<width)&&(x<c.x2||y!=c.y2);x++){
        cx=min_cx+x*punkt_abstand;
        struct complex d;
        d.re=cx;
        d.im=cy;
        pixcolor=pix_calcul(d);
        if (pixcolor >= 255/2){
          rgb[i] = 0;
          rgb[i+1] = 0;
          rgb[i+2] = 0;
        }else
        {
          rgb[i]=255-(pixcolor%2*125);
          rgb[i+1]=255-(pixcolor%7*55);
          rgb[i+2]=255-(pixcolor%3*85);
        }
        i=i+3;
      }
    }
    write_bmp(filename, width, height, rgb);
    return 0;
}
