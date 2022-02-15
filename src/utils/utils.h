#pragma once

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <stdarg.h>
#include <stdint.h>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif ///_WIN32

typedef unsigned char byte;

namespace utils{
#ifdef _WIN32
	static inline std::wstring _GetModulePath( int ){
		wchar_t tmp_path[MAX_PATH]={0};
		if( 0 == ::GetModuleFileNameW( ::GetModuleHandleW( nullptr),tmp_path , MAX_PATH )){
			return std::wstring();
		}
		std::wstring path = tmp_path;
		auto pos1 = path.find_last_of('\\');
		//auto pos2 = path.find_last_of('/' );
		path = path.substr(0, pos1);
		return path;
	}
	static inline std::string _GetModulePath( char) {
		char tmp_path[MAX_PATH]={0};
		if( 0 == ::GetModuleFileNameA( ::GetModuleHandleA( nullptr),tmp_path , MAX_PATH )){
			return std::string();
		}
		std::string path = tmp_path;
		auto pos1 = path.find_last_of('\\');
		//auto pos2 = path.find_last_of('/' );
		path = path.substr(0, pos1);
		return path;
	}
	template<typename T>
	inline T getModulePath(){
		static_assert(std::is_same<std::string,T>::value || std::is_same<std::wstring,T>::value, "this T must wstring or string" );
		return _GetModulePath( typename std::conditional<std::is_same<std::string,T>::value, char,int>::type()  );
	}
#endif ///_WIN32
	template<typename T, size_t _N>
	size_t array_size(   T ( & array)[_N] ){
		return _N;
	}
	template<typename T>
	size_t array_size( uint32_t size){
		return sizeof(T) * size;
	}

#ifdef _MSC_VER
	class Watch{
	public:
		Watch()
			:_count(0)
			
		{
			QueryPerformanceFrequency(&_freq);
			_time.QuadPart = 0;
		}
		void start(){
			_count++;
			QueryPerformanceCounter(&_begin);
		}
		
		void end(){
			 QueryPerformanceCounter(&_end);
			 _time.QuadPart += ((_end.QuadPart - _begin.QuadPart)); //// 这里的加法肯定丢失数据
		}
		void reset(){
			_count = 0;
			_time.QuadPart = 0;
		}
		size_t get_count() const{
			return _count;
		}
		double get_time() const{
			return (_time.QuadPart *1.0 / _freq.QuadPart);
		}
	private:
		LARGE_INTEGER _freq;
		size_t _count;
		LARGE_INTEGER _time;
		LARGE_INTEGER _begin;
		LARGE_INTEGER _end;

	};
#else 
	
#endif /// _MSC_VER
}

