#pragma once

namespace ADT{
	template<bool>
	struct enable;
	template<>
	struct<true>{};
	
	template<typename ... _Args>
	class flags;
	template<typename _H, typename ..._Args>
	class flags : public enable<std::is_enum<_H>::value> , public flags_impl<0,_H, _Args...> ){
		bool is_set( _H t){
			return __is_set<
			
		}
		
	};
	
	
	template<size_t N,typename _H, typename ... _Args>
	class flags_impl : public flags_impl<N + sizeof(_H), _Args...>{
		bool is_set( _H t ){
			return __is_set( N, _H value );	
		}
		
	};
	
	template<size_t N>
	class flags_impl{
	protected:
		bool __is_set( int32_t offset, _H t ){
			
			
		}
	private:
		std::bit<N> m_bits;
	};
}