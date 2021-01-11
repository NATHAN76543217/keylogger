# keylogger
A linux keylogger srcipt

This scipts is in two part:
- C scripts for keyloggin
- Bash scripts for keylogger implentation in system

## Detections scripts
	detect2.sh is a bash script thats test 'kill' on every pid to detect hidden process
## procsHides.so
- procsHides.so: shared lib thats override libc functions.
	- readdir
	- kill
## Asking permission
	first program display popup for requiring password
## Persistance
	(Comming soon)
	Next, program install keylogger in filesystem for persist after reboot and auto-run at lunch.
## Read keyboards input
	Then, program select and read eventX file for get keyboard stream.
## Display
	In last, program write an save_line.log file with all data parsed.
## Dissimiluation
	Process is hidden for every call to readdir (ls, ps, top, lsof etc...)
	Process can not be detect by bruteforce scanning on kill return value
### suggestion ?
	Contact me at: lecaille.nathan@outlook.com.
