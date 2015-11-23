#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/platform/typedefs.h"
#include "lophura/include/shader_regs.h"
#include "lophura/include/voidptr.h"

#include <map>
#include <unordered_map>
#include <string>
#include <assert.h>

BEGIN_NS_LOPHURA()

enum system_values
{
	sv_none,

	sv_position,
	sv_texcoord,
	sv_normal,

	sv_customized
};

class semantic_value
{
public:
	static std::string lower_copy( std::string const& name)
	{
		std::string ret(name);
		for ( size_t i = 0; i < ret.size(); ++i)
		{
			if ( 'A' <= ret[i] && ret[i] <= 'Z')
			{
				ret[i] = ret[i] - ('A' - 'a');
			}
		}
		return ret;
	}

	semantic_value():sv_(sv_none),index_(0){}

	explicit semantic_value( std::string const& name, uint32_t index)
	{
		assert(!name.empty());

		std::string lower_name = lower_copy(name);

		if ("position" == lower_name){
			sv_ = sv_position;
		}else if ( lower_name == "normal" ){
			sv_ = sv_normal;
		} else if ( lower_name == "texcoord" ){
			sv_ = sv_texcoord;
		}

		index_ = index;
	}

	explicit semantic_value( system_values sv, uint32_t index)
	{
		assert( sv_none <= sv && sv < sv_customized);

		sv_		= sv;
		index_	= index;
	}

	std::string const& get_name() const{
		return name_;
	}

	system_values get_system_value() const{
		return sv_;
	}

	uint32_t get_index() const{
		return index_;
	}

	bool operator < ( semantic_value const& rhs) const{
		return sv_ < rhs.sv_ || name_ < rhs.name_ || index_ < rhs.index_;
	}

	bool operator == ( semantic_value const& rhs) const{
		return is_same_sv(rhs) && index_ == rhs.index_;
	}

	bool operator == ( system_values rhs) const{
		return sv_ == rhs && index_ == 0;
	}

	template <typename T>
	bool operator != ( T const& v ) const{
		return !( *this == v );
	}

	bool valid() const
	{
		return sv_ != sv_none || !name_.empty();
	}
private:
	std::string		name_;
	system_values	sv_;
	uint32_t		index_;

	bool is_same_sv( semantic_value const& rhs ) const{
		if( sv_ != rhs.sv_ ) return false;
		if( sv_ == sv_customized ) return rhs.name_ == name_;
		return true;
	}
};

class cpp_shader
{
public:
	virtual ~cpp_shader(){}

	virtual bool set_constant( const lophura_base::kstring& vaname, const_void_ptr pval) = 0;
};

class cpp_shader_imple : public cpp_shader
{
public:
	
	virtual bool set_constant( const lophura_base::kstring& vaname, const_void_ptr pval){
		auto var_it = varmap_.find(vaname);
		if ( var_it == varmap_.end() ){
			return false;
		}

		return assign( var_it->second, pval);
	}

	template< class T >
	void declare_constant(const lophura_base::kstring varname, T& var)
	{
		varmap_[varname] = &var;
	}

	std::map<semantic_value, size_t> const& get_register_map();

	void bind_semantic( char const* name, size_t semantic_index, size_t register_index );
	void bind_semantic( semantic_value const& s, size_t register_index );
protected:
	typedef std::map<lophura_base::kstring, void_ptr>
		variable_map;
#pragma message("struct op")
	typedef std::map<semantic_value, size_t>
		register_map;

	variable_map	varmap_;
	register_map	regmap_;
};

class cpp_vertex_shader : public cpp_shader_imple
{
public:
	void execute(const vs_input& in, vs_output& out);
	virtual void shader_prog(const vs_input& in, vs_output& out) = 0;
	virtual uint32_t num_output_attributes() const = 0;
	virtual uint32_t output_attribute_modifiers(uint32_t index) const = 0;
};

class cpp_pixel_shader : public cpp_shader_imple
{
public:
	void execute(const vs_output& in, ps_output& out);
	virtual void shader_prog(const vs_output& in, ps_output& out) = 0;
};

END_NS_LOPHURA()