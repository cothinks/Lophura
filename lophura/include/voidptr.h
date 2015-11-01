#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/math/matrix.h"
#include "lophura_base/include/math/vector.h"
#include <map>

BEGIN_NS_LOPHURA()

enum type_id
{
	unkonw_type,
	mat_type,
	vec_type
};

//type mapping
template<class T>
struct type_encode
{
	enum { id = unkonw_type };
};

template<>
struct type_encode<lophura_base::matrix44>
{ 
	enum { id = mat_type , size = sizeof(lophura_base::matrix44)};
};

template<>
struct type_encode<lophura_base::vec4>
{
	enum { id = vec_type , size = sizeof(lophura_base::vec4)};
};

extern const std::map<int,size_t> g_type_mapping;

struct const_voidptr;
struct void_ptr
{
	friend struct const_void_ptr;
	friend bool assign( void_ptr lhs, const_void_ptr rhs );
	template<class T> friend T* void_ptr_cast( void_ptr& ptr);
public:
	void_ptr():
		id_(unkonw_type),
		pval_(nullptr)
	{}

	template<class T>
	void_ptr(T* ptr):
		id_(type_encode<T>::id),
		pval_(ptr)
	{}

	template<class T>
	operator T*(){
		return void_ptr_cast(*this);
	}

	void_ptr& operator = ( const void_ptr& rhs){
		id_ = rhs.id_;
		pval_ = rhs.pval_;
		return *this;
	}

	type_id get_id() const{
		return static_cast<type_id>(id_); 
	}
private:
	int		id_;
	void*	pval_;
};


struct const_void_ptr
{
	friend bool assign( void_ptr lhs, const_void_ptr rhs );
public:
	const_void_ptr(): 
		id_( unkonw_type ),
		pval_(nullptr)
	{}

	template<class T>
	const_void_ptr(const T* rhs):
		id_(type_encode<T>::id),
		pval_(rhs)
	{}

	const_void_ptr(const void_ptr& rhs):
		id_(rhs.id_),
		pval_(rhs.pval_)
	{}

	const_void_ptr(const const_void_ptr& rhs):
		id_(rhs.id_),
		pval_(rhs.pval_)
	{}

	const_void_ptr& operator = (const void_ptr& rhs){
		id_ = rhs.id_;
		pval_ = rhs.pval_;
		return *this;
	}

	const_void_ptr& operator = (const const_void_ptr& rhs){
		id_ = rhs.id_;
		pval_ = rhs.pval_;
		return *this;
	}

	type_id get_id() const{
		return static_cast<type_id>(id_);
	}
private:
	int			id_;
	const void*	pval_;
};

template<class T>
T* void_ptr_cast( const void_ptr& ptr)
{
	if ( ptr.id_ == type_encode<T>::id ){
		return static_cast<T*>(ptr.pval_);
	}
	return nullptr;
}

//the type must be standard layout
inline bool assign( void_ptr lhs, const_void_ptr rhs )
{
	if (lhs.id_ == rhs.id_){
		auto type_itor	= g_type_mapping.find(lhs.id_);
		if ( type_itor != g_type_mapping.end()){
			return  0 == memcpy_s( lhs.pval_, type_itor->second,
				rhs.pval_, type_itor->second);
		}
	}
	return false;
}
END_NS_LOPHURA()