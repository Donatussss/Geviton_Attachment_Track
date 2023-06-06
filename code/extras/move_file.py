# A small script to copy arduino files from their folders to the repo
import os
import sys
import shutil
    
os.chdir('..\\..\\..\\')
try:
    src_folder = f'code\\{sys.argv[1]}'
    dst_folder = f'Geviton_Attachment_Track\\code\\{sys.argv[2]}'
    dst_file_list = os.listdir(dst_folder)
except:
    print(f'Usage: move_file.py wk1\\day2 wk1\\day2')

for src_folder_name in os.listdir(src_folder):
    # need to check if file exists
    dst_file_name = f'{dst_folder}\\{src_folder_name}.ino'
    if dst_file_name not in dst_file_list:
        shutil.copy(f'{src_folder}\\{src_folder_name}\\{src_folder_name}.ino', dst_file_name)
