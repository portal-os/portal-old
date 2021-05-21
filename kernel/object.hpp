#include <functional>
#include <map>
#include <memory>
#include <string>
#include <hash_map>
struct Object{
	std::map<std::string, std::function<void*(Object*,void*)>> virtfns;
	std::map<std::string,std::shared_ptr<Object>> data;
	void *pdata;
	virtual void *call_virtfn(std::string x,void *y);
	template<typename T,typename U> T call_virtfn(std::string x,U y);
	template<typename T> Object(std::map<std::string, std::function<void*(Object*,void*)>>,T*,void*);
	~Object();
};