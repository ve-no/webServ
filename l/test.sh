#!/bin/bash

RED_BOLD='\033[1;31m'
GREEN_BOLD='\033[1;32m'
YELLOW_BOLD='\033[1;33m'
BLUE_BOLD='\033[1;34m'
MAGENTA_BOLD='\033[1;35m'
CYAN_BOLD='\033[1;36m'
WHITE_BOLD='\033[1;37m'
RESET='\033[0m'

echo -e "${YELLOW_BOLD}Which program would you like to use for testing: ${RESET}"
echo -en "${YELLOW_BOLD}[1 - telnet] : ${RESET}"
read PROGRAM

if [ $PROGRAM -eq 1 ]; then
	./tests/telnet/telnet_test.sh
fi