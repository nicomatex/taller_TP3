/* Includes */
#include "server_thread.h"
#include <utility>
#include <thread>

/*Implementacion de metodos*/
Thread::Thread() {}

Thread::~Thread() {}

void Thread::start() { thread = std::thread(&Thread::run, this); }

void Thread::join() { thread.join(); }

/*Implementacion de constructores por movimiento*/
Thread::Thread(Thread&& other) { this->thread = std::move(other.thread); }

Thread& Thread::operator=(Thread&& other) {
    this->thread = std::move(other.thread);
    return *this;
}
