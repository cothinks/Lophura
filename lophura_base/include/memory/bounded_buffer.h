#pragma once

#include <deque>
#include <mutex>
#include <condition_variable>

namespace lophura_base
{
	template<typename T>
	class bounded_buffer
	{
	public:

		void	push_front(T const& item)
		{
			queue_lock_.lock();
			queues_.push_front(item);
			queue_lock_.unlock();

			not_empty_.notify_one();
		}

		void	pop_back(T& item)
		{
			std::lock_guard<std::mutex> guard(queue_lock_);
			if(!queues_.empty()){
				item = queues_.back();
				queues_.pop_back();
			}
		}
	private:
		//bool	is_not_full() const {}
		bool	is_not_empty() const {}
	private:
		std::deque<T>				queues_;

		std::mutex					queue_lock_;
		std::condition_variable		not_empty_;
		std::condition_variable		not_full_;
	};
};