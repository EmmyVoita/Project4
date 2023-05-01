#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>



using namespace std;
namespace fs = std::filesystem;



void CreateDirectory() 
{
    string directoryName;
    cout << "Please enter directory name: ";
    cin >> directoryName;

    //try to create the directory
    int status = mkdir(directoryName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    if (status == 0) 
        cout << "Directory successfully created." << endl; 
    else 
        cout << "Error creating directory." << endl;
}





void RenameDirectory()
{
    string oldName, newName;
    cout << "Enter the old directory name: ";
    cin >> oldName;
    cout << "Enter the new directory name: ";
    cin >> newName;

    int status = rename(oldName.c_str(), newName.c_str());

    if (status == 0) 
        cout << "Directory renamed successfully." << endl;
    else 
        cout << "Error renaming directory." << endl;
    
}




void delete_directory_recursive(const std::string& dir)
{
    DIR* d = opendir(dir.c_str());
    if (!d) {
        cerr << "Error opening directory " << dir << std::endl;
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(d)) != NULL) {
        std::string path = dir + "/" + entry->d_name;
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            delete_directory_recursive(path);
        } else {
            remove(path.c_str());
        }
    }

    closedir(d);
    int status = rmdir(dir.c_str());
    if (status == 0) {
        std::cout << "Directory " << dir << " deleted successfully." << std::endl;
    } else {
        std::cerr << "Error deleting directory " << dir << std::endl;
    }
}



void DeleteDirectory()
{
    std::string dirname;
    std::cout << "Enter directory name: ";
    std::cin >> dirname;

    delete_directory_recursive(dirname);
}


void CreateFile() 
{
    string filename;
    cout << "Enter the filename: ";
    cin.ignore(); 
    getline(std::cin, filename);

    string directory;
    cout << "Enter the path to the directory: ";
    getline(std::cin, directory);


    ofstream file(directory + "/" + filename);
    if (file.is_open()) {
        std::cout << "File created successfully." << std::endl;
        file.close();
    }
    else {
        std::cerr << "Error creating file." << std::endl;
    }
}



void CreateFile(std::string path) 
{
    string filename;
    cout << "Enter the filename: ";
    cin.ignore(); 
    getline(cin, filename);
    ofstream file(path + "/" + filename);
    if (file.is_open()) {
        cout << "File created successfully." << endl;
        file.close();
    }
    else {
        cerr << "Error creating file." << endl;
    }
}


void RenameFile() 
{
    string oldName, newName;
    cout << "Entername of the file to rename: ";
    cin >> oldName;
    cout << "Enter the new name for the file: ";
    cin >> newName;

    if (rename(oldName.c_str(), newName.c_str()) != 0) 
        cerr << "Error renaming file." << endl;
    else 
        cout << "File renamed successfully." << endl;
}

void EditFile() 
{
    string fileName;
    cout << "Enter the name of the file to edit: ";
    cin >> fileName;

    ofstream file(fileName.c_str());

    if (!file.is_open()) 
    {
        cerr << "Error opening file." << endl;
        return;
    }

    cout << "(press Ctrl-D to finish) Enter the text you want to write:" << endl;
    string line;
    while (getline(cin, line)) 
    {
        file << line << endl;
    }
    file.close();
    cout << "File edited successfully." << endl;
}

void DeleteFile() 
{
    string filename;
    cout << "Enter the name of the file to delete: ";
    cin >> filename;
    if (remove(filename.c_str()) != 0) 
        cerr << "Error deleting file." << endl;
    else 
        cout << "File deleted successfully." << endl;
}

void GenerateRandomData() 
{
    string filename;
    int size;
    cout << "Generate random data for file: ";
    cin >> filename;
    cout << "Enter the size of the file (in bytes): ";
    cin >> size;

    ofstream file(filename.c_str(), ios::out | ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
    }
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        char byte = rand() % 256;
        file.write(&byte, sizeof(byte));
    }

    file.close();
    cout << "Random data generated and written to file ." << endl;
}

void MoveFile() 
{
    string oldName, newName;
    cout << "Enter the name of the file to move: ";
    cin >> oldName;
    cout << "Enter the name of the directory to move the file to: ";
    cin >> newName;

    if (rename(oldName.c_str(), (newName + "/" + oldName).c_str()) != 0) 
        cerr << "Error moving file." << endl;
    else 
        cout << "File moved successfully." << endl;
}


