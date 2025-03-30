// SPDX-License-Identifier: GPL-3.0-only
/*
 * Kernel module to monitor kill() syscall usage
 * 
 * Logs information about processes attempting to kill other processes
 * 
 * Copyright (C) 2025 EntasaDev
 * 
 * Uses Linux kernel headers:
 * Copyright (C) Linux kernel authors (see kernel sources for full copyright info)
 * Licensed under GPL-2.0-only WITH Linux-syscall-note
 * 
 */

 #include <linux/kernel.h>
 #include <linux/module.h>
 #include <linux/kprobes.h>
 
 MODULE_LICENSE("GPL v3");
 MODULE_AUTHOR("EntasaDev");
 MODULE_DESCRIPTION("Monitor kill() system calls");
 MODULE_VERSION("0.1");
 
 static struct kprobe kp = {
     .symbol_name = "__x64_sys_kill",
 };

 static int handler_pre(struct kprobe *p, struct pt_regs *regs)
 {
     pid_t target_pid = (pid_t)regs->di;
     pr_info("Process %d will be killed by process %s (PID: %d)\n", 
             target_pid, current->comm, current->pid);
     return 0;
 }
 
 static int __init kprobe_init(void)
 {
     int ret;
     kp.pre_handler = handler_pre;
     ret = register_kprobe(&kp);
     if (ret < 0) {
         pr_err("Failed to register kprobe\n");
         return ret;
     }
     
     pr_info("Kill syscall monitor module loaded\n");
     return 0;
 }

 static void __exit kprobe_exit(void)
 {
     unregister_kprobe(&kp);
     pr_info("Kill syscall monitor module unloaded\n");
 }

 module_init(kprobe_init);
 module_exit(kprobe_exit);


 