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
  pthread_mutex_init(&mutex_op_queue_, NULL);
  pthread_cond_init(&cond_op_queue_, NULL);
}

AndroidFileSystem::~AndroidFileSystem() {
  pthread_mutex_lock(&mutex_op_queue_);
  this->destroy_ = true;
  pthread_cond_signal(&cond_op_queue_);
  pthread_mutex_unlock(&mutex_op_queue_);
  pthread_join(thread_op_queue_, NULL);
  pthread_mutex_destroy(&mutex_op_queue_);
  pthread_cond_destroy(&cond_op_queue_);
}

InternalFile* AndroidFileSystem::Internal(const std::string path) {
  return new AndroidInternalFile(path);
}

void* AndroidFileSystem::Run(void* data) {
  AndroidFileSystem* afs = static_cast<AndroidFileSystem*>(data);

  while (true) {

    pthread_mutex_lock(&afs->mutex_op_queue_);
    while (!afs->destroy_ && afs->op_queue_.size() == 0) {
      pthread_cond_wait(&afs->cond_op_queue_, &afs->mutex_op_queue_);
    }

    if (afs->destroy_) {
      pthread_mutex_unlock(&afs->mutex_op_queue_);
      pthread_exit(NULL);
      return NULL;
    }

    if (afs->op_queue_.size() == 0) {
      pthread_mutex_unlock(&afs->mutex_op_queue_);
      continue;
    }

    AndroidFSOPData data = afs->op_queue_.front();
    afs->op_queue_.pop();
    pthread_mutex_unlock(&afs->mutex_op_queue_);

    switch (data.op_) {
      case AFS_OP_OPEN: {
        Furai::LOG->LogV("AFS: OP OPEN");
        AAsset* asset = AAssetManager_open(afs->asset_manager_,
                                           data.file_->path().c_str(),
                                           AASSET_MODE_STREAMING);
        if (asset == NULL) {
          static_cast<AndroidInternalFile*>(data.file_)->OpenCallback(false,
                                                                      asset,
                                                                      -1);
          continue;
        }
        int64_t size = AAsset_getLength(asset);
        static_cast<AndroidInternalFile*>(data.file_)->OpenCallback(true, asset,
                                                                    size);
      }
        break;
      case AFS_OP_READ: {
        Furai::LOG->LogV("AFS: OP READ");
        off_t ret = AAsset_seek(data.asset_, data.offset_, SEEK_SET);
        if (ret == -1) {
          static_cast<AndroidInternalFile*>(data.file_)->ReadCallback(false,
                                                                      -1);
          continue;
        }
        int64_t bytes_read = AAsset_read(data.asset_, data.buffer_,
                                         data.bytes_to_read_);
        if (bytes_read < 0) {
          static_cast<AndroidInternalFile*>(data.file_)->ReadCallback(false,
                                                                      -1);
          continue;
        }

        static_cast<AndroidInternalFile*>(data.file_)->ReadCallback(true,
                                                                    bytes_read);
      }
        break;
      case AFS_OP_CLOSE: {
        Furai::LOG->LogV("AFS: OP CLOSE");
        AAsset_close(data.asset_);

        static_cast<AndroidInternalFile*>(data.file_)->CloseCallback();
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

void AndroidFileSystem::QueueOpen(File* file) {
  Furai::LOG->LogV("AFS: QueueOpen");
  AndroidFSOPData data;
  data.op_ = AFS_OP_OPEN;
  data.file_ = file;
  pthread_mutex_lock(&mutex_op_queue_);
  this->op_queue_.push(data);
  pthread_cond_signal(&cond_op_queue_);
  pthread_mutex_unlock(&mutex_op_queue_);
}

void AndroidFileSystem::QueueClose(File* file, AAsset* asset) {
  Furai::LOG->LogV("AFS: QueueClose");
  AndroidFSOPData data;
  data.op_ = AFS_OP_CLOSE;
  data.file_ = file;
  data.asset_ = asset;
  pthread_mutex_lock(&mutex_op_queue_);
  this->op_queue_.push(data);
  pthread_cond_signal(&cond_op_queue_);
  pthread_mutex_unlock(&mutex_op_queue_);
}

void AndroidFileSystem::QueueRead(File* file, AAsset* asset,
                                  const int64_t offset,
                                  const int32_t bytes_to_read, char *buffer) {
  AndroidFSOPData data;
  data.op_ = AFS_OP_READ;
  data.file_ = file;
  data.asset_ = asset;
  data.offset_ = offset;
  data.bytes_to_read_ = bytes_to_read;
  data.buffer_ = buffer;
  pthread_mutex_lock(&mutex_op_queue_);
  this->op_queue_.push(data);
  pthread_cond_signal(&cond_op_queue_);
  pthread_mutex_unlock(&mutex_op_queue_);
}

}  // namespace furai
