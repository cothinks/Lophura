#include "lophura/include/shader.h"

using namespace std;

BEGIN_NS_LOPHURA()

void cpp_shader_imple::bind_semantic( char const* name, size_t semantic_index, size_t register_index )
{
	bind_semantic( semantic_value(name,static_cast<uint32_t>(semantic_index)), register_index);
}

void cpp_shader_imple::bind_semantic( semantic_value const& s, size_t register_index )
{
	regmap_.insert( make_pair(s,register_index));
}

std::map<semantic_value, size_t> const& cpp_shader_imple::get_register_map()
{
	return regmap_;
}

void cpp_vertex_shader::execute(const vs_input& in, vs_output& out){
	shader_prog(in, out);
}

END_NS_LOPHURA()