#!/bin/bash

copy_passwd_group_to_home() {
    cp /etc/{passwd,group} ~/
    echo "Files /etc/passwd and /etc/group copied to the home directory."
}

create_hello_txt() {
    echo "hello world" > hello.txt
    echo "File hello.txt created with content 'hello world'."
}

copy_using_cp_terminal() {
    cp /dev/terminal hello.txt
    echo "File hello.txt created with content 'hello world' using 'cp' with 'terminal' as source file."
}

explore_dev() {
    echo "Available devices in /dev:"
    ls -l /dev

    echo "Character-oriented devices:"
    find /dev -type c

    echo "Block-oriented devices:"
    find /dev -type b

    echo "Your tty (terminal) device:"
    tty
    echo "Owner of your tty device:"
    ls -l $(tty)
}

explain_ls_options() {
    echo "Listing contents of directory 'play' with 'ls -l':"
    ls -l play

    echo "Listing contents of directory 'play' with 'ls -L':"
    ls -L play
}

delete_all_files_in_other_dir() {
    echo "Enter the directory path:"
    read directory

    if [ -d "$directory" ]; then
        cd "$directory" || exit
        echo "Attempting to delete all files in $directory..."
        rm -rf *
        echo "All files deleted in $directory."
    else
        echo "Directory '$directory' not found."
    fi
}

find_files_bigger_than_1MB() {
    echo "Files bigger than 1MB in the system:"
    find / -type f -size +1M
}

grep_my_login_details() {
    echo "Line in /etc/passwd containing your login details:"
    grep $(whoami) /etc/passwd
}

test_regular_expression() {
    cat << EOF > regex_test_file.txt
1234abc
98765xyz
12345
abcdefg
none
EOF

    echo "Lines that match the regular expression: (^[0-9]{1,5}[a-zA-z ]+$)|none"
    egrep "(^[0-9]{1,5}[a-zA-z ]+$)|none" regex_test_file.txt

    echo "Lines that do not match the regular expression:"
    egrep -v "(^[0-9]{1,5}[a-zA-z ]+$)|none" regex_test_file.txt
}

show_executing_process() {
    ps aux | sed "s/$(whoami)/me/g"
}

list_processes_with_sed() {
    ps aux | sed "s/$(whoami)/me/g"
}

while true; do
    echo "Menu:"
    echo "11. Copy /etc/passwd and /etc/group into the home directory in one command"
    echo "12. Create a file called hello.txt that contains the words 'hello world'"
    echo "13. Copy using 'cp' with 'terminal' as the source file"
    echo "14. Explore /dev and identify devices"
    echo "15. Explain the difference between listing directory contents with 'ls -l' and 'ls -L'"
    echo "16. Change into a directory that does not belong to you and try to delete all files"
    echo "17. Use find to display the names of all files in the system that are bigger than 1MB"
    echo "18. Use grep to isolate the line in /etc/passwd that contains your login details"
    echo "19. Create a file containing lines that match and do not match a given regular expression and use egrep to check"
    echo "20. List all your processes, using sed to substitute 'me' for your username"
    echo "21. Exit"
    read choice

    case $choice in
        11) copy_passwd_group_to_home ;;
        12) create_hello_txt ;;
        13) copy_using_cp_terminal ;;
        14) explore_dev ;;
        15) explain_ls_options ;;
        16) delete_all_files_in_other_dir ;;
        17) find_files_bigger_than_1MB ;;
        18) grep_my_login_details ;;
        19) test_regular_expression ;;
        20) list_processes_with_sed ;;
        21) echo "Exiting..."; exit ;;
        *) echo "Invalid option";;
    esac
done
