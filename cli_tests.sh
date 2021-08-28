#!/usr/bin/expect -f
# 01
# check command line error handling
# ***************************************************
# you may edit the following variables
#      error message when no arguments are provided
set noArguments "Missing argument"
#     error message when strategy name is wrong
set wrongStrategy "Unknown search strategy unknown_search_strategy"
# ****************************************************
# Do NOT edit anything below this point

set timeout -1
set programName "library"
set output "init"

# no arguments
try {
set output [exec ./$programName]
} trap CHILDSTATUS {} {}
if {[regexp -nocase $noArguments $output]} {
    puts "1) Command line error handling: No arguments ;-)"
} else {
    puts "1) Command line error handling: No arguments :-("
}

# no valid search strategy
try {
set output [exec ./$programName unknown_search_strategy tests]
} trap CHILDSTATUS {} {}
if {[regexp -nocase $wrongStrategy $output]} {
    puts "2) Command line error handling: Bad strategy ;-)"
} else {
    puts "2) Command line error handling: Bad strategy :-("
}

puts "3) Script end. ;-)"
