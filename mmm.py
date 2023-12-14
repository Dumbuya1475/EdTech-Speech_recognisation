import os

def play_music():
    # Replace 'your_music_file.mp3' with the actual path and filename of your music file
    music_file_path = r'C:\\Users\\Suber\\Downloads\play music
    \Alan Walker.mp3'

    # Command to play music using the default music player on Windows
    command = f'start {music_file_path}'

    # Execute the command
    os.system(command)

# Example usage
user_input = input("Enter a command: ")
if user_input.lower() == 'play music':
    play_music()
