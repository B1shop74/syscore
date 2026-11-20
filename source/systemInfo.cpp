#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <sys/utsname.h>
#include <stdexcept>
#include <optional>

#include "systemInfo.hpp"


                                        //  *==========*   PART 1   *==========*  //


void SystemInformation::OSnameInfo ()
{
    std::ifstream file(LinuxnameF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        std::size_t pos = linebuffer.find("PRETTY_NAME");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find('"', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find('=');

            namebuffer = linebuffer.substr(pos + 1, linebuffer.length() - pos - 2);
            OSname = namebuffer;
            break;
        }
    }
}

void SystemInformation::KernelInfo ()
{
    std::ifstream file(LinuxkernelF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    std::string linebuffer;
    std::getline(file, linebuffer);
    if(linebuffer.empty() || file.fail())
        throw std::logic_error("Empty file error");

    Kernel = linebuffer;
}

void SystemInformation::HostnameInfo ()
{
    std::ifstream file(LinuxhostF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    std::string linebuffer;
    std::getline(file, linebuffer);
    if(linebuffer.empty() || file.fail())
        throw std::logic_error("Empty file error");

    Hostname = linebuffer;
}

void SystemInformation::UptimeInfo ()
{
    std::ifstream file(LinuxuptimeF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    std::string namebuffer;
    std::string linebuffer;
    std::getline(file, linebuffer);
    if(linebuffer.empty() || file.fail())
        throw std::logic_error("Empty file error");

    std::size_t pos = linebuffer.find_first_of(" \t");
    if(pos == std::string::npos)
        throw std::runtime_error("File process error");

    namebuffer = linebuffer.substr(0, pos);
    Uptime = namebuffer;
}

void SystemInformation::ArchitectureInfo ()
{
        struct utsname linebuffer;
        if(uname(&linebuffer) == -1)
            throw std::runtime_error("Syscall error");

        Architecture = linebuffer.machine;
}


                                //  *==========*   PART 2   *==========*  //


void SystemInformation::CPU_modelInfo ()
{
    std::ifstream file(CPUinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        std::size_t pos = linebuffer.find("model name");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find(':', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find("model name");

            pos = linebuffer.find_first_not_of(" \t", pos + 1);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos);
            CPUmodel = namebuffer;
            break;
        }
    }
}

void SystemInformation::CPU_coresInfo ()
{
    std::ifstream file(CPUinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    unsigned long intvalue;
    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        std::size_t pos = linebuffer.find("cpu cores");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find(':', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find("cpu cores");

            pos = linebuffer.find_first_not_of(" \t", pos + 1);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos);
            intvalue = std::stoul(namebuffer);

            if(intvalue > UINT32_MAX)
                throw std::out_of_range("Value too large");

            CPUcores = static_cast<std::uint32_t>(intvalue);
            break;
        }
    }
}

void SystemInformation::CPU_threadsInfo ()
{
    std::ifstream file(CPUinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    unsigned long intvalue;
    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        std::size_t pos = linebuffer.find("siblings");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find(':', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find("siblings");

            pos = linebuffer.find_first_not_of(" \t", pos + 1);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos);
            intvalue = std::stoul(namebuffer);

            if(intvalue > UINT32_MAX)
                throw std::out_of_range("Value too large");

            CPUthreads = static_cast<std::uint32_t>(intvalue);
            break;
        }
    }
}

void SystemInformation::CPU_maxFrequencyInfo ()
{
    std::ifstream file(CPUmaxFrequencyinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    unsigned long intvalue;
    std::string linebuffer;

    std::getline(file, linebuffer);
    if(linebuffer.empty())
        throw std::logic_error("Empty file error");

    intvalue = std::stoul(linebuffer);
    CPUmaxFrequency = (static_cast<double>(intvalue) / 1000000.0);
}

void SystemInformation::CPU_currentFrequencyInfo ()
{
    std::ifstream file(CPUcurrentFrequencyinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    unsigned long intvalue;
    std::string linebuffer;

    std::getline(file, linebuffer);
    if(linebuffer.empty())
        throw std::logic_error("Empty file error");

    intvalue = std::stoul(linebuffer);
    CPUcurrentFrequency = (static_cast<double>(intvalue) / 1000000.0);
}


                                //  *==========*   PART 3   *==========*  //


void SystemInformation::RAM_totalInfo ()
{
    std::ifstream file(RAMinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    unsigned long long intvalue;
    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        if(linebuffer.empty())
            throw std::logic_error("Empty file error");

        std::size_t pos = linebuffer.find("MemTotal");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find(':', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find("MemTotal");

            pos = linebuffer.find_first_not_of(" \t", pos + 1);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos, linebuffer.length() - pos);
            intvalue = std::stoull(namebuffer);

            RAMtotal = (static_cast<std::uint64_t>(intvalue) * 1024ULL);
            break;
        }
    }
}

void SystemInformation::RAM_freeInfo ()
{
    std::ifstream file(RAMinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    unsigned long long intvalue;
    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        if(linebuffer.empty())
            throw std::logic_error("Empty file error");

        std::size_t pos = linebuffer.find("MemFree");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find(':', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find("MemFree");

            pos = linebuffer.find_first_not_of(" \t", pos + 1);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos, linebuffer.length() - pos);
            intvalue = std::stoull(namebuffer);

            RAMfree = (static_cast<std::uint64_t>(intvalue) * 1024ULL);
            break;
        }
    }
}

