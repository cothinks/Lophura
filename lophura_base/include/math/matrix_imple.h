#pragma once

#include "lophura_base/include/math/vector_imple.h"

namespace lophura_base
{
	template<typename T,int col_size,int row_size>
	struct Matrix;

	template<typename T,int col_size,int row_size>
	struct MatrixData
	{
		Vector<T,col_size> const& GetRow(int i) const
		{
			return *reinterpret_cast<Vector<T,col_size> const*>(&data_[i][0]);
		}

		Vector<T,row_size>  GetCol(int i) const
		{
			Vector<T,row_size> ret;
			for (int row = 0;row < row_size; ++row)
			{
				ret.data_[row] = data_[row][i];
			}

			return ret;
		}

		T operator[] (int index) const
		{
			assert(index<size);
			return data_[index];
		}

		T& operator[] (int index)
		{
			assert(index < size);
			return data_[index];
		}

		static Matrix<T,col_size,row_size>	Zero()
		{
			Matrix<T,col_size,row_size> zero_matrix;
			for (int i = 0;i < row_size; ++i)
			{
				for (int j = 0;j < col_size; ++j)
				{
					zero_matrix.data_[i][j] = 0.0f;
				}
			}

			return zero_matrix;
		}

		static Matrix<T,col_size,row_size>	Identity()
		{
			Matrix<T,col_size,row_size>	identity_matrix = Zero();
			for (int i = 0;i < col_size; ++i)
			{
				identity_matrix.data_[i][i] = 1.0f;
			}

			return identity_matrix;
		}

		T	data_[row_size][col_size];
	};

	template<typename T,int col_size,int row_size>
	struct Matrix {};

	template<typename T>
	struct Matrix<T,4,4> : MatrixData<T,4,4>
	{
		Matrix(){}
		Matrix(
			T _11, T _12, T _13, T _14,
			T _21, T _22, T _23, T _24,
			T _31, T _32, T _33, T _34,
			T _41, T _42, T _43, T _44
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