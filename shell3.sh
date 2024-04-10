#!/bin/bash

list_empty_files() {
    directory=$1
    empty_files=$(find "$directory" -type f -empty)
    if [ -n "$empty_files" ]; then
        echo "Empty files found:"
        echo "$empty_files"
    else
        echo "No empty files found."
    fi
}

delete_files() {
    file_list=$1
    for file_path in $file_list; do
        rm "$file_path"
        echo "Deleted: $file_path"
    done
}

get_total_memory_usage() {
    total_memory=$(free -h | awk 'NR==2{print $2}')
    echo "Total memory usage: $total_memory"
}

get_file_memory_usage() {
    file_path=$1
    if [ -f "$file_path" ]; then
        memory_usage=$(du -h "$file_path" | awk '{print $1}')
        echo "Memory usage of $file_path: $memory_usage"
    else
        echo "File $file_path not found."
    fi
}

while true; do
    echo ""
    echo "1. List Empty Files"
    echo "2. Delete Empty Files"
    echo "3. Get Total Memory Usage"
    echo "4. Get Memory Usage of a File"
    echo "5. Exit"
    echo ""

    read -p "Enter your choice: " choice

    case $choice in
        1)
            read -p "Enter the directory path: " directory
            list_empty_files "$directory"
            ;;
        2)
            read -p "Enter the directory path: " directory
            empty_files=$(find "$directory" -type f -empty)
            if [ -n "$empty_files" ]; then
                echo "Empty files found:"
                echo "$empty_files"
                read -p "Are you sure you want to delete $(echo "$empty_files" | wc -w) empty files? (yes/no): " confirmation
                if [ "$confirmation" = "yes" ]; then
                    delete_files "$empty_files"
                fi
            else
                echo "No empty files found to delete."
            fi
            ;;
        3)
            get_total_memory_usage
            ;;
        4)
            read -p "Enter the file path: " file_path
            get_file_memory_usage "$file_path"
            ;;
        5)
            echo "Exiting..."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please enter a valid option."
            ;;
    esac
done
