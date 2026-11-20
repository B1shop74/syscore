 #include <iostream>
 #include <fstream>
 #include <string>
 #include <cstdint>
 #include <unistd.h>
 #include <stdexcept>
 #include <optional>
 #include <chrono>
 #include <thread>
 #include <sstream>

 #include "processInfo.hpp"


                                 //  *==========*   PART 1   *==========*  //


std::optional<std::uint32_t> ProcessInformation::PIDselfInfo ()
{
    std::ifstream file(PIDselfF);
    if(!file.is_open())
        throw std::runtime_error("file open error");

    std::string linebuffer;
    unsigned long intvalue;

    file >> linebuffer;
    intvalue = std::stoul(linebuffer);

    PIDself = static_cast<std::optional<std::uint32_t>>(intvalue);
    lastPID = PIDself;
    return PIDself;
}

std::optional<std::uint32_t> ProcessInformation::lastPIDInfo ()
{
    if(lastPID == std::nullopt)
        throw std::runtime_error("Not found");

    return lastPID;
}


                                //  *==========*   PART 2   *==========*  //


std::string ProcessInformation::ProcessnameInfo (const std::optional<std::uint32_t>& pid)
{
    if(!pid.has_value())
        throw std::invalid_argument("process empty");

    PIDstatusF = "/proc/" + std::to_string(pid.value()) + "/status";
    std::ifstream file(PIDstatusF);
    if(!file.is_open())
        throw std::runtime_error("file open error");

    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        if(linebuffer.empty())
            throw std::logic_error("Empty file error");

        std::size_t pos = linebuffer.find("Name:");
        if(pos != std::string::npos){
            pos = linebuffer.find_first_not_of(" \t", pos + 5);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos);
            Nameprocess = namebuffer;
            break;
        }
    }
    if(Nameprocess == "")
        throw std::logic_error("Not found");

    lastPID = pid;
    return Nameprocess;
}

std::string ProcessInformation::ProcessStatusInfo (const std::optional<std::uint32_t>& pid)
{
    if(!pid.has_value())
            throw std::invalid_argument("process empty");

    PIDstatusF = "/proc/" + std::to_string(pid.value()) + "/status";
    std::ifstream file(PIDstatusF);
    if(!file.is_open())
        throw std::runtime_error("file open error");

    std::string namebuffer;
    std::string linebuffer;
    while(std::getline(file, linebuffer))
    {
        std::size_t pos = linebuffer.find("State:");
        if(pos != std::string::npos){
            pos = linebuffer.find_first_not_of(" \t", pos + 6);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos);
            Statusprocess = namebuffer;
            break;
        }
    }
    if(Statusprocess == "")
        throw std::logic_error("Not found");

    lastPID = pid;
    return Statusprocess;
}

std::optional<std::uint32_t> ProcessInformation::PPidInfo(const std::optional<std::uint32_t>& pid)
{
    if(!pid.has_value())
        throw std::invalid_argument("process empty");

    PIDstatusF = "/proc/" + std::to_string(pid.value()) + "/status";
    std::ifstream file(PIDstatusF);
    if(!file.is_open())
        throw std::runtime_error("file open error");

    std::string namebuffer;
    std::string linebuffer;
    unsigned long intvalue;

    while(std::getline(file, linebuffer))
    {
        std::size_t pos = linebuffer.find("PPid:");
        if(pos != std::string::npos){
            pos = linebuffer.find_first_not_of(" \t", pos + 5);
            if(pos == std::string::npos)
                throw std::runtime_error("Not found");

            namebuffer = linebuffer.substr(pos);
            intvalue = std::stoul(namebuffer);

            PPIDprocess = static_cast<std::optional<std::uint32_t>>(intvalue);
            break;
        }
    }
    if(PPIDprocess == std::nullopt)
        throw std::logic_error("Not found");

    lastPID = pid;
    return PPIDprocess;
}

std::optional<std::uint32_t> ProcessInformation::ThreadscountInfo(const std::optional<std::uint32_t>& pid)
{
    if(!pid.has_value())
        throw std::invalid_argument("process empty");

    PIDstatusF = "/proc/" + std::to_string(pid.value()) + "/status";
    std::ifstream file(PIDstatusF);
    if(!file.is_open())
        throw std::runtime_error("file open error");

    std::string namebuffer;
    std::string linebuffer;
    unsigned long intvalue;

    while(std::getline(file, linebuffer))
    {
        std::size_t pos = linebuffer.find("Threads:");
        if(pos != std::string::npos){
            pos = linebuffer.find_first_not_of(" \t", pos + 8);
            if(pos == std::string::npos)
                throw std::runtime_error("Not found");

            namebuffer = linebuffer.substr(pos);
            intvalue = std::stoul(namebuffer);

            Threadscount = static_cast<std::optional<std::uint32_t>>(intvalue);
            break;
        }
    }
    if(Threadscount == std::nullopt)
        throw std::logic_error("Not found");

    lastPID = pid;
    return Threadscount;
}
std::optional<std::uint64_t> ProcessInformation::RAMusingInfo(const std::optional<std::uint32_t>& pid)

