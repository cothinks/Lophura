#pragma once

#include <assert.h>

namespace lophura_base
{
	template<typename T,int size>
	struct VectorData
	{
		T operator [] (int index) const
		{
			assert(index < size);
			return data_[index];
		}

		T& operator [] (int index)
		{
			assert(index < size);
			return data_[index];
		}

		void Normalize()
		{
			T  sum = 0.0f;
			for (int i = 0;i < size; ++i){
				sum += data_[i]*data_[i];
			}

			sum = sqrt(sum);
			for (int i = 0;i <size; ++i){
				data_[i] /= sum;
			}
		}

		T data_[size];
	};

	template<typename T,int size>
	struct Vector {};

	template<typename T>
	struct Vector<T,2> : public VectorData<T,2>
	{
		Vector(){}
		explicit Vector(T const& v1,T const& v2)
		{
			data_[0] = v1;
			data_[1] = v2;
		}

		T x() const
		{
			return data_[0];
		}

		T y() const
		{
			return data_[1];
		}
	};

	template<typename T>
	struct Vector<T,3> :public VectorData<T,3>
	{
		Vector(){}
		explicit Vector(T const& v1,T const& v2,T const& v3)
		{
			data_[0] = v1;
			data_[1] = v2;
			data_[2] = v3;
		}

		T x() const{
			return data_[0];
		}

		T y() const{
			return data_[1];
		}

		T z() const{
			return data_[2];
		}
	};

	template<typename T>
	struct Vector<T,4>: public VectorData<T,4>
	{
		Vector(){}
		explicit Vector(T const& v1,T const& v2,T const& v3,T const& v4)
		{
			data_[0] = v1;
			data_[1] = v2;
			data_[2] = v3;
			data_[3] = v4;
		}

		T x() const{
			return data_[0];
		}

		T y() const{
			return data_[1];
		}

		T z() const{
			return data_[2];
		}

		T w() const{
			return data_[3];
		}

		Vector<T,2> xy(){
			return Vector<T,2>(x(),y());
		}
	};

	template<typename T,int size>
	Vector<T,size> operator - (Vector<T,size> const& lhs,Vector<T,size> const& rhs)
	{
		Vector<T,size> ret;
		for (int i = 0;i < size; ++i)
		{
			ret.data_[i] = lhs.data_[i] - rhs.data_[i];
		}

		return ret;
	}

	template<typename T,int size>
	Vector<T,size> operator * (Vector<T,size> const& lhs,T s)
	{
		Vector<T,size> ret;
		for (int i = 0; i < size; i++)
		{
			ret.data_[i] = lhs.data_[i] * s;
		}

		return ret;
	}
};