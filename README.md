# Building and running

## Linux:
**1. Install depencies:**  
  
Arch-based:
```
 pacman -Sy git gcc sdl2 sdl2_image sdl2_mixer sdl2_ttf
```
Debian-based:
```
 apt install git gcc libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```
**2. Clone repository:**
```
 git clone https://github.com/hypeq/tankzors_remake.git
```
**3. Build:**
```
 cd tankzors_remake/src
 make -j$(nproc)
``` 

**4. Run:**
```
 cd ..
 ./tankzors
```
# Screenshots
![image](https://github.com/user-attachments/assets/4f7c2035-8499-4e21-9571-dcb74a05df65)
![image](https://github.com/user-attachments/assets/21c22905-2b9f-43c0-a689-7b75af4966f5)
