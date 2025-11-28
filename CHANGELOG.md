# Changelog

All notable changes to the XV6 User Authentication & File Permissions project.

## [1.2.0] - 2025-11-23

### Added
- **MLFQ Scheduler** - Multi-Level Feedback Queue scheduler with 3 priority levels
- **Priority Queues** - High (4 ticks), Medium (8 ticks), Low (16 ticks) quantum
- **Priority Boost** - Periodic boost every 100 ticks to prevent starvation
- **Aging Mechanism** - Promote processes waiting > 50 ticks
- **Scheduler Logging** - Console messages showing scheduler decisions
- **Test Programs** - cpubound, iobound, mixed, mlfqtest for testing MLFQ

### Changed
- Replaced simple round-robin scheduler with MLFQ
- Enhanced process structure with priority, ticks_used, wait_ticks, total_runtime
- Modified timer interrupt handler to track CPU usage and demote processes

### Technical Details
- 3-level priority queue implementation
- Dynamic priority adjustment based on CPU usage
- Prevents starvation through boost and aging
- Favors I/O-bound processes (better responsiveness)

## [1.1.0] - 2025-11-23

### Added
- **Command History** - Navigate through last 10 commands using up/down arrow keys
- **Clear Command** - Built-in `clear` command to clear the screen
- **History Command** - Built-in `history` command to view command history
- Visual feedback for backspace (character erasing)
- Character echoing for better user experience

### Changed
- Enhanced shell input handling with arrow key support
- Improved command-line editing experience

### Technical Details
- Added command history buffer (10 commands)
- Implemented escape sequence handling for arrow keys
- Added ANSI escape codes for screen clearing
- Enhanced getcmd() function with history navigation

## [1.0.0] - 2025-11-23

### Added
- User authentication system with login/logout
- Three default users (admin, user1, user2) with different permission levels
- File ownership tracking (UID per file)
- File permission system (read, write, execute, admin flags)
- New commands:
  - `whoami` - Display current user
  - `chmod` - Change file permissions (admin only)
  - `logout` - Logout and return to login screen
  - `reboot` - Reboot the system
- Enhanced `ls` command showing permissions and owner UID
- Tab completion for filenames in shell
- User-specific shell prompt (admin$, user1$, user2$)
- Error messages for permission denied operations
- O_APPEND flag for proper append operations
- Comprehensive documentation (13 files, ~100KB)

### Fixed
- Logout command now properly exits shell instead of just clearing credentials
- Read-only files now block writes for everyone, including the owner
- Append operator (>>) now correctly appends to files instead of overwriting
- Permission checking logic corrected in sys_write()

### Changed
- `init.c` - Completely rewritten to show login screen at boot
- `sh.c` - Added tab completion, logout handling, and append fix
- `ls.c` - Enhanced to show permissions and owner UID
- `sysfile.c` - Added permission checking and error messages
- `fs.c` - Modified to save/load permissions to/from disk
- `proc.c` - Added user credential management

### Technical Details

#### New System Calls
- `SYS_login` (22) - Authenticate user
- `SYS_logout` (23) - Clear user session
- `SYS_getuid` (24) - Get current user ID
- `SYS_chmod` (25) - Change file permissions
- `SYS_reboot` (26) - Reboot system

#### Modified Structures
- `struct stat` - Added uid and permissions fields
- `struct inode` - Added uid and permissions fields
- `struct dinode` - Added uid and permissions fields (with padding)
- `struct proc` - Added uid and permissions fields

#### New Files
- `user_auth.h` - Authentication structures and constants
- `login.c` - Login program
- `logout.c` - Logout program
- `whoami.c` - Display current user
- `chmod.c` - Change file permissions
- `reboot.c` - Reboot system
- `README.md` - Project documentation
- `CHANGELOG.md` - This file
- `.gitignore` - Git ignore rules

#### Documentation
- `docs/README_FIRST.txt` - Quick start guide
- `docs/DEMO_SCRIPT.txt` - Step-by-step demonstration
- `docs/EXPECTED_OUTPUT.txt` - Expected output for all tests
- `docs/IMPLEMENTATION_DETAILS.txt` - Complete technical documentation
- `docs/BUGS_FIXED.txt` - Bug fixes explained
- `docs/APPEND_BUG_FIXED.txt` - Append operator fix
- `docs/ERROR_MESSAGES_ADDED.txt` - Error message improvements
- `docs/TESTING_GUIDE.txt` - Comprehensive testing instructions
- `docs/FINAL_VERIFICATION.txt` - Verification checklist
- `docs/QUICK_REFERENCE.txt` - Command reference card
- `docs/SUMMARY.txt` - Project overview
- `docs/ALL_DONE.txt` - Completion status
- `docs/DOCUMENTATION_INDEX.txt` - Documentation guide

### Security Considerations
- Passwords stored in plaintext (educational implementation)
- No password hashing (should be added for production)
- Simple permission model (owner-based, no groups)
- Admin can change any file's permissions
- Execute permission not enforced (placeholder for future)

### Known Limitations
- Maximum 10 users (hardcoded)
- No persistent user database (users reset on reboot)
- No password change functionality
- No group permissions
- Tab completion only works in current directory
- No command history

### Future Improvements
- Hash passwords using SHA-256 or similar
- Persistent user database on disk
- Add user management commands (adduser, deluser, passwd)
- Implement group permissions
- Add sudo command for temporary privilege elevation
- Implement execute permission checking
- Add command history with up/down arrows
- Support path completion in tab
- Add file access control lists (ACLs)
- Implement audit logging

## [0.0.0] - Original XV6

### Base System
- Original MIT XV6 operating system
- Basic file system
- Process management
- Simple shell
- Standard UNIX-like commands

---

**Note:** This project is based on MIT's XV6 operating system and is intended for educational purposes.
