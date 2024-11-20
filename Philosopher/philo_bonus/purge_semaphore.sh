#!/bin/bash

semaphores=(
	"fork"
	"fork_access"
	"print"
)

for semaphore in "${semaphores[@]}"; do
	rm "/dev/shm/sem.${semaphore}"
	if [ $? -eq 0 ]; then
		echo -e "\033[1;92mSemaphore sem.${semaphore} deleted successfully\033[0m"
	else
		echo -e "\033[1;31mSemaphore sem.${semaphore} failed to delete\033[0m"
	fi
done