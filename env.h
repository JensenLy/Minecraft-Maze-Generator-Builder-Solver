#ifndef ENV
#define ENV
#include <iostream>
#include <mcpp/mcpp.h>
class Env {
public:
//constructors/de-constructors
Env();
Env(int length, int width);
~Env();
//methods
int getLength();
int getWidth();
// int getHeight();

void setEnvElement(int, int, char);
char getEnvElement(int, int);
private:
//Fields
int length;
int width;
// int height;
char **envStructure;
};
#endif //ENV