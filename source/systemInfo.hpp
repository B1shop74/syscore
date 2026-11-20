#pragma once

#include <string>
#include <cstdint>
#include <optional>

class SystemInformation
{
private:
    std::string OSname = "";
    std::string Kernel = "";
    std::string Hostname = "";
    std::string Uptime = "";
    std::string Architecture = "";

    std::string CPUmodel = "";
    std::optional<std::uint32_t> CPUcores = std::nullopt;
    std::optional<std::uint32_t> CPUthreads = std::nullopt;
    std::optional<double> CPUmaxFrequency = std::nullopt;
    std::optional<double> CPUcurrentFrequency = std::nullopt;

    std::optional<std::uint64_t> RAMtotal = std::nullopt;
    std::optional<std::uint64_t> RAMfree = std::nullopt;
    std::optional<std::uint64_t> RAMused = std::nullopt;
    std::optional<std::uint64_t> RAMavailable = std::nullopt;


    const std::string LinuxnameF = "/etc/os-release";
    const std::string LinuxkernelF = "/proc/sys/kernel/osrelease";
    const std::string LinuxhostF = "/proc/sys/kernel/hostname";
    const std::string LinuxuptimeF = "/proc/uptime";

    const std::string CPUinfoF = "/proc/cpuinfo";
    const std::string CPUmaxFrequencyinfoF = "/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq";
    const std::string CPUcurrentFrequencyinfoF = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq";

    const std::string RAMinfoF = "/proc/meminfo";

public:
    void OSnameInfo ();
    void KernelInfo ();
    void HostnameInfo ();
    void UptimeInfo ();
    void ArchitectureInfo ();

    void CPU_modelInfo ();
    void CPU_coresInfo ();
    void CPU_threadsInfo ();
    void CPU_maxFrequencyInfo ();
    void CPU_currentFrequencyInfo ();

    void RAM_totalInfo ();
    void RAM_freeInfo ();
    void RAM_availableInfo ();
    void RAM_usedInfo ();

    const std::string& getOSname () const;
    const std::string& getKernel () const;
    const std::string& getHostname () const;
    const std::string& getUptime () const;
    const std::string& getArchitecture () const;

    const std::string& getCPUmodel () const;
    std::optional<std::uint32_t> getCPUcores () const;
    std::optional<std::uint32_t> getCPUthreads () const;
    std::optional<double> getCPUmaxFrequency () const;
    std::optional<double> getCPUcurrentFrequency () const;

    const std::optional<std::uint64_t>& getRAMtotal () const;
    const std::optional<std::uint64_t>& getRAMfree () const;
    const std::optional<std::uint64_t>& getRAMavailable () const;
    const std::optional<std::uint64_t>& getRAMused () const;
};