{
    if(!pid.has_value())
        throw std::invalid_argument("process empty");

    PIDstatusF = "/proc/" + std::to_string(pid.value()) + "/status";
    std::ifstream file(PIDstatusF);
    if(!file.is_open())
        throw std::runtime_error("file open error");

    std::string namebuffer;
    std::string linebuffer;
    unsigned long long intvalue;

    while(std::getline(file, linebuffer))
    {
        std::size_t pos = linebuffer.find("VmRSS:");
        if(pos != std::string::npos){
            pos = linebuffer.find_first_not_of(" \t", pos + 6);
            if(pos == std::string::npos)
                throw std::runtime_error("Not found");

            namebuffer = linebuffer.substr(pos);
            intvalue = std::stoull(namebuffer) * 1024ULL;

            RAMusing = static_cast<std::optional<std::uint64_t>>(intvalue);
            break;
        }
    }
    if(RAMusing == std::nullopt)
        throw std::logic_error("Not found");

    lastPID = pid;
    return RAMusing;
}


std::optional<double> ProcessInformation::CPUusingInfo(const std::optional<std::uint32_t>& pid)
{
    if(!pid.has_value())
        throw std::invalid_argument("process empty");

    PIDstatF = "/proc/" + std::to_string(pid.value()) + "/stat";

    std::string linebuffer = "NULL";
    std::string buffer;

    std::chrono::steady_clock::time_point time1;
    std::chrono::steady_clock::time_point time2;

    unsigned long utime;
    unsigned long stime;

    std::size_t pos1 = 0;

    double CPUtime1 = 0.0;
    double CPUtime2 = 0.0;

    std::uint8_t counter = 0;

    while (counter < 2)
    {
        std::ifstream file(PIDstatF);
        if(!file.is_open())
            throw std::runtime_error("file open error");

        if(!std::getline(file, linebuffer))
            throw std::runtime_error("file empty");

        if(counter == 0)
            time1 = std::chrono::steady_clock::now();
        else
            time2 = std::chrono::steady_clock::now();

        pos1 = linebuffer.rfind(')');
        if(pos1 == std::string::npos)
            throw std::runtime_error("Invalid stat format");

        std::istringstream stream(linebuffer.substr(pos1 + 2));

        for(int i = 0; i < 11; i++)
        {
            if(!(stream >> buffer))
                throw std::runtime_error("Invalid stat format");
        }

        if(!(stream >> utime >> stime))
            throw std::runtime_error("Invalid stat format");

        if(counter == 0){
            unsigned long tmp1 = (utime + stime);
            CPUtime1 = static_cast<double>(tmp1);

            counter++;
            file.close();

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else if(counter == 1){
            unsigned long tmp2 = (utime + stime);
            CPUtime2 = static_cast<double>(tmp2);
            counter++;
        }
    }


    long tmpp = sysconf(_SC_CLK_TCK);
    if(tmpp == -1)
        throw std::invalid_argument("CTK_TCK error");

    double CLK_TCK = static_cast<double>(tmpp);
    double deltaCPUtime = (CPUtime2 - CPUtime1);
    double deltaT = std::chrono::duration<double>(time2 - time1).count();
    if(deltaT <= 0.0)
        throw std::runtime_error("Invalid time interval");

    double tmp = ((deltaCPUtime / (CLK_TCK * deltaT)) * 100.0);

    CPUusing = static_cast<std::optional<double>>(tmp);
    lastPID = pid;
    return CPUusing;
}


                                //  *==========*   PART 3   *==========*  //


std::optional<std::uint32_t> ProcessInformation::getPIDself () const { return PIDself; }
std::optional<std::uint32_t> ProcessInformation::getPIDlast () const { return lastPID; }

const std::string& ProcessInformation::getProcessname () const { return Nameprocess; }
const std::string& ProcessInformation::getProcessStatus () const { return Statusprocess; }

std::optional<std::uint32_t> ProcessInformation::getPPIDprocess () const { return PPIDprocess; }
std::optional<std::uint32_t> ProcessInformation::getThreadscount () const { return Threadscount; }
const std::optional<std::uint64_t>& ProcessInformation::getRAMusing () const { return RAMusing; }
std::optional<double> ProcessInformation::getCPUusing () const { return CPUusing; }
