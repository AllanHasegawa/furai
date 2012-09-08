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

#ifndef FURAI_ANDROIDFILESYSTEM_H_
#define FURAI_ANDROIDFILESYSTEM_H_

#include <tr1/memory>
#include <queue>
#include <pthread.h>

#include <android/asset_manager.h>

#include <furai/storage/FileSystem.h>
#include <furai/core/Furai.h>

namespace furai {

class AndroidInternalFile;

enum AndroidFSOP {
  AFS_OP_OPEN,
  AFS_OP_READ,
  AFS_OP_WRITE,
  AFS_OP_CLOSE
};

typedef struct AndroidFSOPData {
  File* file_;
  AAsset* asset_;
  AndroidFSOP op_;
  char* buffer_;
  int64_t offset_;
  int32_t bytes_to_read_;
} AndroidFSOPData;

class AndroidFileSystem : public furai::FileSystem {
  friend class AndroidInternalFile;

 public:
  AndroidFileSystem(AAssetManager* asset_manager)

  ;

  virtual ~AndroidFileSystem();

  InternalFile* Internal(const std::string path);

 private:
  AAssetManager* asset_manager_;

  bool destroy_;
  std::queue<AndroidFSOPData> op_queue_;

  pthread_t thread_op_queue_;
  pthread_mutex_t mutex_op_queue_;
  pthread_cond_t cond_op_queue_;

  static void* Run(void* data);

  void QueueOpen(File* file) {
    Furai::LOG->LogV("AFS: QueueOpen");
    AndroidFSOPData data;
    data.op_ = AFS_OP_OPEN;
    data.file_ = file;
    this->op_queue_.push(data);
  }

  void QueueClose(AAsset* asset) {

  }

  void QueueRead(File* file, AAsset* asset, const int64_t offset,
                 const int32_t bytes_to_read, char *buffer) {
    AndroidFSOPData data;
    data.op_ = AFS_OP_READ;
    data.file_ = file;
    data.asset_ = asset;
    data.offset_ = offset;
    data.bytes_to_read_ = bytes_to_read;
    data.buffer_ = buffer;
    this->op_queue_.push(data);
  }
};

}  // namespace furai
#endif /* FURAI_ANDROIDFILESYSTEM_H_ */
