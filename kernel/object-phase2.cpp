#include "object.hpp"
#include <functional>
#include <memory>
#include <utility>
void* s2p(void *a,std::string b){
	return (void*)new std::pair<void*,std::string>(a,b);
}
void s2p_free(void *a){
	delete (std::pair<void*,std::string>*)a;
}
void *init_phase2(Object *a,void *b){
	a->data["__fns__"]=std::shared_ptr<Object>((Object*)a->call_virtfn("__fns__",b));
	a->virtfns["call"]=[&](Object *aa,void *bb) -> void*{
		std::pair<void*, std::string> p = *(std::pair<void*, std::string>*)bb;
		return a->data["__fns__"]->data[p.second]->virtfns["__fn__"](&*a->data["__fns__"]->data[p.second],p.first);
	};
	a->virtfns["inject"]=[&](Object *aa,void *bb) -> void*{
		std::pair<void*, std::string> p = *(std::pair<void*, std::string>*)bb;
		a->data["__fns__"]->data[p.second]=std::make_shared<Object>(std::map<std::string, std::function<void*(Object*,void*)>>({{"__fn__",[&](Object *c,void *d) -> void*{
			return (*(std::function<void*(Object*,void*)>*)p.first)(c,d);
		}}}),(void*)nullptr,(void*)nullptr);
		return 0;
	};
	auto is2p = s2p((void*)&a->virtfns["inject"],"inject");
	a->call_virtfn("inject",is2p);
	s2p_free(is2p);

	is2p = s2p((void*)&a->virtfns["call"],"call");
	a->call_virtfn("inject",is2p);
	s2p_free(is2p);
	
	return 0;
}
std::map<std::string, std::function<void*(Object*,void*)>> phase2_Object = {{"__init__",init_phase2}};