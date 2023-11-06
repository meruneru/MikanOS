#include <cstdio>
#include <cstddef>
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "font.hpp"

void* operator new(size_t size, void* buf){
  return buf;
}

void operator delete(void* obj){
}

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

extern "C" void KernelMain(const struct FrameBufferConfig& frame_buffer_config) {
  switch(frame_buffer_config.pixel_format){
    case kPixelRGBResv8BitPerColor:
     pixel_writer = new(pixel_writer_buf) RGBResv8BitPerColorPixelWriter{frame_buffer_config};
     break;
    case kPixelBGRResv8BitPerColor:
     pixel_writer = new(pixel_writer_buf) BGRResv8BitPerColorPixelWriter{frame_buffer_config};
     break;
  }
  for(int x=0; x<frame_buffer_config.horizontal_resolution; x++){
    for(int y=0; y<frame_buffer_config.vertical_resolution; y++){
      pixel_writer->Write(x, y, {255, 255, 255});
    }
  }

  for(int x=0; x<200; x++){
    for(int y=0; y<100; y++){
      pixel_writer->Write(100+x, 100+y, {0, 255, 0});
    }
  }


  WriteStrings(*pixel_writer, 0, 0, "Hello, World!", {0,0,255});

  char buf[128];
  sprintf(buf, "1+2 = %d", 1+2);
  WriteStrings(*pixel_writer, 0, 20, buf, {0,0,0});

  int posX=0;
  int line=0;
  for(unsigned char c=0x01; c<=0x7E;c++, posX++){
      if(posX%20==0){
        line++;
        posX=0;
      }
      WriteAscii(*pixel_writer, 50+8*posX, 50+line*20, c, {0,0,0});
  }

  while(1) __asm__("hlt");
}