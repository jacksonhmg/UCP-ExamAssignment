# Open this folder directly. Enter in command line: "bash Task1.sh logfile.txt". 
#'$1' represents the third command line input which is 'logfile.txt'. The first half before '$1' is checking if the line has an entry after 08:53:00, the second half is checking if it has an IPV4 address. 
# The structure of the '|' and multiple greps works as an AND condition
grep '08:5[3-4]:[0-5][0-9]' $1 | egrep '[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}\.[[:digit:]]{1,3}'