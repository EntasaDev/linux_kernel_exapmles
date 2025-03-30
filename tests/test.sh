#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

if [ "$EUID" -ne 0 ]; then
    echo -e "${RED}Start with root privileges!${NC}"
    exit 1
fi

check_module() {
    if ! lsmod | grep -q syscall_monitor; then
        echo -e "${RED}syscall_monitor module not loaded!${NC}"
        exit 1
    fi
}

run_python_test() {
    if ! command -v python3 &>/dev/null; then
        echo -e "${RED}Python3 not found!${NC}"
        return
    fi

    if [ ! -f "killer.py" ]; then
        echo -e "${RED}killer.py not found in current directory${NC}"
        return
    fi
    sleep 1
    python3 killer.py
}

echo -e "${GREEN}Test...${NC}"

run_python_test

echo -e "${GREEN}Test is ended!${NC}"
echo -e "$(dmesg | tail -5 )"