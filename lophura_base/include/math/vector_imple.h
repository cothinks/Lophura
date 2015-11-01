#pragma once

#include <assert.h>

namespace lophura_base
{
	template<typename param_type,int size>
	struct vector_data
	{
		param_type operator [] (int index) const
		{
			assert(index < size);
			return data_[index];
		}

		param_type& operator [] (int index)
		{
			assert(index < size);
			return data_[index];
		}
		
		void normalize()
		{
			param_type  sum = 0.0f;
			for (int i = 0;i < size; ++i)
			{
				sum += data_[i]*data_[i];
			}

			sum = sqrt(sum);
			for (int i = 0;i <size; ++i)
			{
				data_[i] /= sum;
			}
		}

		param_type data_[size];
	};

	template<typename param_type,int size>
	struct vector {};

	template<typename param_type>
	struct vector<param_type,2> : public vector_data<param_type,2>
	{
		vector(){}
		explicit vector(param_type const& v1,param_type const& v2)
		{
			data_[0] = v1;
			data_[1] = v2;
		}

		param_type x() const
		{
			return data_[0];
		}

		param_type y() const
		{
			return data_[1];
		}
	};

	template<typename param_type>
	struct vector<param_type,3> :public vector_data<param_type,3>
	{
		vector(){}
		explicit vector(param_type const& v1,param_type const& v2,param_type const& v3)
		{
			data_[0] = v1;
			data_[1] = v2;
			data_[2] = v3;
		}

		param_type x() const
		{
			return data_[0];
		}

		param_type y() const
		{
			return data_[1];
		}

		param_type z() const
		{
			return data_[2];
		}
	};

	template<typename param_type>
	struct vector<param_type,4>: public vector_data<param_type,4>
	{
		vector(){}
		explicit vector(param_type const& v1,param_type const& v2,param_type const& v3,param_type const& v4)
		{
			data_[0] = v1;
			data_[1] = v2;
			data_[2] = v3;
			data_[3] = v4;
		}

		param_type x() const
		{
			return data_[0];
		}

		param_type y() const
		{
			return data_[1];
		}

		param_type z() const
		{
			return data_[2];
		}

		param_type w() const
		{
			return data_[3];
		}

		vector<param_type,2> xy()
		{
			return vector<param_type,2>(x(),y());
		}

		static vector<param_type,4> zero()
		{
			return vector<param_type,4>(0,0,0,0);
		}
	};

	template<typename param_type,int size>
	vector<param_type,size> operator - (vector<param_type,size> const& lhs,vector<param_type,size> const& rhs)
	{
		vector<param_type,size> ret;

		for (int i = 0;i < size; ++i)
		{
			ret.data_[i] = lhs.data_[i] - rhs.data_[i];
		}

		return ret;
	}

	template<typename param_type,int size>
	vector<param_type,size> operator * (vector<param_type,size> const& lhs,param_type s)
	{
		vector<param_type,size> ret;

		for (int i = 0; i < size; i++)
		{
			ret.data_[i] = lhs.data_[i] * s;
		}

		return ret;
	}
};