void SystemInformation::RAM_availableInfo ()
{
    std::ifstream file(RAMinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    unsigned long long intvalue;
    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        if(linebuffer.empty())
            throw std::logic_error("Empty file error");

        std::size_t pos = linebuffer.find("MemAvailable");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find(':', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find("MemTotal");

            pos = linebuffer.find_first_not_of(" \t", pos + 1);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos, linebuffer.length() - pos);
            intvalue = std::stoull(namebuffer);

            RAMavailable = (static_cast<std::uint64_t>(intvalue) * 1024ULL);
            break;
        }
    }
}

void SystemInformation::RAM_usedInfo ()
{
    if(RAMtotal != std::nullopt && RAMavailable != std::nullopt){
        RAMused = (RAMtotal.value() - RAMavailable.value());
        return;
    }

    std::ifstream file(RAMinfoF);
    if(!file.is_open())
        throw std::runtime_error("File open error");

    unsigned long long intvalue;
    std::string namebuffer;
    std::string linebuffer;

    while(std::getline(file, linebuffer))
    {
        if(linebuffer.empty())
            throw std::logic_error("Empty file error");

        std::size_t pos = linebuffer.find("MemTotal");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find(':', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find("MemTotal");

            pos = linebuffer.find_first_not_of(" \t", pos + 1);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos, linebuffer.length() - pos);
            intvalue = std::stoull(namebuffer);

            RAMtotal = (static_cast<std::uint64_t>(intvalue) * 1024ULL);
            break;
        }
    }


    file.clear();
    file.seekg(0);

    intvalue = 0;
    namebuffer = "";
    linebuffer = "";

    while(std::getline(file, linebuffer))
    {
        if(linebuffer.empty())
            throw std::logic_error("Empty file error");

        std::size_t pos = linebuffer.find("MemAvailable");
        if(pos != std::string::npos)
        {
            pos = linebuffer.find(':', pos);
            if(pos == std::string::npos)
                pos = linebuffer.find("MemTotal");

            pos = linebuffer.find_first_not_of(" \t", pos + 1);
            if(pos == std::string::npos)
                throw std::logic_error("Not found");

            namebuffer = linebuffer.substr(pos, linebuffer.length() - pos);
            intvalue = std::stoull(namebuffer);

            RAMavailable = (static_cast<std::uint64_t>(intvalue) * 1024ULL);
            break;
        }
    }

    RAMused = (RAMtotal.value() - RAMavailable.value());
}


                                //  *==========*   PART 4   *==========*  //



const std::string& SystemInformation::getOSname () const { return OSname; } 
const std::string& SystemInformation::getKernel () const { return Kernel; }
const std::string& SystemInformation::getHostname () const { return Hostname; } 
const std::string& SystemInformation::getUptime () const { return Uptime; } 
const std::string& SystemInformation::getArchitecture () const { return Architecture; } 

const std::string& SystemInformation::getCPUmodel () const { return CPUmodel; } 
std::optional<std::uint32_t> SystemInformation::getCPUcores () const { return CPUcores; } 
std::optional<std::uint32_t> SystemInformation::getCPUthreads () const { return CPUthreads; } 
std::optional<double> SystemInformation::getCPUmaxFrequency () const { return CPUmaxFrequency; } 
std::optional<double> SystemInformation::getCPUcurrentFrequency () const { return CPUcurrentFrequency; } 

const std::optional<std::uint64_t>& SystemInformation::getRAMtotal () const { return RAMtotal; } 
const std::optional<std::uint64_t>& SystemInformation::getRAMfree () const { return RAMfree; } 
const std::optional<std::uint64_t>& SystemInformation::getRAMavailable () const { return RAMavailable; } 
const std::optional<std::uint64_t>& SystemInformation::getRAMused () const { return RAMused; } 
//   +-70R4-+ - -+8/-\88*1*-+ |:/:\:\:/:| -+*71|| |\1|\/|-+   //