# XV6 Operating System Enhancements

A comprehensive enhancement of the MIT xv6 educational operating system with modern features including user authentication, file permissions, advanced shell capabilities, and a Multi-Level Feedback Queue (MLFQ) scheduler.

## 🚀 Features

### ✅ User Authentication System
- **Three user types**: admin, user1, user2 with different permission levels
- **Secure login/logout**: Complete session management
- **Permission enforcement**: UID-based access control

### ✅ File Permission System  
- **File ownership tracking**: UID-based file ownership
- **Access control**: Read, write, execute permissions
- **Administrative tools**: chmod command for permission management

### ✅ Enhanced Shell
- **Command history**: Up/down arrow navigation through previous commands
- **Tab completion**: Auto-complete for commands and filenames
- **User-specific prompts**: Display current user in shell prompt
- **Clear command**: Screen clearing functionality

### ✅ MLFQ Scheduler
- **Three priority levels**: High (0), Medium (1), Low (2) priority queues
- **Automatic demotion**: CPU-bound processes move to lower priorities
- **Priority boost**: Periodic boost to prevent starvation
- **Fair scheduling**: Optimal for mixed workloads

### ✅ Process Monitoring
- **ps command**: Real-time process information with priorities
- **getprocinfo() system call**: Detailed process statistics
- **Scheduler observation**: Monitor MLFQ behavior in real-time

## 🛠️ Quick Start

### Prerequisites
- Linux (Ubuntu/Debian recommended) or macOS
- GCC compiler and Make
- QEMU for emulation

### Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/xv6-enhanced.git
cd xv6-enhanced

# Build and run
cd xv6-source
make
make qemu-nox
```

### First Login
```
Username: admin
Password: admin
```

## 📋 User Accounts

| Username | Password | Permissions | Description |
|----------|----------|-------------|-------------|
| admin    | admin    | Full access | Can modify files, change permissions |
| user1    | pass1    | Read-only   | Can read and execute files only |
| user2    | pass2    | Read+Write  | Can read, write, and execute files |

## 🧪 Testing Features

### Test Authentication
```bash
admin$ whoami
admin$ logout
# Login as different user
Username: user1
Password: pass1
user1$ whoami
```

### Test File Permissions
```bash
admin$ echo "test" > file.txt
admin$ chmod file.txt 0644
admin$ logout
# Login as user1
user1$ cat file.txt     # Should work
user1$ echo "fail" > file.txt  # Should fail
```

### Test MLFQ Scheduler
```bash
admin$ mlfqtest    # Run comprehensive MLFQ test
admin$ ps          # Monitor process priorities
admin$ cpubound &  # Run CPU-intensive process
admin$ ps          # See process demotion
```

### Test Shell Features
```bash
admin$ ls
admin$ history     # View command history
admin$ wh<TAB>     # Tab completion (completes to whoami)
admin$ clear       # Clear screen
```

## 📊 MLFQ Scheduler Details

### Priority Levels
- **Priority 0 (High)**: 4 ticks quantum - Interactive, I/O-bound processes
- **Priority 1 (Medium)**: 8 ticks quantum - Mixed workload processes  
- **Priority 2 (Low)**: 16 ticks quantum - CPU-bound, background processes

### Scheduler Rules
1. Higher priority processes run first
2. Same priority processes use round-robin
3. New processes start at highest priority
4. Process demotion after using full quantum
5. Priority boost every 1000 ticks prevents starvation

## 🏗️ Architecture

The enhanced xv6 maintains the original architecture while adding:

- **Extended process structure** with UID, permissions, and MLFQ fields
- **New system calls** for authentication and monitoring
- **Enhanced file system** with permission checking
- **Improved shell** with modern features

## 📁 Project Structure

```
xv6-enhanced/
├── README.md                 # This file
├── CHANGES.md               # Detailed list of modifications
├── HOW_TO_TEST.md          # Comprehensive testing guide
├── xv6-source/             # Enhanced XV6 source code
│   ├── Makefile            # Build configuration
│   ├── *.c, *.h           # Source files with enhancements
│   └── ...
└── project-report/         # LaTeX project report
    ├── XV6_PROJECT_REPORT_NEW.tex
    └── images/             # Screenshots and documentation
```

## 🎓 Educational Value

This project provides hands-on experience with:
- **Process scheduling algorithms** (MLFQ implementation)
- **Operating system security** (authentication and permissions)
- **System programming** (kernel modifications and system calls)
- **User interface design** (shell enhancements)
- **Software testing** (comprehensive validation)

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is based on MIT xv6 and follows the same licensing terms.

## 🙏 Acknowledgments

- MIT xv6 development team for the excellent educational OS
- IIITDM Kancheepuram for project support
- Operating Systems course instructors and peers

## 📞 Contact

**Anjani Nithin** - CS23B1012  
**Project**: Operating Systems Course  
**Institution**: IIITDM Kancheepuram

---

⭐ **Star this repository if you found it helpful for learning operating systems!**