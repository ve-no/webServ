#!/bin/sh

RED_BOLD='\033[1;31m'
GREEN_BOLD='\033[1;32m'
YELLOW_BOLD='\033[1;33m'
BLUE_BOLD='\033[1;34m'
MAGENTA_BOLD='\033[1;35m'
CYAN_BOLD='\033[1;36m'
WHITE_BOLD='\033[1;37m'
RESET='\033[0m'

# This script tests the telnet server by connecting to it and sending
URI="127.0.0.1"

echo -n "${YELLOW_BOLD}Enter the port number: ${RESET}"
read PORT
echo -n "${YELLOW_BOLD}Which method do you want to test? [1 - GET] [2 - POST] [3 - DELETE]: ${RESET}"
read METHOD

echo -n "${GREEN_BOLD}Testing webserv on port $PORT${RESET}\n"

if [ $METHOD -eq 1 ]; then
	echo "${BLUE_BOLD}Testing GET method${RESET}"
	telnet $URI $PORT < ./tests/telnet/telnet_get.re
	echo "${GREEN_BOLD}Finished testing${RESET}"
elif [ $METHOD -eq 2 ]; then
	echo "${BLUE_BOLD}Testing POST method${RESET}"
	telnet $URI $PORT < ./tests/telnet/telnet_post.re
	echo "${GREEN_BOLD}Finished testing${RESET}"
elif [ $METHOD -eq 3 ]; then
	echo "${BLUE_BOLD}Testing DELETE method${RESET}"
	telnet $URI $PORT < ./tests/telnet/telnet_delete.re
	echo "${GREEN_BOLD}Finished testing${RESET}"
else
	echo "${RED_BOLD}Invalid method${RESET}"
fi
