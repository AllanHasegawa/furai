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

#ifndef FURAI_ANDROIDINTERNALFILE_H_
#define FURAI_ANDROIDINTERNALFILE_H_

#include <android/asset_manager.h>

#include <furai/core/Furai.h>
#include <furai/storage/InternalFile.h>
#include <furai/backends/android/storage/AndroidFileSystem.h>

namespace furai {

class AndroidInternalFile : public furai::InternalFile {
  friend class AndroidFileSystem;
 public:
  AndroidInternalFile(const std::string path);
  virtual ~AndroidInternalFile();

  void WaitOperationToComplete();

  void Open();
  void Read(const int64_t offset, const int32_t bytes_to_read, char *buffer);
  void Close();

 private:
  AAsset* asset_;

  pthread_mutex_t mutex_status_;
  pthread_cond_t cond_status_;

  void OpenCallback(bool success, AAsset* asset, int64_t size);
  void ReadCallback(bool success, int64_t bytes_read);
  void CloseCallback();
};

}  // namespace furai
#endif /* FURAI_ANDROIDINTERNALFILE_H_ */
