#!/bin/bash

search_files_by_name() {
    echo "Files in the subtree of /usr/include with names of length 5-7 characters (excluding .h suffix):"
    find /usr/include -type f -name '*.h' -exec basename {} \; | grep -E '^.{5,7}\.h$' | sed 's/\.h$//'
}

search_files_containing_printf() {
    echo "Files in the subtree of /usr/include containing the string 'printf':"
    grep -r -l "printf" /usr/include/*
}

delete_line_from_file() {
    echo "Enter the file name:"
    read filename
    echo "Enter the line number to delete:"
    read line_number

    if [ -f "$filename" ]; then
        sed -i "${line_number}d" "$filename"
        echo "Line $line_number deleted from $filename."
    else
        echo "File '$filename' not found."
    fi
}

reverse_parameters() {
    echo "Enter parameters separated by spaces:"
    read -a params

    reversed_params=""
    for ((i=${#params[@]}-1; i>=0; i--)); do
        reversed_params+=" ${params[i]}"
    done

    echo "Reversed parameters: $reversed_params"
}

output_every_tenth_line() {
    echo "Enter the input:"
    awk 'NR % 10 == 0' -
}

add_sum_column_to_csv() {
    echo "Enter the CSV file name:"
    read filename

    if [ -f "$filename" ]; then
        awk -F ',' 'BEGIN { OFS = "," } { if (NR == 1) print $0, "Sum"; else { sum = 0; for (i = 2; i <= NF; i++) sum += $i; print $0, sum } }' "$filename"
    else
        echo "File '$filename' not found."
    fi
}

print_seconds_since_unix_epoch() {
    awk 'BEGIN { srand(); print "Number of seconds since beginning of UNIX era:", srand() }'
}

compute_average() {
    sum=0
    count=0
    for num in "$@"; do
        sum=$(expr $sum + $num)
        count=$(expr $count + 1)
    done
    average=$(expr $sum / $count)
    echo "Average: $average"
}

create_and_delete_file_with_hash() {
    echo "Creating a file that begins with the symbol #"
    touch '#filename.txt'
    echo "File created: #filename.txt"

    echo "Files in the current directory:"
    ls -l

    echo "Do you want to delete the file? (y/n)"
    read confirm_delete
    if [ "$confirm_delete" == "y" ]; then
        rm '#filename.txt'
        echo "File deleted: #filename.txt"
    else
        echo "File not deleted."
    fi
}

perform_brace_expansion() {
    echo "Output of the command: echo {con,pre}{sent,fer}{s,ed}"
    echo {con,pre}{sent,fer}{s,ed}
}

while true; do
    echo "Menu:"
    echo "1. Search for files in the subtree of /usr/include by name"
    echo "2. Search for files in the subtree of /usr/include containing the string 'printf'"
    echo "3. Delete a specific line from a given file"
    echo "4. Reverse parameters and write to standard output"
    echo "5. Output every tenth line of the input using AWK"
    echo "6. Add a new column 'Sum' to a CSV file containing the sum of the number fields"
    echo "7. Print the number of seconds since the beginning of the UNIX era and terminate"
    echo "8. Compute the average value of numeric parameters and write the result to standard output"
    echo "9. Create and delete a file that begins with the symbol #"
    echo "10. Perform brace expansion and display the result"
    echo "11. Exit"
    read choice

    case $choice in
        1) search_files_by_name ;;
        2) search_files_containing_printf ;;
        3) delete_line_from_file ;;
        4) reverse_parameters ;;
        5) output_every_tenth_line ;;
        6) add_sum_column_to_csv ;;
        7) print_seconds_since_unix_epoch; exit ;;
        8) echo "Enter numeric parameters separated by spaces:"
           read -a params
           compute_average "${params[@]}" ;;
        9) create_and_delete_file_with_hash ;;
        10) perform_brace_expansion ;;
        11) echo "Exiting..."; exit ;;
        *) echo "Invalid option";;
    esac
done
