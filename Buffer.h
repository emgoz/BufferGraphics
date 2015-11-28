/*-------------------------------------------------------------------------------------------------
//    *** Change Log / Version history ***
//
// 0.1 -  A basic Graphics library for buffers,
//        made to use it with any low res (up to 256 x 256 pix) monochrome LCD
//        The LCD must have a width which is divisible by 8 and
//        the data has to be stored byte-wise (1 bit = 1 pixel) starting at the top left.
//        For further information on how to use the functions, read the Documentation.pdf
//        Made by Marvin G. aka MGOS  / Apr 28 2013
//        request, bug reports and qustions to: marv.mgos@gmail.com
//-----------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------
//        You are allowed to copy, distribute or modify the source code of this library.
//        Any modification you make should be added to the change log / version history
//        in this document and at the top of each source file, including the author,
//        the date and all changes made.
//
//        Release into public domain.
//-----------------------------------------------------------------------------------------------*/
#ifndef BUFFER_h
#define BUFFER_h

#include "Arduino.h"
#include "inttypes.h"


//Drawing Modes
#define OFF     0
#define CLEAR   0
#define ON      1
#define FILLED  1
#define XOR     2
#define INVERT  2
#define OR      3
#define AND     4


class Buffer{
public:
  Buffer(byte * RAM_area, uint16_t pixHor, uint16_t pixVer);       //Constructor
  //Control
  uint16_t getWidth(void);               //Returns size of buffer
  uint16_t getHeight(void);              //Returns size of buffer
  byte* ptr(void);                       //Returns pointer to graphics area
  byte* ptr(byte* new_pointer);          //Changes pointer to another Ram area

  //Buffer manipulation
  byte* overwrite(Buffer other_buffer);
  byte* overwrite(byte* other_buffer);    //Copies another buffer (must be same size!) to this buffer and overwrites it.
  byte* overwrite(const byte* picture);
  byte* overlay(Buffer other_buffer, byte mode);
  byte* overlay(byte* other_buffer, byte mode);   //Puts another on top of this buffer. modes availlable are: OR / AND / XOR
  byte* overlay(const byte* picture, byte mode);
  byte* invert(void);                     //Inverts the colors
  byte* clear(void);                      //Clears the screen
  byte* fill(byte n);                     //fills every location with specified byte.


  void scrollUp(int x, int y, int a, int b);      //Scrolls the content of the given area up one pixel
  void scrollDown(int x, int y, int a, int b);    //Scrolls the content of the given area down one pixel
  void scrollLeft(int x, int y, int a, int b);    //Scrolls the content of the given area left one pixel
  void scrollRight(int x, int y, int a, int b);   //Scrolls the content of the given area right one pixel
  byte* scrollUp(int n);                 //Same as the above, but applies on whole buffer and number of pixels to scroll can be specified
  byte* scrollDown(int n);
  byte* scrollLeft(int n);               // |n| <= 8
  byte* scrollRight(int n);


  void flipV(int x, int y, int a, int b);  //Flips the given area vertically
  void flipH(int x, int y, int a, int b);  //Flips the given area horizontally
  void rotateR(int x, int y, int a);       //Rotates the given square clockwise
  void rotateL(int x, int y, int a);       //Rotates the given square counter clockwise
  byte * flipV(void);       //Same as the above, but applies on whole buffer
  byte * flipH(void);
  byte * rotateR(void);
  byte * rotateL(void);

  //Drawing
  void fillRect(int x, int y, int a, int b, byte mode);  //Draws a filled rectangle at top left x|y a pixels wide and b pixels high
                                         //Modes available: ON=FILLED / OFF=CLEAR / XOR=INVERT
  void rect(int x, int y, int a, int b, byte mode);  //Draws a rectangular frame at top left x|y a pixels wide and b pixels high
                                         //line styles available: ON=FILLED / OFF=CLEAR / XOR=INVERT
  void line(int x1,int y1, int x2, int y2, byte mode);   //Draws a line from x1|y1 to x2|y2
                                         //line styles available: ON=FILLED / OFF=CLEAR / XOR=INVERT
  void lineAcross(int x,int y, int w, byte mode);   //Draws a horizontal, w pixels long line from x|y to the right.
                                         //line styles available: ON=FILLED / OFF=CLEAR / XOR=INVERT
  void lineDown(int x,int y, int h, byte mode);    //Draws a vertical, h pixels long line from x|y to the bottom.
                                         //line styles available: ON=FILLED / OFF=CLEAR / XOR=INVERT
  void circle(int cx, int cy, int radius, byte mode);     //Draws a circle with center cx|cy and given radius
                                         //line styles available: ON=FILLED / OFF=CLEAR / XOR=INVERT
  void fillCircle(int cx, int cy, int radius, byte mode);     //Draws a filled circle with center cx|cy and given radius

  void quad(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, byte mode);
  void tri(int x0, int y0, int x1, int y1, int x2, int y2, byte mode);

  //Pixel access
  void setPixel(int x, int y, byte mode);  //Sets the state of the pixel x|y. Modes/Colors available: ON=FILLED / OFF=CLEAR / XOR=INVERT
  bool getPixel(int x, int y);           //Returns whether a pixel is set (1) or not (0).

  //Bitmaps
  void bitmap(int x, int y, uint16_t a, uint16_t b, byte* pic, byte mode);  //Draws a*b bitmap at top left x,y; Modes available OR=FILLED=ON / XOR=INVERT / OFF=CLEAR (deletes background)
  void bitmap(int x, int y, uint16_t a, uint16_t b, const byte* pic, byte mode);
  void bitmap(int x, int y, Buffer pic_buffer, byte mode);  //Same as first, but takes a buffer as a bitmap

  byte* getBitmap(int x, int y, uint16_t a, uint16_t b, byte* buff); //Takes a screenshoot of the given area and stores it in another buffer. "Bitmap backwards"
  byte* getBitmap(int x, int y, Buffer buff2); //Same as above, but screenshot is as large as the buffer given.

private:
  byte * array;         //pointer to buffer array
  uint16_t size;	    //#Bytes the buffer holds (Width/8 * Height)
  uint16_t width;
  uint16_t height;
  byte columns;         //#Columns the buffer has (Width/8)
};





#endif // BUFFER_h
