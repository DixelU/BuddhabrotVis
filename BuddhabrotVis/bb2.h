#pragma once
#include <thread>
#include <complex>
#include <mutex>
#include <vector>
#include "field_vis.h"
#include "weird_hacks.h"
#include "consts.h"

#include "pooled_thread.h"

namespace bb {
	dsfield iter_counts, iter_counts_buffer;
	field zero;
	float size = 4., max_iters = 200, amount = 10., progressrate = 10;
	const int64_t fsize = 600;
	bool iter_pause = false;
	bool iter_break = false;
	std::recursive_mutex global_pause_lock;
	std::mutex local_lock;
	std::vector<pooled_thread*> threads;
	int step_counter = 0;
	int threads_count = max(std::thread::hardware_concurrency() - 2, 1u);
	inline std::pair<int64_t, int64_t> find_cell(const std::complex<double>& a) {
		auto t = (a + std::complex<double>(2, 2)) * (fsize / size * 1.);
		return { t.real(),t.imag() };
	}
	void create_iter_threads() {
		iter_pause = false;
		local_lock.lock();
		iter_counts.fd = iter_counts_buffer.fd = zero;
		for (int thid = 0; thid < threads_count; thid++) {
			threads.push_back(new pooled_thread());
			threads.back()->set_new_function([](void** void_ptr) {
				global_pause_lock.lock();
				for (int i = 0; i < fsize * amount; i++) {
					std::complex<double> c = { RANDFLOAT(size / 2.),RANDFLOAT(size / 2.) }, z = 0;
					for (int j = 0; j < max_iters; j++) {
						z = z * z + c;
						if (z.real() * z.real() + z.imag() * z.imag() > 4.)break;
						auto t = find_cell(z);
						iter_counts_buffer.at(t.first, t.second) += 1;
					}
				}
				printf("abx %i\n", step_counter);
				global_pause_lock.unlock();
				});
			threads.back()->sign_awaiting();
		}
		threads.push_back(new pooled_thread());
		threads.back()->set_new_awaiting_time(10);
		threads.back()->set_new_default_state(pooled_thread::state::waiting);
		threads.back()->set_new_function([](void** ptr) {
			for (auto ptr : threads)
				if (ptr != threads.back() && ptr->get_state() != pooled_thread::state::idle) {
					threads.back()->sign_awaiting();
					return;
				}
			global_pause_lock.lock();

			iter_counts.swap(iter_counts_buffer);
			//iter_counts_buffer.fd = zero;
			step_counter++;

			global_pause_lock.unlock();
			for (auto ptr : threads)
				ptr->sign_awaiting();
			});
		threads.back()->sign_awaiting();
		local_lock.unlock();
	}
}
