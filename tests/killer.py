import os, signal
pid = os.getpid()
os.kill(pid,signal.SIGTERM)
