#include <iostream>
#include <coroutine>
#include <stdexcept>
#include <thread>
using namespace std;

namespace c20_coroutine {
//https://en.cppreference.com/w/cpp/language/coroutines 中的代码

	struct promise;
	struct coroutine : std::coroutine_handle<promise>
	{ using promise_type = struct promise; };

	struct promise {
	coroutine get_return_object()
	  { return {coroutine::from_promise(*this)}; }
	  std::suspend_always initial_suspend() noexcept { return {}; }
	  std::suspend_never final_suspend() noexcept { return {}; }
	  void return_void() {}
	  void unhandled_exception() {}
	};

	struct S {
	  int i;
	  coroutine f() {
		std::cout << i;
		co_return;
	  }
	};

	void bad1() {
	  coroutine h = S{0}.f();
	  // S{0} destroyed
	  h.resume(); // resumed coroutine executes std::cout << i, uses S::i after free
	  h.destroy();
	}

	coroutine bad2() {
	  S s{0};
	  return s.f(); // returned coroutine can't be resumed without committing use after free
	}

	void bad3() {
	  coroutine h = [i = 0]() -> coroutine { // a lambda that's also a coroutine
		std::cout << i;
		co_return;
	  }(); // immediately invoked
	  // lambda destroyed
	  h.resume(); // uses (anonymous lambda type)::i after free
	  h.destroy();
	}

	void good() {
	  coroutine h = [](int i) -> coroutine { // make i a coroutine parameter
		std::cout << i;
		co_return;
	  }(0);
	  // lambda destroyed
	  h.resume(); // no problem, i has been copied to the coroutine frame as a by-value parameter
	  h.destroy();
	}



	auto switch_to_new_thread(std::jthread& out) {
	  struct awaitable {
		std::jthread* p_out;
		bool await_ready() { return false; }
		void await_suspend(std::coroutine_handle<> h) {
		  std::jthread& out = *p_out;
		  if (out.joinable())
			throw std::runtime_error("Output jthread parameter not empty");
		  out = std::jthread([h] { h.resume(); });
		  // Potential undefined behavior: accessing potentially destroyed *this
		  // std::cout << "New thread ID: " << p_out->get_id() << '\n';
		  std::cout << "New thread ID: " << out.get_id() << '\n'; // this is OK
		}
		void await_resume() {}
	  };
	  return awaitable{&out};
	}

	struct task{
	  struct promise_type {
		task get_return_object() { return {}; }
		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() {}
	  };
	};

	task resuming_on_new_thread(std::jthread& out) {
	  std::cout << "Coroutine started on thread: " << std::this_thread::get_id() << '\n';
	  co_await switch_to_new_thread(out);
	  // awaiter destroyed here
	  std::cout << "Coroutine resumed on thread: " << std::this_thread::get_id() << '\n';
	}

	int main(int  argc, char* argv[])
	{
		std::jthread out;
		resuming_on_new_thread(out);
		return 1;
	}
}
