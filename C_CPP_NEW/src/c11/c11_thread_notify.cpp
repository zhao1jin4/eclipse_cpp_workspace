#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <functional>
#include <mutex>
#include <condition_variable>
using namespace std;

namespace c11_thread_notify{
/*
	class SyncQueue
	{
	public:
	    SyncQueue(int maxSize) : m_maxSize(maxSize) {}

	    void put(const int& x)
	    {
	        unique_lock<mutex> locker(m_mutex);//unique_lock 包装一个 mutex
	        while (m_queue.size() == m_maxSize)//为何不用if,wait会假醒？
	        {
	            cout << "任务队列已满, 请耐心等待..." << endl;
	            m_notFull.wait(locker);//还有wait_for和wait_until方法,第二个参数可传一个函数，返回true不阻塞，返回false阻塞(看源码)
	        }
	        m_queue.push_back(x);
	        cout << x << " 被生产" << endl;
	        m_notEmpty.notify_one(); //也有 notify_all
	    }

	    int take()
	    {
	        unique_lock<mutex> locker(m_mutex);
	        while (m_queue.empty())
	        {
	            cout << "任务队列已空，请耐心等待。。。" << endl;
	            m_notEmpty.wait(locker);
	        }
	        int x = m_queue.front();
	        m_queue.pop_front();
	        m_notFull.notify_one();
	        cout << x << " 被消费" << endl;
	        return x;
	    }

	    bool empty()
	    {
	        lock_guard<mutex> locker(m_mutex);
	        return m_queue.empty();
	    }

	    bool full()
	    {
	        lock_guard<mutex> locker(m_mutex);
	        return m_queue.size() == m_maxSize;
	    }

	    int size()
	    {
	        lock_guard<mutex> locker(m_mutex);
	        return m_queue.size();
	    }

	private:
	    list<int> m_queue;
	    mutex m_mutex;
	    condition_variable m_notEmpty;
	    condition_variable m_notFull;
	    int m_maxSize;
	};
*/



	class SyncQueue //使用 condition_variable_any 可使用任何 mutex (要和进入 函数共用一个mutex??并发低)
	{
	public:
	    SyncQueue(int maxSize) : m_maxSize(maxSize) {}

	    void put(const int& x)
	    {
	        //lock_guard<mutex> locker(m_mutex);
	        // 根据条件阻塞线程
	        m_notFull.wait(m_mutex, [this]() {
	            return m_queue.size() != m_maxSize;
	        });
	        m_queue.push_back(x);
	        cout << x << " 被生产" << endl;
	        m_notEmpty.notify_one();
	    }

	    int take()
	    {
	        //lock_guard<mutex> locker(m_mutex);
	        m_notEmpty.wait(m_mutex, [this]() {
	            return !m_queue.empty();
	        });
	        int x = m_queue.front();
	        m_queue.pop_front();
	        m_notFull.notify_one();
	        cout << x << " 被消费" << endl;
	        return x;
	    }

	    bool empty()
	    {
	        lock_guard<mutex> locker(m_mutex);
	        return m_queue.empty();
	    }

	    bool full()
	    {
	        lock_guard<mutex> locker(m_mutex);
	        return m_queue.size() == m_maxSize;
	    }

	    int size()
	    {
	        lock_guard<mutex> locker(m_mutex);
	        return m_queue.size();
	    }

	private:
	    list<int> m_queue;
	    mutex m_mutex;
	    condition_variable_any m_notEmpty;
	    condition_variable_any m_notFull;
	    int m_maxSize;
	};

	int main(int argc, char* argv[])
	{
		 SyncQueue taskQ(50);
		auto produce = bind(&SyncQueue::put, &taskQ, placeholders::_1);
		auto consume = bind(&SyncQueue::take, &taskQ);
		thread t1[3];
		thread t2[3];
		for (int i = 0; i < 3; ++i)
		{
			t1[i] = thread(produce, i+100);
			t2[i] = thread(consume);
		}

		for (int i = 0; i < 3; ++i)
		{
			t1[i].detach();
			t2[i].detach();
		}

		this_thread::sleep_for(chrono::seconds(2));
	}
};
