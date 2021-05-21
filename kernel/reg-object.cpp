#include "reg-object.hpp"
#include <string>
#include <utility>
void *RegObject::call_virtfn(std::string x,void *y){
	if(!audit->call_virtfn<bool>("audit",std::pair<std::string, void*>(x,y)))return 0;
	return Object::call_virtfn(x,y);
}