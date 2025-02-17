#include "Directory.h"

File Directory::getFile(int index) const
{
	/* TODO */
	if(0<=index && index<files.size()){
	    return files[index];
	}
	else{
	    File emptyFile = File();
	    return emptyFile;
	}
}

size_t Directory::directorySize() const
{
	/* TODO */
	int i = 0;
	size_t directSize = 0;
	while(i<files.size()){
	    directSize += files[i].fileSize();
	    i++;
	}
	return directSize;
}

bool Directory::isEmpty() const
{
	/* TODO */
	if(files.size() == 0) return true;
	else return false;
}

size_t Directory::numFiles() const
{
	/* TODO */
	size_t num = 0;
	int i = 0;
	while(i<files.size()){
	    if(!files[i].isEmpty()) {
	        num++;
	    }  
	    i++;
	}
	return i;
}

void Directory::newFile(const File &file)
{
	/* TODO */
	files.push_back(file);
}

void Directory::removeFile(int index)
{
	/* TODO */
	files.erase(files.begin() + index);
}

void Directory::removeFile(File &file)
{
	/* TODO */
	size_t i;
    for (i = 0; i < files.size(); ++i) {
        if (files[i] == file) {
            files.erase(files.begin() + i); 
            break;                     
        }
    }
}

void Directory::removeBiggestFile()
{
	/* TODO */
	int i = 0;
	int j = 0;
	size_t maxSize; 
	if(files.size()!=0){
        maxSize = files[0].fileSize();
        for(i=1; i<files.size()-1; i++){
            if(files[i].fileSize() > maxSize) {
                maxSize = files[i].fileSize();
                j = i;
                i++;
            }
            else i++;
        }
        removeFile(j);
	}
}
