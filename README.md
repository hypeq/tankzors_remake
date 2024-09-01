Screenshots

![image](https://github.com/user-attachments/assets/4f7c2035-8499-4e21-9571-dcb74a05df65)
![image](https://github.com/user-attachments/assets/21c22905-2b9f-43c0-a689-7b75af4966f5)

Building and running

  Linux:
  
    for Arch Linux based (example):  
    
    Install depencies on your system
    pacman -Sy git gcc sdl2 sdl2_image sdl2_mixer sdl2_ttf 
    
    Clone repository
    git clone https://github.com/hypeq/tankzors_remake
    
    Compile using make script
    cd tankzors_remake/src
    make -j$(nproc)
    
    Running
    cd ..
    ./tankzors # or run in your file explorer
    
