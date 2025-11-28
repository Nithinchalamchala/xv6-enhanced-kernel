# XV6 Enhanced Features - Testing Guide

This guide provides step-by-step instructions for testing all enhanced features in the XV6 operating system.

## 🚀 Getting Started

### Build and Run XV6
```bash
cd xv6-source
make clean
make
make qemu-nox
```

### Initial System Boot
After booting, you'll see the login prompt:
```
=== XV6 User Authentication System ===
Default users:
admin/admin (full access)
user1/pass1 (read only)  
user2/pass2 (read+write)
=====================================
Username: 
```

## 🔐 Testing User Authentication

### Test 1: Valid Admin Login
```bash
Username: admin
Password: admin
# Expected: Login successful, admin$ prompt appears
```

### Test 2: Invalid Login Attempts
```bash
Username: admin
Password: wrong
# Expected: Login failed message

Username: baduser  
Password: anything
# Expected: Login failed message
```

### Test 3: User Switching
```bash
admin$ logout
# Expected: Returns to login screen

Username: user1
Password: pass1
# Expected: user1$ prompt appears

user1$ whoami
# Expected: user1
```

### Test 4: Permission Verification
```bash
user1$ whoami
# Expected: Shows current user (user1, user2, or admin)

admin$ whoami  
# Expected: admin
```

## 📁 Testing File Permission System

### Test 5: File Creation and Ownership
```bash
admin$ echo "test content" > testfile.txt
admin$ ls -l
# Expected: Shows file with admin ownership
```

### Test 6: Permission Checking
```bash
admin$ chmod testfile.txt 0644
admin$ ls -l  
# Expected: Shows updated permissions

admin$ logout
Username: user1
Password: pass1

user1$ cat testfile.txt
# Expected: Should work (read permission)

user1$ echo "user1 edit" > testfile.txt
# Expected: Should fail (no write permission)
```

### Test 7: Administrative Privileges
```bash
user1$ chmod testfile.txt 0777
# Expected: Permission denied (user1 is not admin)

user1$ logout
Username: admin
Password: admin

admin$ chmod testfile.txt 0666
# Expected: Should work (admin has chmod privileges)
```

### Test 8: Write Permission Testing
```bash
admin$ chmod testfile.txt 0444  # Read-only
admin$ echo "should fail" > testfile.txt
# Expected: Write should fail even for owner

admin$ chmod testfile.txt 0644  # Restore write
admin$ echo "should work" > testfile.txt  
# Expected: Write should succeed
```

## 🖥️ Testing Enhanced Shell Features

### Test 9: Command History
```bash
admin$ ls
admin$ whoami
admin$ ps
# Press UP arrow key
# Expected: Shows previous command (ps)
# Press UP arrow again  
# Expected: Shows whoami
# Press DOWN arrow
# Expected: Shows ps again
```

### Test 10: History Command
```bash
admin$ history
# Expected: Shows numbered list of previous commands
```

### Test 11: Tab Completion
```bash
admin$ wh<TAB>
# Expected: Completes to "whoami"

admin$ ps<TAB>
# Expected: Completes to "ps" 

admin$ mk<TAB>
# Expected: Completes to "mkdir"
```

### Test 12: Clear Command
```bash
admin$ clear
# Expected: Screen clears, cursor at top
```

### Test 13: User-Specific Prompts
```bash
admin$ # Should show "admin$"
admin$ logout

Username: user1
Password: pass1
user1$ # Should show "user1$"

user1$ logout
Username: user2  
Password: pass2
user2$ # Should show "user2$"
```

## ⚙️ Testing MLFQ Scheduler

### Test 14: Process Monitoring
```bash
admin$ ps
# Expected: Shows process list with PID, STATE, PRI, TICKS, RUNTIME, NAME
# Example output:
# PID  STATE   PRI  TICKS  RUNTIME  NAME
# ---  ------  ---  -----  -------  ----
# 1    run     0    0      245      init
# 2    run     0    0      12       sh
```

### Test 15: CPU-Bound Process Testing
```bash
admin$ cpubound &
# Expected: Process starts in background

admin$ ps
# Expected: Shows cpubound process, initially at priority 0
# Wait a few seconds, then run ps again
# Expected: cpubound should be demoted to priority 2
```

### Test 16: I/O-Bound Process Testing  
```bash
admin$ iobound &
# Expected: Process starts with I/O operations

admin$ ps
# Expected: iobound should maintain priority 0 or 1 (not demoted to 2)
```

### Test 17: Mixed Workload Testing
```bash
admin$ mixed &
# Expected: Process alternates between CPU and I/O

admin$ ps  
# Expected: mixed should be at priority 1 (medium)
```

### Test 18: Comprehensive MLFQ Test
```bash
admin$ mlfqtest
# Expected: Detailed output showing:
# - Multiple processes spawning
# - CPU-bound processes completing quickly
# - I/O-bound processes with sleep intervals  
# - Mixed workload alternating phases
# - Fair scheduling demonstration
```

