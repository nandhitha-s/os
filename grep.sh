#!/bin/bash

search_files_by_name() {
    echo "Files in the subtree of /usr/include with names of length 5-7 characters (excluding .h suffix):"
    find /usr/include -type f -name '*.h' -exec basename {} \; | grep -E '^.{5,7}\.h$' | sed 's/\.h$//'
}


search_files_containing_printf() {
    echo "Files in the subtree of /usr/include containing the string 'printf':"
    grep -r -l "printf" /usr/include/*
}

while true; do
    echo "Menu:"
    echo "1. Search for files in the subtree of /usr/include by name"
    echo "2. Search for files in the subtree of /usr/include containing the string 'printf'"
    echo "3. Exit"
    read choice

    case $choice in
        1) search_files_by_name ;;
        2) search_files_containing_printf ;;
        3) echo "Exiting..."; exit ;;
        *) echo "Invalid option";;
    esac
done
