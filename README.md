an open source c++ thread pool.

use linked list to manage tasks.

use mutex to protect setting task to each thread.

usage:
create all tasks and add the task list to thread pool before calling startThreadPool method.