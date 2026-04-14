#include "box.h"
Box::Box() {
 _len=10;
 _width=10;
 _height =10;
 volume= _len * _width * _height;
}
Box::Box(int a){
 _len=a;
 _width=a;
 _height =a;
 volume= _len * _width * _height;
}

Box::Box(int l, int w, int h){
 _len=l;
 _width=w;
 _height =h;
 volume= _len * _width * _height;
}
void writeToFile(const char* fileName, const struct Box& box) { 
FILE* file;
file = fopen (fileName,"w");
if (!file) {
 return;
}
fprintf(file, "%d %d %d %x\n", box._len, box._width, box._height, box._color);
fclose(file);
}


void readFromFile(const char* fileName, struct Box& box) {

FILE* file;
file = fopen (fileName,"r");
if (!file) {
 return;
}
fscanf (file,"%d %d %d %x", &box._len, &box._width, &box._height, &box._color );
box.volume = box._len * box._width * box._height;
}
std::ostream& operator<<(std::ostream& file, const Box& box) {
   file  << "len = " << box._len
       << ", width = " << box._width
       << ", height = " << box._height
       << ", volume = " << box.volume <<'\n';
    return file;
}