### Test 19: Priority Boost Verification
```bash
# Run multiple CPU-bound processes
admin$ cpubound &
admin$ cpubound &
admin$ ps
# Expected: Both should eventually be at priority 2

# Wait for priority boost (occurs every 1000 ticks)
# Run ps again after some time
# Expected: Processes should be boosted back to priority 0
```

## 🔄 Testing System Utilities

### Test 20: Reboot Command
```bash
admin$ reboot
# Expected: System restarts, returns to login screen
```

### Test 21: Multiple User Sessions
```bash
# Test concurrent user operations
admin$ echo "admin file" > admin_file.txt
admin$ logout

Username: user2
Password: pass2
user2$ echo "user2 file" > user2_file.txt
user2$ cat admin_file.txt
# Expected: Should work (read access)

user2$ echo "edit" >> admin_file.txt  
# Expected: May fail depending on permissions
```

## 🧪 Advanced Testing Scenarios

### Test 22: System Stress Test
```bash
admin$ cpubound &
admin$ iobound &
admin$ mixed &
admin$ cpubound &
# Run multiple processes simultaneously

admin$ ps
# Expected: Fair distribution across priority levels
# System should remain responsive
```

### Test 23: Permission Edge Cases
```bash
admin$ echo "test" > edgecase.txt
admin$ chmod edgecase.txt 0000  # No permissions
admin$ cat edgecase.txt
# Expected: Should fail (no read permission)

admin$ chmod edgecase.txt 0644  # Restore permissions
admin$ cat edgecase.txt
# Expected: Should work
```

### Test 24: Shell Feature Combinations
```bash
admin$ ls
admin$ whoami  
admin$ ps
# Use UP arrow to navigate history
# Use TAB completion on various commands
# Test clear command
# Verify user prompt consistency
```

## 📊 Expected Results Summary

### ✅ Authentication System
- ✓ Valid logins succeed with appropriate prompts
- ✓ Invalid logins fail with error messages  
- ✓ User switching works correctly
- ✓ whoami shows correct user information

### ✅ File Permissions
- ✓ Files have proper ownership tracking
- ✓ Permission checks enforce access control
- ✓ chmod works for admin users only
- ✓ Read-only users cannot write files

### ✅ Shell Enhancements  
- ✓ Command history navigable with arrow keys
- ✓ Tab completion works for commands
- ✓ Clear command clears screen
- ✓ User-specific prompts display correctly

### ✅ MLFQ Scheduler
- ✓ CPU-bound processes demoted to low priority
- ✓ I/O-bound processes maintain high priority
- ✓ Mixed workloads get medium priority
- ✓ Priority boost prevents starvation
- ✓ ps command shows real-time priority information

### ✅ System Integration
- ✓ All features work together seamlessly
- ✓ System remains stable under load
- ✓ No conflicts between enhancements
- ✓ Backward compatibility maintained

## 🐛 Troubleshooting

### Common Issues and Solutions

**Issue**: Login not working
- **Solution**: Ensure correct username/password (case-sensitive)
- **Check**: admin/admin, user1/pass1, user2/pass2

**Issue**: Permission denied errors
- **Solution**: Check current user with `whoami`
- **Note**: user1 has read-only access

**Issue**: MLFQ not showing priority changes
- **Solution**: Run CPU-intensive processes and wait a few seconds
- **Check**: Use `ps` command to monitor changes

**Issue**: Shell features not working
- **Solution**: Ensure you're using the enhanced shell
- **Check**: Look for user-specific prompts (admin$, user1$, user2$)

## 📝 Test Checklist

Use this checklist to verify all features:

- [ ] Admin login works
- [ ] User1 login works  
- [ ] User2 login works
- [ ] Invalid login fails
- [ ] whoami shows correct user
- [ ] File creation works
- [ ] Permission checking works
- [ ] chmod works for admin
- [ ] chmod fails for non-admin
- [ ] Command history works
- [ ] Tab completion works
- [ ] Clear command works
- [ ] User prompts correct
- [ ] ps command shows priorities
- [ ] CPU-bound processes demoted
- [ ] I/O-bound processes stay high priority
- [ ] Mixed workload gets medium priority
- [ ] mlfqtest runs successfully
- [ ] System remains responsive
- [ ] Reboot works
- [ ] All features integrate properly

## 🎯 Performance Expectations

- **Login time**: < 1 second
- **Command response**: Immediate for simple commands
- **Process switching**: Smooth, no noticeable delays
- **File operations**: Fast, with proper permission checking
- **MLFQ scheduling**: Fair distribution, responsive system
- **Memory usage**: Minimal overhead from enhancements

This comprehensive testing ensures all XV6 enhancements work correctly and provide the intended educational and practical value.