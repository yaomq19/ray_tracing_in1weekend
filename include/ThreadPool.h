#pragma once
#include <thread>
#include <queue>
#include <vector>
#include "windows.h"
using namespace std;

class ThreadPool {
public:
	int cnt_thread;
	vector<thread*> m_threads;
	vector<bool> isAccess;
	ThreadPool() {
		SYSTEM_INFO sysInfo;
		//获取当前系统CPU的逻辑核心数，并赋值给n_core
		cnt_thread = sysInfo.dwNumberOfProcessors;
		//线程池大小拓展为逻辑核心数
		m_threads.resize(cnt_thread);
		isAccess.resize(cnt_thread,false);
	}
	ThreadPool(int n_threads) {
		//手动指定线程个数
		cnt_thread = n_threads;
		m_threads.resize(n_threads);
		isAccess.resize(n_threads,false);
	}
};