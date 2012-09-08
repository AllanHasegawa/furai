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

#include "furai/backends/android/storage/AndroidFileSystem.h"
#include <android/asset_manager.h>

#include <furai/backends/android/storage/AndroidInternalFile.h>

namespace furai {

AndroidFileSystem::AndroidFileSystem(AAssetManager* asset_manager)
    : asset_manager_(asset_manager) {
  this->destroy_ = false;
  pthread_create(&thread_op_queue_, NULL, &AndroidFileSystem::Run, this);
}

AndroidFileSystem::~AndroidFileSystem() {
  this->destroy_ = true;
  pthread_join(thread_op_queue_, NULL);
}

InternalFile* AndroidFileSystem::Internal(const std::string path) {
  return new AndroidInternalFile(path);
}

void* AndroidFileSystem::Run(void* data) {
  AndroidFileSystem* afs = static_cast<AndroidFileSystem*>(data);

  while (true) {

    if (afs->destroy_) {
      pthread_exit(NULL);
      return NULL;
    }

    while (afs->op_queue_.size() == 0) {
      sleep(1);
    }

    AndroidFSOPData data = afs->op_queue_.front();
    afs->op_queue_.pop();

    switch (data.op_) {
      case AFS_OP_OPEN: {
        Furai::LOG->LogV("AFS: OP OPEN");
        AAsset* asset = AAssetManager_open(afs->asset_manager_,
                                           data.file_->path().c_str(),
                                           AASSET_MODE_STREAMING);
        int64_t size = AAsset_getLength(asset);

        static_cast<AndroidInternalFile*>(data.file_)->OpenCallback(asset,
                                                                    size);

      }
        break;
      case AFS_OP_READ: {
        Furai::LOG->LogV("AFS: OP READ");
        AAsset_seek(data.asset_, data.offset_, SEEK_SET);
        int64_t bytes_read = AAsset_read(data.asset_, data.buffer_,
                                         data.bytes_to_read_);

        static_cast<AndroidInternalFile*>(data.file_)->ReadCallback(bytes_read);
      }
        break;
      case AFS_OP_CLOSE: {
      }
        break;
      default: {
      }
        break;
    }
  }

  pthread_exit(NULL);
  return NULL;
}

}  // namespace furai
