#ifndef CONCUR2018API
#define CONCUR2018API

#include <string>
#include <vector>
#include <random>
// REMEMBER: do NOT make any changes to this file

namespace concur2018 {
    
    // datatype for a list of filenames
    typedef std::vector<std::string> FileList;

    // return a list of picture files from <directory>
    // THREADS: not threadsafe
    FileList GetFiles( std::string directory );

    // image operations available
    enum Ops {
        Copyright, // add copyright text to image
        Rotate,    // rotate image
        Border,    // change border color
        Grayscale, // color->grayscale conversion
        Unfocus    // blur image
    };

    // Create a new image from <filename> and
    // do <operation> to it.
    // THREADS: threadsafe to separate filenames
    // running operation to two files at the same time is undefined
    // RETURN VALUE: true is operation succeeded
    bool ProcessFile( std::string filename, Ops operation );


} // namespace concur2018

#endif // CONCUR2018API