void DuplicateFile() 
{
    string src_filename, dst_filename;
    cout << "Enter the name of the file to duplicate: ";
    cin >> src_filename;
    cout << "Enter the name of the new file: ";
    cin >> dst_filename;

    ifstream src_file(src_filename, std::ios::binary);
    if (!src_file.is_open()) {
        cerr << "Error opening source file." << endl;
        return;
    }

    ofstream dst_file(dst_filename, std::ios::binary);
    if (!dst_file.is_open()) {
        std::cerr << "Error opening destination file." << std::endl;
        return;
    }

    dst_file << src_file.rdbuf();

    src_file.close();
    dst_file.close();

    std::cout << "File duplicated successfully." << std::endl;
}



void DuplicateDirectory(string source_dir, string target_dir);

void DuplicateDirectory() 
{

    // Get source directory path from user input
    std::string source_dir_path;
    std::cout << "Enter the source directory path: ";
    std::getline(std::cin, source_dir_path);
    
    // Get target directory path from user input
    std::string target_dir_path;
    std::cout << "Enter the target directory path: ";
    std::getline(std::cin, target_dir_path);
    
    // Check if source directory exists and is a directory
    if (!std::filesystem::exists(source_dir_path)) {
        std::cerr << "Source directory does not exist." << std::endl;
        return;
    }
    if (!std::filesystem::is_directory(source_dir_path)) {
        std::cerr << "Source path is not a directory." << std::endl;
        return;
    }
    
    // Check if target directory exists and is a directory
    if (!std::filesystem::exists(target_dir_path)) {
        std::cerr << "Target directory does not exist." << std::endl;
        return;
    }
    if (!std::filesystem::is_directory(target_dir_path)) {
        std::cerr << "Target path is not a directory." << std::endl;
        return;
    }


    DuplicateDirectory(source_dir_path, target_dir_path);
}


void DuplicateDirectory(string source_dir, string target_dir) 
{
    DIR* source = opendir(source_dir.c_str());
    if (source == NULL) {
        cerr << "Error opening source directory." << endl;
        return;
    }

    DIR* target = opendir(target_dir.c_str());
    if (target == NULL) {
        cerr << "Error opening target directory." << endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(source)) != NULL) {
        string source_file_path = source_dir + "/" + entry->d_name;
        string target_file_path = target_dir + "/" + entry->d_name;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        struct stat s;
        lstat(source_file_path.c_str(), &s);

        if (S_ISDIR(s.st_mode)) {
            mkdir(target_file_path.c_str(), 0777);
            DuplicateDirectory(source_file_path, target_file_path);
        } else {
            ifstream source_file(source_file_path.c_str(), ios::binary);
            ofstream target_file(target_file_path.c_str(), ios::binary);

            target_file << source_file.rdbuf();

            source_file.close();
            target_file.close();
        }
    }

    closedir(source);
    closedir(target);

    cout << "Directory duplicated successfully." << endl;
}

void SearchFile() 
{
    std::string filename;
    std::cout << "Enter the name of the file to search for: ";
    std::getline(std::cin, filename);

    DIR* dir = opendir(".");
    if (dir == NULL) {
        std::cerr << "Error opening directory." << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string path = std::string(entry->d_name);
        if (path == "." || path == "..") {
            continue;
        }

        if (entry->d_type == DT_DIR) {
            chdir(entry->d_name);
            SearchFile();
            chdir("..");
        } else if (entry->d_type == DT_REG && path == filename) {
            std::cout << "File found: " << getcwd(NULL, 0) << "/" << filename << std::endl;
        }
    }
    closedir(dir);
}

void DisplayDirectory(const std::string& dirname, int level);

void DisplayDirectory() 
{
    std::string dirname;
    std::cout << "Enter starting directory: ";
    std::cin >> dirname;
    DisplayDirectory(dirname, 0);
}

void DisplayDirectory(const std::string& directory_name, int level) 
{
    DIR* directory = opendir(directory_name.c_str());
    if (directory == NULL) {
        std::cerr << "Error opening directory: " << directory_name << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            std::cout << std::string(level, '\t') << entry->d_name << "/" << std::endl;
            std::string path = directory_name + "/" + entry->d_name;
            DisplayDirectory(path, level + 1);
        } else {
            std::cout << std::string(level, '\t') << entry->d_name << std::endl;
        }
    }

    closedir(directory);
}

void GetBasicFileInfo() 
{
    string filename;
    cout << "Enter the name of the file you want information about: ";
    cin >> filename;

    struct stat fileStat;
    if (stat(filename.c_str(), &fileStat) == -1) {
        cerr << "Error: could not get file information.\n";
        return;
    }

    cout << "Information for " << filename << ":\n";
    cout << "Last access time: " << ctime(&fileStat.st_atime);
    cout << "Owner UID: " << fileStat.st_uid << "\n";
    cout << "Size: " << fileStat.st_size << " bytes\n";
    
   
}

