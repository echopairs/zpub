#ifndef ZPUB_THREAD_POOL_H
#define ZPUB_THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <atomic>


namespace nsky {
namespace utils {

  using namespace std;
  class ThreadPool {
  public:
  	ThreadPool(size_t);
  	template <typename F, typename... Args>
  	// interface push task
  	auto enqueue(F&& f, Args&&... args)
  		-> std::future<typename std::result_of<F(Args...)>::type>;
  	~ThreadPool();
  private:
  	// workers thread
  	std::vector< std::thread > wks_;
  	// the task queue
  	std::queue< std::function<void()> > tks_;

  	// sync
  	std::mutex mtx_;
  	std::condition_variable cv_;
  	// control thread
  	std::atomic<bool> stop_;
  };

  inline ThreadPool::ThreadPool(size_t threads)
  	:stop_(false)
  {
  	for (size_t i = 0; i < threads; i++)
  	{
  		// create thread jush like emplace_back(thread)
  		wks_.emplace_back(
  			[this]
  			{
  				for(;;)
  				{
  					std::function<void()>task;

  					{
  						std::unique_lock<std::mutex>lock(this->mtx_);
  						// not stop && empty wait again, else continue
  						this->cv_.wait(lock, [this]{ return this->stop_ || !this->tks_.empty(); });
  						// stop && empty just return ,else manage remaining tasks
  						if (this->stop_ && this->tks_.empty())
  						{
  							return ;
  						}
  						task = std::move(this->tks_.front());
  						this->tks_.pop();
  					}
  					task();
  				}
  			}
  		);
  	}
  }

  inline ThreadPool::~ThreadPool()
  {
  	stop_ = true;
  	cv_.notify_all();
  	for (auto & t: wks_)
  	{
  		t.join();
  	}
  }

  // add new task to the pool
  template <typename F, typename... Args>
  // interface push task
  auto ThreadPool::enqueue(F&& f, Args&&... args)
  	-> std::future<typename std::result_of<F(Args...)>::type>
  {
  	using return_type = typename std::result_of<F(Args...)>::type;
  	auto task = std::make_shared<std::packaged_task<return_type()> >(
  		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
  	);

  	// wait task execute
  	std::future <return_type> res = task->get_future();
  	if(stop_)
  	{
  		throw std::runtime_error("enqueue on stoppend ThreadPool");
  	}
  	std::unique_lock<std::mutex>lock(this->mtx_);
  	tks_.emplace([task](){(*task)();});
  	cv_.notify_one();
  	return res;
  }
} // namespace utils
} // namespace nsky

#endif // ZPUB_THREAD_POOL_H
