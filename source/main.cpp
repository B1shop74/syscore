#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <optional>
#include <limits>
#include <cstdint>

#include "systemInfo.hpp"
#include "processInfo.hpp"

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
            throw std::invalid_argument("Usage: syscore <system|process>");

        const std::string_view command = argv[1];

        if (command == "system")
        {
            SystemInformation system;

            auto printCPU = [&]()
            {
                std::cout << "\n--- CPU ---\n";
                std::cout << "Model: " << system.getCPUmodel() << '\n';

                if (auto value = system.getCPUcores())
                    std::cout << "Cores: " << *value << '\n';

                if (auto value = system.getCPUthreads())
                    std::cout << "Threads: " << *value << '\n';

                if (auto value = system.getCPUmaxFrequency())
                    std::cout << "Max frequency: " << *value << " MHz\n";

                if (auto value = system.getCPUcurrentFrequency())
                    std::cout << "Current frequency: " << *value << " MHz\n";
            };

            auto printRAM = [&]()
            {
                std::cout << "\n--- RAM ---\n";

                if (auto value = system.getRAMtotal())
                    std::cout << "Total: " << *value << " bytes\n";

                if (auto value = system.getRAMfree())
                    std::cout << "Free: " << *value << " bytes\n";

                if (auto value = system.getRAMavailable())
                    std::cout << "Available: " << *value << " bytes\n";

                if (auto value = system.getRAMused())
                    std::cout << "Used: " << *value << " bytes\n";
            };

            if (argc == 2)
            {
                system.OSnameInfo();
                system.KernelInfo();
                system.HostnameInfo();
                system.UptimeInfo();
                system.ArchitectureInfo();

                system.CPU_modelInfo();
                system.CPU_coresInfo();
                system.CPU_threadsInfo();
                system.CPU_maxFrequencyInfo();
                system.CPU_currentFrequencyInfo();

                system.RAM_totalInfo();
                system.RAM_freeInfo();
                system.RAM_availableInfo();
                system.RAM_usedInfo();

                std::cout << "--- SYSTEM ---\n";
                std::cout << "OS: " << system.getOSname() << '\n';
                std::cout << "Kernel: " << system.getKernel() << '\n';
                std::cout << "Hostname: " << system.getHostname() << '\n';
                std::cout << "Uptime: " << system.getUptime() << '\n';
                std::cout << "Architecture: " << system.getArchitecture() << '\n';

                printCPU();
                printRAM();
            }
            else if (argc == 3)
            {
                const std::string_view params = argv[2];

                if (params == "cpu")
                {
                    system.CPU_modelInfo();
                    system.CPU_coresInfo();
                    system.CPU_threadsInfo();
                    system.CPU_maxFrequencyInfo();
                    system.CPU_currentFrequencyInfo();

                    printCPU();
                }
                else if (params == "ram")
                {
                    system.RAM_totalInfo();
                    system.RAM_freeInfo();
                    system.RAM_availableInfo();
                    system.RAM_usedInfo();

                    printRAM();
                }
                else if (params.size() >= 2 &&
                         params.size() <= 5 &&
                         params[0] == '-')
                {
                    for (std::size_t i = 1; i < params.size(); ++i)
                    {
                        switch (params[i])
                        {
                            case 'n':
                                system.OSnameInfo();
                                std::cout << "OS: " << system.getOSname() << '\n';
                                break;

                            case 'k':
                                system.KernelInfo();
                                std::cout << "Kernel: " << system.getKernel() << '\n';
                                break;

                            case 'h':
                                system.HostnameInfo();
                                std::cout << "Hostname: " << system.getHostname() << '\n';
                                break;

                            case 'u':
                                system.UptimeInfo();
                                std::cout << "Uptime: " << system.getUptime() << '\n';
                                break;

                            case 'a':
                                system.ArchitectureInfo();
                                std::cout << "Architecture: " << system.getArchitecture() << '\n';
                                break;

                            default:
                                throw std::invalid_argument("Unknown system option");
                        }
                    }
                }
                else
                    throw std::invalid_argument("Invalid system arguments");
            }
            else
                throw std::invalid_argument("Too many system arguments");
        }

        else if (command == "process")
        {
            if (argc != 3)
                throw std::invalid_argument("Usage: syscore process <PID>");

            const std::string_view pidArg = argv[2];

            if (pidArg.empty() ||
                pidArg.find_first_not_of("0123456789") != std::string_view::npos)
                throw std::invalid_argument("PID must be a positive integer");

            const unsigned long tmp = std::stoul(std::string(pidArg));

            if (tmp == 0 || tmp > std::numeric_limits<std::uint32_t>::max())
                throw std::invalid_argument("PID is out of range");

            const std::optional<std::uint32_t> pid =
                static_cast<std::uint32_t>(tmp);

            ProcessInformation process;

            process.PIDselfInfo();
            process.lastPIDInfo();

            process.ProcessnameInfo(pid);
            process.ProcessStatusInfo(pid);
            process.PPidInfo(pid);
            process.ThreadscountInfo(pid);
            process.RAMusingInfo(pid);
            process.CPUusingInfo(pid);

            std::cout << "--- PROCESS ---\n";

            if (auto value = process.getPIDself())
                std::cout << "Current PID: " << *value << '\n';

            if (auto value = process.getPIDlast())
                std::cout << "Last PID: " << *value << '\n';

            std::cout << "Name: " << process.getProcessname() << '\n';
            std::cout << "Status: " << process.getProcessStatus() << '\n';

            if (auto value = process.getPPIDprocess())
                std::cout << "Parent PID: " << *value << '\n';

            if (auto value = process.getThreadscount())
                std::cout << "Threads: " << *value << '\n';

            if (auto value = process.getRAMusing())
                std::cout << "RAM: " << *value << " bytes\n";

            if (auto value = process.getCPUusing())
                std::cout << "CPU usage: " << *value << "%\n";
        }
        
        else
            throw std::invalid_argument("Unknown command");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}