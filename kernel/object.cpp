#include "object.hpp"
#include <exception>
void *Object::call_virtfn(std::string x,void *y){
		return virtfns[x](this,y);
	};
template<typename T,typename U> T Object::call_virtfn(std::string x,U y){
		return *(T*)call_virtfn(x,(void*)&y);
	};
template<typename T> Object::Object(std::map<std::string, std::function<void*(Object*,void*)>> x,T* y,void *z): virtfns(x), pdata(z){
	try{
call_virtfn("__init__",y);
	}catch(std::exception e){

	}
}
Object::~Object(){
	try{
call_virtfn("__rm__",0);
	}catch(std::exception e){

	}
}