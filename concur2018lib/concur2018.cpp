/*
 * TIE-0250x project library
 *
 * DO NOT make any changes to this file
 * Reading the source is allowed and encouraged
 *
 * 2018-02-15 v1.0 published
 */

#include "concur2018.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <atomic>
#include <chrono>
#include <thread>
#include <QDirIterator>
#include <QFileInfo>
#include <QString>

namespace concur2018 {

namespace { // module internal

    // c++11 random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(10,500);

    // assert function and macro to notify failed operation (including source file and linenumber)
    void my_assert( bool cond, const char* WHAT, const char* FILE, int LINE ) {
        if( cond ) {
            return;
        } else {
            std::cerr << FILE << ":" << LINE << ":" << WHAT << ":Assertion failed" << std::endl;
            exit(1);
        }
    }
#define MY_ASSERT( cond ) my_assert(cond, #cond, __FILE__, __LINE__)


    // flags for the external 'convert' program (ImageMagick)
    std::map<Ops,std::string> IMops = {
        { Copyright, "-fill White -box SkyBlue -gravity South -pointsize 42 -annotate +4+4 ' Copyright ' " },
        { Rotate, "-rotate 45" },
        { Border, "-bordercolor Pink -border 11x11" },
        { Grayscale, "-type Grayscale" },
        { Unfocus, "-blur 3x3" }
    };

    std::atomic<int> entrycounter(0);

}

FileList GetFiles(std::string directory)
{
    // API is not threadsafe. Add some checks against wrong usage
    entrycounter++;
    std::this_thread::sleep_for( std::chrono::milliseconds( dis(gen) ));
    MY_ASSERT( entrycounter.load() == 1);

    // use handy Qt-libs to collect all '*.png'
    // filenames and return them as FileList
    FileList retval;
    QDirIterator it( QString::fromStdString(directory) );
    while( it.hasNext() ) {
        QString filename = it.next();
        if( filename.endsWith(".png")) {
            retval.push_back( filename.toUtf8().constData() );
        }
    }

    MY_ASSERT( entrycounter.load() == 1);
    entrycounter--;
    std::this_thread::sleep_for( std::chrono::milliseconds( dis(gen) ));
    MY_ASSERT( entrycounter.load() == 0);

    return retval;
}


bool ProcessFile(std::string filename, Ops operation )
{
    std::string CMD = "convert ";
    CMD += filename;
    CMD += " ";
    CMD += IMops[ operation ];
    CMD += " ";
    // remove any directory information from >filename>:
    std::string outfile = QFileInfo( QString::fromStdString(filename) ).fileName().toUtf8().constData();
    // hardcoded result directory and filename suffix:
    CMD += "outdir/" + outfile + "_processed";

    // in linux system actually execute the conversion
    // all other environments -> just print out the command string
#ifdef __linux__
    // 0 return means OK -> "flip" it with not-operator
    return not static_cast<bool>( std::system( CMD.c_str() ) );
#else
    std::cout << "(nonlinux system, only printing the command): " << CMD << std::endl;
    return true;
#endif
}

} // namespace concur2018
