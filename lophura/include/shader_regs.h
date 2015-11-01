#pragma once

#include "lophura/include/lophura_forward.h"
#include "lophura_base/include/math/vector.h"
#include "lophura/include/lophura_capacity.h"

#include <array>

BEGIN_NS_LOPHURA()

class vs_input
{
public:
	vs_input()
	{}

	lophura_base::vec4& attribute(size_t index)
	{
		return attributes_[index];
	}

	lophura_base::vec4 const& attribute(size_t index) const
	{
		return attributes_[index];
	}
private:
	typedef std::tr1::array<
		lophura_base::vec4, MAX_VS_INPUT_ATTRS> attribute_array;
	attribute_array attributes_;
};

class vs_output
{
public:
	enum attrib_modifier_type
	{
		am_linear = 1UL << 0
	};
public:
	vs_output()
	{}

	lophura_base::vec4& position()
	{
		return registers_[0];
	}

	lophura_base::vec4 const& position() const
	{
		return registers_[0];
	}

	lophura_base::vec4* raw_data()
	{
		return registers_.data();
	}

	lophura_base::vec4 const* raw_data() const
	{
		return registers_.data();
	}

	lophura_base::vec4& attribute(size_t index)
	{
		return registers_[index];
	}

	lophura_base::vec4 const& attribute(size_t index) const
	{
		return registers_[index];
	}
private:
	typedef std::tr1::array<
		lophura_base::vec4,MAX_VS_OUTPUT_ATTRS> register_array;
	register_array registers_;

	vs_output(vs_output const& rhs);
	//vs_output& operator=(vs_output const& rhs);
};

END_NS_LOPHURA()