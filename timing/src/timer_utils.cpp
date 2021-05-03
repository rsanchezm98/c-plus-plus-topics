#include "timer_utils.hpp"

namespace timer {

    /* explicit constuctor */
    Timer::Timer(const char* name)
        : m_Name(name), m_Stopped(false)
    {
        m_InitPoint = std::chrono::high_resolution_clock::now();
    }

    Timer::~Timer()
    {
        if(!m_Stopped) 
            stop();
    }

    void Timer::stop()
    {
        auto endPoint = std::chrono::high_resolution_clock::now();
        
        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_InitPoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

        std::cout << "[" << m_Name << "]: Duration of " << (end-start)/1000.0 << " ms" << std::endl;
        m_Stopped = true;
    }

    Instrumentor::Instrumentor()
        :m_CurrentSession(nullptr), m_ProfileCount(0)
    {
        std::cout << "Creation of the instrumentor!\n";
    }

    void Instrumentor::BeginSession(const char* name, const char* filepath)
    {
        m_OutputStream.open(filepath);
        WriteHeader();
        m_CurrentSession = std::make_unique<InstrumentationSession>();
    }

    void Instrumentor::EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        m_ProfileCount = 0;
    }

    void Instrumentor::WriteProfile(const ProfileResult& result)
    {
        std::lock_guard<std::mutex> lock(s_Mutex);
        
        if(m_ProfileCount++ > 0)
        {
            m_OutputStream << ",";
        }

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (result.end - result.start) << ",";
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":0,";
        m_OutputStream << "\"tid\":" << result.threadId << ",";
        m_OutputStream << "\"ts\":" << result.start;
        m_OutputStream << "}";

        m_OutputStream.flush();
    }

    void Instrumentor::WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();
    }

    void Instrumentor::WriteFooter()
    {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    std::shared_ptr<Instrumentor> Instrumentor::Get()
    {
        static std::shared_ptr<Instrumentor> instance = std::make_shared<Instrumentor>();
        return instance;
    }

    InstrumentationTimer::InstrumentationTimer(const char* name)
        : m_Name(name), m_Stopped(false)
    {
        m_InitPoint = std::chrono::high_resolution_clock::now();
    }

    InstrumentationTimer::~InstrumentationTimer()
    {
        if(!m_Stopped) 
            stop();
    }


    void InstrumentationTimer::stop()
    {
        auto endPoint = std::chrono::high_resolution_clock::now();
        
        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_InitPoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

        /* we need to convert from std::thread::id to uint32_T */
        uint32_t threadId = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::Get()->WriteProfile({m_Name, start, end, threadId});
        m_Stopped = true;
    }

} // end of timer