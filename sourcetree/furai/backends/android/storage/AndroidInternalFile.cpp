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

#include "furai/backends/android/storage/AndroidInternalFile.h"

#include <pthread.h>
#include <android/configuration.h>

namespace furai {

AndroidInternalFile::AndroidInternalFile(const std::string path)
    : InternalFile(path) {
  pthread_mutex_init(&mutex_status_, NULL);
  pthread_cond_init(&cond_status_, NULL);
}

AndroidInternalFile::~AndroidInternalFile() {
  this->Close();
  pthread_mutex_destroy(&mutex_status_);
  pthread_cond_destroy(&cond_status_);
}

void AndroidInternalFile::WaitOperationToComplete() {
  pthread_mutex_lock(&mutex_status_);
  while (this->status_ == FILE_STATUS_WORKING) {
    pthread_cond_wait(&cond_status_, &mutex_status_);
  }
  pthread_mutex_unlock(&mutex_status_);
}

void AndroidInternalFile::Open() {
  pthread_mutex_lock(&mutex_status_);
  this->status_ = FILE_STATUS_WORKING;
  pthread_mutex_unlock(&mutex_status_);
  static_cast<AndroidFileSystem*>(Furai::FS)->QueueOpen(this);
}

void AndroidInternalFile::Read(const int64_t offset,
                               const int32_t bytes_to_read, char *buffer) {
  pthread_mutex_lock(&mutex_status_);
  this->status_ = FILE_STATUS_WORKING;
  pthread_mutex_unlock(&mutex_status_);
  static_cast<AndroidFileSystem*>(Furai::FS)->QueueRead(
      static_cast<File*>(this), this->asset_, offset, bytes_to_read, buffer);
}

void AndroidInternalFile::Close() {
  if (this->asset_ == NULL) {
    return;
  }
  pthread_mutex_lock(&mutex_status_);
  this->status_ = FILE_STATUS_WORKING;
  pthread_mutex_unlock(&mutex_status_);
  static_cast<AndroidFileSystem*>(Furai::FS)->QueueClose(this, this->asset_);
}

void AndroidInternalFile::OpenCallback(bool success, AAsset* asset,
                                       int64_t size) {
  this->info_.size_ = size;
  this->asset_ = asset;
  pthread_mutex_lock(&mutex_status_);
  this->status_ = (success) ? FILE_STATUS_WAITING : FILE_STATUS_ERROR;
  pthread_cond_signal(&cond_status_);
  pthread_mutex_unlock(&mutex_status_);
}

void AndroidInternalFile::ReadCallback(bool success, int64_t bytes_read) {
  this->bytes_read_ = bytes_read;
  pthread_mutex_lock(&mutex_status_);
  this->status_ = (success) ? FILE_STATUS_WAITING : FILE_STATUS_ERROR;
  pthread_cond_signal(&cond_status_);
  pthread_mutex_unlock(&mutex_status_);
}

void AndroidInternalFile::CloseCallback() {
  pthread_mutex_lock(&mutex_status_);
  this->asset_ = NULL;
  this->status_ = FILE_STATUS_WAITING;
  pthread_cond_signal(&cond_status_);
  pthread_mutex_unlock(&mutex_status_);
}

}  // namespace furai
