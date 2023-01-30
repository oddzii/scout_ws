#!/bin/bash

# Store the ubuntu username and password in variables
username="mclab"
password="egat"

# Store the remote Windows server's username and password in variables
remote_username='bbrobotics'
remote_password='u6sk^7FuKF!n'

# Store the address of the remote PC in a variable
remote_pc="192.168.99.14"

# Store the share name in a variable
sharename="image_data"

# Get the current date and time
now=$(date +"%d-%m-%Y_%H")

# Construct the remote folder name
remote_folder="$now"

# Store the local folder in a variable
local_folder="/home/mclab/Database/pic"

# Get a list of all files in the local folder
files=$(ls $local_folder)

# Iterate through the list of files
for file in $files; do
# Send the file to the remote PC
  smbclient -d //$remote_pc/$sharename -U $username%$password -c "mkdir $remote_folder; put $local_folder/$file $remote_folder/$file -W $remote_username -U $remote_username%$remote_password; quit"

# Check if the file was sent successfully
if [ $? -eq 0 ]; then
# If the file was sent successfully, remove it from the local folder
  #rm "$local_folder/$file"
  echo "The file $file has been sent and deleted."
else
  echo "The file $file has not been sent."
fi
done
