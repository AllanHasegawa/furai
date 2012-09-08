/*
 -----------------------------------------------------------------------------
 This source file is part of the Project Furai.
 For more information, go to:
 http://code.google.com/p/furai/
 -----------------------------------------------------------------------------

 Copyright 2012 Allan Yoshio Hasegawa

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 -----------------------------------------------------------------------------
 */

#ifndef FURAI_FILE_H_
#define FURAI_FILE_H_

#include <string>
#include <android/asset_manager.h>

namespace furai {

enum FileType {
  FILE_TYPE_REGULAR,
  FILE_TYPE_DIRECTORY,
  FILE_TYPE_DONT_EXIST,
  FILE_TYPE_UNKNOWN
};

enum FileSystemType {
  FILE_SYSTEM_TYPE_INTERNAL,
  FILE_SYSTEM_TYPE_EXTERNAL
};

enum FileStatus {
  FILE_STATUS_WORKING,
  FILE_STATUS_WAITING,
  FILE_STATUS_ERROR
};

typedef struct FileInfo {
  int64_t size_;
  FileType file_type_;
  FileSystemType file_system_type_;
} FileInfo;

class File {
 public:
  File(std::string path)
      : path_(path) {

  }
  virtual ~File() {
  }

  virtual void Open() = 0;
  virtual void Close() = 0;

  virtual void WaitOperationToComplete() = 0;

  /*


   virtual void ListFiles(const int32_t max_file_list, File* files,
   int32_t* number_files) = 0;

   std::string GetFileName();
   std::string GetFileExtension();
   std::string GetParent();
   */

  std::string path() {
    return path_;
  }

  FileInfo info() {
    return info_;
  }

  FileStatus status() {
    return status_;
  }

 protected:
  std::string path_;
  FileInfo info_;
  FileStatus status_;
};

}  // namespace furai
#endif /* FURAI_FILE_H_ */
