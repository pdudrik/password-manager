# Loctopus
Easy CLI (C based) local password manager.

# Start
Within project directory:
```
mkdir build
cd build
cmake ..
make
```

It will make executable file ```./run``` after which you can pass params and commands like bellow.

# Params
-p, --password=PASSWORD     Enter your password
-s, --service=SERVICE       Enter the service from which are those credentials
-u, --username=USERNAME     Enter your username

# Commands
- show list - list all credentials (only services)
- show [service] - show credentials for specific service

# Agenda
1. Check for memory leaks and erros via valgrind
