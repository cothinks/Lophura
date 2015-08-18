#pragma once

#include "lophura_base/include/math/vector_imple.h"

namespace lophura_base
{
	template<typename param_type,int col_size,int row_size>
	struct matrix;

	template<typename param_type,int col_size,int row_size>
	struct matrix_data
	{
		vector<param_type,col_size> const& get_row(int i) const
		{
			return *reinterpret_cast<vector<param_type,col_size> const*>(&data_[i][0]);
		}

		vector<param_type,row_size>  get_col(int i) const
		{
			vector<param_type,row_size> ret;
			for (int row = 0;row < row_size; ++row)
			{
				ret.data_[row] = data_[row][i];
			}

			return ret;
		}

		param_type operator[] (int index) const
		{
			assert(index<size);
			return data_[index];
		}

		param_type& operator[] (int index)
		{
			assert(index < size);
			return data_[index];
		}

		static matrix<param_type,col_size,row_size>	zero()
		{
			matrix<param_type,col_size,row_size> zero_matrix;
			for (int i = 0;i < row_size; ++i)
			{
				for (int j = 0;j < col_size; ++j)
				{
					zero_matrix.data_[i][j] = 0.0f;
				}
			}

			return zero_matrix;
		}

		static matrix<param_type,col_size,row_size>	identity()
		{
			matrix<param_type,col_size,row_size>	identity_matrix = zero();
			for (int i = 0;i < col_size; ++i)
			{
				identity_matrix.data_[i][i] = 1.0f;
			}

			return identity_matrix;
		}

		param_type	data_[row_size][col_size];
	};

	template<typename param_type,int col_size,int row_size>
	struct matrix {};

	template<typename param_type>
	struct matrix<param_type,4,4> : matrix_data<param_type,4,4>
	{
		matrix(){}
		matrix(
			param_type _11, param_type _12, param_type _13, param_type _14,
			param_type _21, param_type _22, param_type _23, param_type _24,
			param_type _31, param_type _32, param_type _33, param_type _34,
			param_type _41, param_type _42, param_type _43, param_type _44
			)
		{
			data_[0][0] = _11;
			data_[0][1] = _12;
			data_[0][2] = _13;
			data_[0][3] = _14;

			data_[1][0] = _21;
			data_[1][1] = _22;
			data_[1][2] = _23;
			data_[1][3] = _24;

			data_[2][0] = _31;
			data_[2][1] = _32;
			data_[2][2] = _33;
			data_[2][3] = _34;

			data_[3][0] = _41;
			data_[3][1] = _42;
			data_[3][2] = _43;
			data_[3][3] = _44;
		}
	};
};