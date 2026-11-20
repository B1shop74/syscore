# SysCore

A lightweight Linux system monitoring tool written in C++20.

## Overview

SysCore is a command-line utility designed to retrieve and display system and process information on Linux systems.

The project interacts directly with Linux system interfaces, primarily `/proc` and `/sys`, to collect information about hardware, memory, operating system details, and running processes.

It is built with a modular C++20 architecture using CMake.

## Features

### System Information

- Operating system name
- Kernel version
- Hostname
- System uptime
- System architecture

### CPU Information

- CPU model
- Number of CPU cores
- Number of CPU threads
- Maximum CPU frequency
- Current CPU frequency

### Memory Information

- Total RAM
- Free RAM
- Available RAM
- Used RAM

### Process Information

Retrieve information about a specific process using its PID:

- Process name
- Process state
- Parent process ID (PPID)
- Number of threads
- RAM usage
- CPU usage

CPU usage is calculated by sampling process statistics over a time interval.

## Technologies

- C++20
- Linux `/proc` filesystem
- Linux `/sys` filesystem
- CMake 3.20+

## Project Structure

```text
syscore/
├── source/
│   ├── main.cpp
│   ├── systemInfo.cpp
│   ├── systemInfo.hpp
│   ├── processInfo.cpp
│   └── processInfo.hpp
│
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Build

### Requirements

- Linux
- C++20-compatible compiler
- CMake 3.20 or newer
- Build tool such as Make or Ninja

### Compilation

Clone the repository:

```bash
git clone https://github.com/B1shop74/syscore.git
cd syscore
```

Configure the project:

```bash
cmake -S . -B build
```

Build the executable:

```bash
cmake --build build
```

The executable will be located at:

```text
build/syscore
```

## Usage

### Display System Information

Display general system, CPU, and RAM information:

```bash
./build/syscore system
```

Display CPU information only:

```bash
./build/syscore system cpu
```

Display RAM information only:

```bash
./build/syscore system ram
```

Display specific system information:

```bash
./build/syscore system -n
./build/syscore system -k
./build/syscore system -h
./build/syscore system -u
./build/syscore system -a
```

Options:

| Option | Information |
|---|---|
| `-n` | Operating system name |
| `-k` | Kernel version |
| `-h` | Hostname |
| `-u` | System uptime |
| `-a` | System architecture |

### Display Process Information

Retrieve information about a process by its PID:

```bash
./build/syscore process 1234
```

Replace `1234` with the PID of the process you want to inspect.

## Implementation Notes

SysCore reads system information from Linux interfaces, including:

- `/proc/cpuinfo`
- `/proc/meminfo`
- `/proc/uptime`
- `/proc/[PID]/status`
- `/proc/[PID]/stat`
- `/etc/os-release`
- `/sys/devices/system/cpu/`

Some CPU frequency information depends on the availability of the corresponding sysfs files.

CPU usage measurement takes approximately one second because it compares two process CPU-time samples.

## Author

**B1shop74**

GitHub: https://github.com/B1shop74
