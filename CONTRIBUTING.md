# Contributing to XV6 User Authentication

Thank you for your interest in contributing to this project! This is an educational implementation of user authentication and file permissions for XV6.

## 🎯 Project Goals

This project aims to:
- Demonstrate OS security concepts
- Provide a learning resource for authentication systems
- Show practical implementation of file permissions
- Maintain code clarity for educational purposes

## 🤝 How to Contribute

### Reporting Bugs

If you find a bug:
1. Check if it's already reported in [Issues](../../issues)
2. Create a new issue with:
   - Clear description of the bug
   - Steps to reproduce
   - Expected vs actual behavior
   - Your environment (OS, compiler version)
   - Relevant logs or screenshots

### Suggesting Enhancements

For feature requests:
1. Check existing issues and documentation
2. Create an issue describing:
   - The enhancement
   - Why it would be useful
   - How it might work
   - Any potential drawbacks

### Code Contributions

#### Before You Start
1. Fork the repository
2. Create a new branch: `git checkout -b feature/your-feature-name`
3. Read the [IMPLEMENTATION_DETAILS.txt](docs/IMPLEMENTATION_DETAILS.txt)

#### Coding Standards
- Follow XV6's existing code style
- Use clear, descriptive variable names
- Add comments for complex logic
- Keep functions small and focused
- Test thoroughly before submitting

#### Making Changes
1. Make your changes
2. Test with: `make clean && make && make qemu-nox`
3. Verify all existing features still work
4. Add documentation for new features
5. Update CHANGELOG.md

#### Submitting Pull Requests
1. Commit with clear messages: `git commit -m "Add feature: description"`
2. Push to your fork: `git push origin feature/your-feature-name`
3. Create a Pull Request with:
   - Clear description of changes
   - Why the changes are needed
   - How you tested them
   - Any breaking changes

## 🧪 Testing

### Required Tests
Before submitting, verify:
- [ ] System builds without errors
- [ ] All three users can login
- [ ] File permissions work correctly
- [ ] New features don't break existing ones
- [ ] Error messages are clear
- [ ] Documentation is updated

### Test Commands
```bash
make clean
make
make qemu-nox

# Test basic functionality
Username: admin
Password: admin
admin$ whoami
admin$ echo "test" > file.txt
admin$ chmod file.txt 1
admin$ echo "fail" >> file.txt
admin$ logout

# Test other users
Username: user1
Password: pass1
user1$ echo "test" > file.txt  # Should fail
```

## 📝 Documentation

### Required Documentation
- Update README.md if adding features
- Add entry to CHANGELOG.md
- Update relevant docs in docs/ folder
- Add code comments for complex logic

### Documentation Style
- Clear and concise
- Include examples
- Explain why, not just what
- Use proper formatting

## 🎓 Educational Focus

Remember this is an educational project:
- Prioritize clarity over optimization
- Add explanatory comments
- Keep implementations simple
- Document design decisions

## 🚫 What Not to Contribute

Please avoid:
- Overly complex implementations
- Features that obscure learning goals
- Breaking changes without discussion
- Removing educational comments
- Production-grade security (this is for learning)

## 💡 Ideas for Contributions

### Easy
- Fix typos in documentation
- Add more test cases
- Improve error messages
- Add code comments

### Medium
- Implement password hashing
- Add more user management commands
- Improve tab completion
- Add command history

### Hard
- Implement group permissions
- Add persistent user database
- Implement sudo command
- Add audit logging

## 🔍 Code Review Process

1. Maintainer reviews PR
2. Feedback provided if needed
3. Changes requested or approved
4. Merged when ready

## 📞 Getting Help

- Check [documentation](docs/)
- Review [IMPLEMENTATION_DETAILS.txt](docs/IMPLEMENTATION_DETAILS.txt)
- Ask questions in Issues
- Be patient and respectful

## 🙏 Recognition

Contributors will be:
- Listed in README.md
- Credited in commit history
- Appreciated for their work!

## 📜 License

By contributing, you agree that your contributions will be licensed under the same license as the project (MIT License, same as XV6).

## ✨ Thank You!

Every contribution helps make this a better learning resource. Thank you for your time and effort!

---

**Questions?** Open an issue or check the [documentation](docs/).