void GetDetailedFileInfo() 
{
    string filename;
    cout << "Enter the name of the file you want to get information about: ";
    cin >> filename;

    struct stat file_stat;
    if (stat(filename.c_str(), &file_stat) == -1) {
        std::cerr << "Error: could not get file information.\n";
        return;
    }

    cout << "Information for file: " << filename << "\n";
    cout << "Size: " << file_stat.st_size << " bytes\n";
    cout << "Last accessed: " << ctime(&file_stat.st_atime);
    cout << "Last modified: " << ctime(&file_stat.st_mtime);
    cout << "Last status change: " << ctime(&file_stat.st_ctime);
    cout << "Owner user ID: " << file_stat.st_uid << "\n";
    cout << "Owner group ID: " << file_stat.st_gid << "\n";
    cout << "Permissions: " << (file_stat.st_mode & 0777) << "\n";
}

void GetBasicDirectoryInfo() 
{
    string dir_path;
    cout << "Enter directory path: ";
    getline(std::cin, dir_path);

    if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
        std::cout << "Error: invalid directory path.\n";
        return;
    }

    cout << "Directory name: " << fs::path(dir_path).filename() << '\n';
    cout << "Number of files: " << std::distance(fs::directory_iterator(dir_path), fs::directory_iterator{}) << '\n';
    cout << "Size: " << fs::directory_entry(dir_path).file_size() << " bytes\n";
}


void GetDetailedDirectoryInfo() 
{
    std::filesystem::path filepath = std::filesystem::current_path();

    struct stat file_stat;
    if (stat(filepath.c_str(), &file_stat) == 0) {
        std::cout << "Detailed information about file: " << filepath << "\n";
        std::cout << std::left << std::setw(20) << "File size:" << std::right << std::setw(15) << file_stat.st_size << " bytes\n";
        std::cout << std::left << std::setw(20) << "Owner UID:" << std::right << std::setw(15) << file_stat.st_uid << "\n";
        std::cout << std::left << std::setw(20) << "Last access time:" << std::right << std::setw(15) << std::ctime(&file_stat.st_atime);
        std::cout << std::left << std::setw(20) << "Last modification time:" << std::right << std::setw(15) << std::ctime(&file_stat.st_mtime);
    } else {
        std::cerr << "Error getting file info for file: " << filepath << "\n";
    }
}








int main() {
    int choice;

    do {
        // Display the menu to the user
        std::cout << "1. Create directory\n";
        std::cout << "2. Rename directory\n";
        std::cout << "3. Delete directory\n";
        std::cout << "4. Create file\n";
        std::cout << "5. Rename file\n";
        std::cout << "6. Edit file\n";
        std::cout << "7. Delete file\n";
        std::cout << "8. Generate random data\n";
        std::cout << "9. Move file\n";
        std::cout << "10. Duplicate file\n";
        std::cout << "11. Duplicate directory\n";
        std::cout << "12. Search file\n";
        std::cout << "13. Display directory\n";
        std::cout << "14. Get basic file info\n";
        std::cout << "15. Get basic directory info\n";
        std::cout << "16. Get detailed file info\n";
        std::cout << "17. Get detailed directory info\n";
        std::cout << "18. Exit\n";

        // Get user choice
        std::cout << "\n Please enter your choice: ";
        std::cin >> choice;

        // Execute selected function
        switch (choice) {
            case 1:
                CreateDirectory();
                break;
            case 2:
                RenameDirectory();
                break;
            case 3:
                DeleteDirectory();
                break;
            case 4:
                CreateFile();
                break;
            case 5:
                RenameFile();
                break;
            case 6:
                EditFile();
                break;
            case 7:
                DeleteFile();
                break;
            case 8:
                GenerateRandomData();
                break;
            case 9:
                MoveFile();
                break;
            case 10:
                DuplicateFile();
                break;
            case 11:
                DuplicateDirectory();
                break;
            case 12:
                SearchFile();
                break;
            case 13:
                DisplayDirectory();
                break;
            case 14:
                GetBasicFileInfo();
                break;
            case 15:
                GetBasicDirectoryInfo();
                break;
            case 16:
                GetDetailedFileInfo();
                break;
            case 17:
                GetDetailedDirectoryInfo();;
                break;
            case 18:
                std::cout << "Exiting program\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 18);

    return 0;
}









