#include <iostream>
#include "quickrefs.hpp"


// Usage: download_references bulk_downloader_folder reffile
int main(int argc, char *argv[]) {
    Archive archive(argv[1], argv[2]);
    archive.run();
}
