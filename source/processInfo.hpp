#pragma once

#include <string>
#include <cstdint>
#include <optional>


class ProcessInformation
{
private:
    std::optional<std::uint32_t> PIDself = std::nullopt;
    std::optional<std::uint32_t> lastPID = std::nullopt;

    std::string Nameprocess = "";
    std::string  Statusprocess = "";

    std::optional<std::uint32_t> PPIDprocess = std::nullopt;
    std::optional<std::uint32_t> Threadscount = std::nullopt;
    std::optional<std::uint64_t> RAMusing = std::nullopt;
    std::optional<double> CPUusing = std::nullopt;

    std::string PIDstatusF = "/proc/[PID]/status";
    std::string PIDstatF = "/proc/[PID]/stat";

    const std::string PIDselfF = "/proc/self/stat";
public:
    std::optional<std::uint32_t> PIDselfInfo ();
    std::optional<std::uint32_t> lastPIDInfo ();

    std::string ProcessnameInfo (const std::optional<std::uint32_t>& pid);
    std::string ProcessStatusInfo (const std::optional<std::uint32_t>& pid);

    std::optional<std::uint32_t> PPidInfo (const std::optional<std::uint32_t>& pid);
    std::optional<std::uint32_t> ThreadscountInfo (const std::optional<std::uint32_t>& pid);
    std::optional<std::uint64_t> RAMusingInfo (const std::optional<std::uint32_t>& pid);
    std::optional<double> CPUusingInfo (const std::optional<std::uint32_t>& pid);

        
    std::optional<std::uint32_t> getPIDself () const;
    std::optional<std::uint32_t> getPIDlast () const;

    const std::string& getProcessname () const;
    const std::string& getProcessStatus () const;

    std::optional<std::uint32_t> getPPIDprocess () const;
    std::optional<std::uint32_t> getThreadscount () const;
    const std::optional<std::uint64_t>& getRAMusing () const;
    std::optional<double> getCPUusing () const;
};
