#include "object.hpp"
struct RegObject: Object{
Object *audit;
void *call_virtfn(std::string x,void *y);
};