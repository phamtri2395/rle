#ifndef _RLE_H_
#define _RLE_H_

#define null 0
#define byte unsigned char

byte *compress_rle(const byte*, long, long&);
byte *decompress_rle(const byte*, long, long&);

#endif
