#pragma once

#ifndef __POOLED_THREAD_H 
#define __POOLED_THREAD_H

#include <functional>
#include <thread>
#include <mutex>

class pooled_thread {
public:
	enum class state {
		running, idle, waiting
	};
private:
	using funcT = std::function<void(void**)>;
	void* thread_data;//memory leak is allowed actually
	int await_in_milliseconds;
	funcT exec_func;
	bool is_active;
	mutable state cur_state;
	mutable state default_state;
	std::recursive_mutex execution_locker;
	void start_thread() {
		std::thread th([this]() {
			while (is_active) {
				execution_locker.lock();
				if (cur_state == state::waiting) {
					cur_state = state::running;
					exec_func(&thread_data);
				}
				cur_state = default_state;
				execution_locker.unlock();
				std::this_thread::sleep_for(std::chrono::milliseconds(await_in_milliseconds));
			}
			});
		th.detach();
	}
public:
	pooled_thread(funcT function = [](void** ptr) {return; }, int awaiting_time = 5) :exec_func(function), await_in_milliseconds(awaiting_time), default_state(state::idle) {
		thread_data = nullptr;
		is_active = true;
		default_state = state::idle;
		start_thread();
	}
	~pooled_thread() {
		disable();
	}
	state get_state() const {
		return cur_state;
	}
	void sign_awaiting() {
		execution_locker.lock();
		cur_state = state::waiting;
		execution_locker.unlock();
	}
	void set_new_awaiting_time(int milliseconds) {
		execution_locker.lock();
		await_in_milliseconds = milliseconds;
		execution_locker.unlock();
	}
	void set_new_default_state(state def_state = state::idle) {
		execution_locker.lock();
		default_state = def_state;
		execution_locker.unlock();
	}
	void set_new_function(funcT func) {
		execution_locker.lock();
		exec_func = func;
		execution_locker.unlock();
	}
	void disable() {
		execution_locker.lock();
		is_active = false;
		execution_locker.unlock();
	}
	void** __void_ptr_accsess() {
		return &thread_data;
	}
};

#endif // __POOLED_THREAD_H 

