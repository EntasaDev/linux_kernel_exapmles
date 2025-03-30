# Kill Syscall Monitor

A Linux kernel module that monitors `kill()` system call usage using kprobes. Logs information about processes attempting to kill other processes.
## Installation
```bash
make
sudo insmod syscall_monitor.ko
```
## Tests 

```bash
chmod +x test.sh
sudo ./test.sh
```

## License  
This project is licensed under the **GNU GPL v3.0**. See [LICENSE](LICENSE) for details. 
