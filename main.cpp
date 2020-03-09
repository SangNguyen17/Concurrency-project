/* The main function first get all files that need to be processed
 * and stores them in files vector. Each image file has its own
 * mutex, which makes sure that only one thread can process on this
 * file at a time. Construct the mutex for each file is handled by
 * initializeMutexMap(const concur2018::FileList& files) function.
 *
 * Then, the main function starts several threads.
 * Each of which associates with the function
 * operateFiles (concur2018::FileList& files, MutexMap mu_map).
 * Inside operateFiles, 7 sub-threads are started
 * (in this exercise we have 7 images), each of which associates
 * with the function
 * callProcessFiles(const std::string& filename, MutexMap mu_map).
 * This function will process the image with given filename.
 * It has a lock_guard to make sure that only one thread
 * can process a particular file at a time.
 * 
 * This is a group assignment. Contributors: Sang Nguyen, Hai Luong, Ankur Dahama
 */

#include "concur2018.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <string>
#include <unordered_map>

struct MutexWrapper {
    std::mutex mu;
};

std::mutex mu;

typedef std::unordered_map<std::string, MutexWrapper*> MutexMap;

void callProcessFiles(const std::string& filename, MutexMap mu_map) {
    const int FIRSTLETTER = 7;
    std::cout << "Processing: " << filename << std::endl;
    // select fileoperation based on the first letter of filename:
    std::lock_guard<std::mutex> guard(mu_map[filename]->mu);
    switch( filename[FIRSTLETTER] ) {
    case 'C':
        concur2018::ProcessFile( filename, concur2018::Copyright );
        break;
    case 'R':
        concur2018::ProcessFile( filename, concur2018::Rotate );
        break;
    case 'B':
        concur2018::ProcessFile( filename, concur2018::Border );
        break;
    case 'G':
        concur2018::ProcessFile( filename, concur2018::Grayscale );
        break;
    case 'U':
        concur2018::ProcessFile( filename, concur2018::Unfocus );
        break;
    default:
        std::cerr << "Cannot operate with firstletter '" + std::string(1, filename[FIRSTLETTER]) + "'" << std::endl;
        break;
    } // switch
}

void operateFiles (concur2018::FileList& files, MutexMap mu_map) {

    for( auto filename : files ) {
        std::thread callProcess(callProcessFiles, filename, mu_map);
        callProcess.join();
    } // for
}

concur2018::FileList getFiles() {
    std::string location = "inputs";

    std::cout << "Starting conversion of " << location << std::endl;
    return concur2018::GetFiles( location );
}

const MutexMap initializeMutexMap(const concur2018::FileList& files) {
    MutexMap mutexMap;
    for (std::string filename: files) {
        MutexWrapper *new_mu = new MutexWrapper();
        mutexMap.insert({filename, new_mu});
    }
    return mutexMap;
}

int main()
{
    std::cerr << "main() starting." << std::endl;
    concur2018::FileList files = getFiles();
    const MutexMap mutexMap = initializeMutexMap(files);
    std::cout << mutexMap.size() << std::endl;

    std::thread t1(operateFiles, std::ref(files), mutexMap);
    std::thread t2(operateFiles, std::ref(files), mutexMap);
    std::thread t3(operateFiles, std::ref(files), mutexMap);
    t1.join();
    t2.join();
    t3.join();

    std::cerr << "main() ending." << std::endl;
}
