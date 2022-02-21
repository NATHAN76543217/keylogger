# keylogger
A linux keylogger script

This scipts composed of three parts:
- C scripts for keylog
- Bash scripts for keylogger implentation in system
- A shared library to hide process by overwritting libc

## Makefile
make all: compile program
make debug: compile program in not furtive mode
## Detections scripts
	detect2.sh is a bash script thats test 'kill' on every pid to detect hidden process
## procsHides.so
- procsHides.so: shared lib thats override libc functions.
	- readdir
	- kill
## Asking permission
	first program display popup for requiring password
## Persistance
	Once init.sh was run, keylogger is implemented in filesystem as service. Its start automatically on boot.
## Read keyboards input
	Then, program select and read eventX file for get keyboard stream.
## Display
	In last, program write an save_line.log file with all data parsed.
## Dissimiluation
	Process is hidden for every call to readdir (ls, ps, top, lsof etc...)
	Process can not be detect by bruteforce scanning on kill return value
### suggestion ?
	Contact me at: lecaille.nathan@outlook.com.
