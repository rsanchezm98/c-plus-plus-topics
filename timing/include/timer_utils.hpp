#ifndef TIMER_UTILS_HPP
#define TIMER_UTILS_HPP

#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include <memory> /* std::unique_ptr */
#include <algorithm> /* std::replace */
#include <mutex> /* for mutex */

namespace timer {

    /* the timer_ measures the life of the scope inside it is called */
    class Timer
    {
        public:
            /* with explicit we make the struct only callable with this constructor */
            explicit Timer(const char* name);

            /* when the destructor is called the latency is computed */
            ~Timer();

            /* stop function to finish with the timer */
            void stop();

        private:
            const char* m_Name;
            bool m_Stopped;
            std::chrono::_V2::system_clock::time_point m_InitPoint;
    };

    struct ProfileResult
    {
        const char* name;
        long long start, end;
        uint32_t threadId;
    };

    struct InstrumentationSession
    {
        const char* name;
    };  

    class Instrumentor
    {
        private:
            std::unique_ptr<InstrumentationSession> m_CurrentSession;
            std::ofstream m_OutputStream;
            int m_ProfileCount;
            std::mutex s_Mutex;
        public:
            Instrumentor();
            void BeginSession(const char* name, const char* filepath);
            void EndSession();
            void WriteHeader();
            void WriteFooter();
            void WriteProfile(const ProfileResult& result);
            static std::shared_ptr<Instrumentor> Get();

    };

    
    /* the timer_ measures the life of the scope inside it is called */
    class InstrumentationTimer
    {
        public:
            /* with explicit we make the struct only callable with this constructor */
            explicit InstrumentationTimer(const char* name);

            /* when the destructor is called the latency is computed */
            ~InstrumentationTimer();

            /* stop function to finish with the timer */
            void stop();

        private:
            const char* m_Name;
            bool m_Stopped;
            std::chrono::_V2::system_clock::time_point m_InitPoint;
    };

} // end of timer

#endif