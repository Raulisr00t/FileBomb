# File Bomb For Windows

## Repository Description: File Bomb Utility (Windows Disk Filler) 💣

This repository contains a Windows-based file bomb utility designed to fill up all available disk space by creating a massive file in the system's temporary folder. The program utilizes the Windows API (CreateFileA, WriteFile, GetTempPathA, GetDiskFreeSpaceExA) to dynamically detect available disk space and continuously write data until the disk is full.

## 💡 Features
1.Detects available disk space automatically (DetectDiskSpace())
2.Creates a random file name using GetRandomFileName()
3.Writes data in 1MB chunks until the disk is full (CreateTempFile())
4.Handles disk full errors (ERROR_DISK_FULL - 112) gracefully
5.Uses the system's temp folder (C:\Users\%USERNAME%\AppData\Local\Temp)

## 🛠️ How It Works
1.Detects the available free space on disk (C:\).
2.Generates a random filename (abc123.txt) inside the temp folder.
3.Creates the file and starts writing 'A' characters in 1MB chunks.
4.Continues writing until the disk is completely full.
5.Stops when Windows prevents further writes (ERROR_DISK_FULL).
6.Prints the final file path and actual written size.

## 🚀 Usage
### Compile and Run
```powershell
gcc FileBomb.c -o FileBomb.exe
FileBomb.exe
```

### 💀 Potential Risks
System may slow down significantly or crash
Some programs might stop working due to lack of disk space
Could cause unexpected system errors or corruption if run on an OS drive

## 📢 Legal Notice
This tool is strictly for educational purposes. The author does not take responsibility for any damages caused by running this program. Use responsibly. 🚀
