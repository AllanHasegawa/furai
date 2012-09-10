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

#include "furai/backends/nacl/storage/NaClInternalFile.h"

#include <ppapi/cpp/completion_callback.h>
#include <ppapi/utility/completion_callback_factory.h>
#include <furai/storage/InternalFile.h>
#include <furai/core/Furai.h>

namespace pp {
class Instance;
}

namespace furai {

NaClInternalFile::NaClInternalFile(pp::Instance* instance,
                                   const std::string path)
    : InternalFile(path),
      url_request_(instance),
      url_loader_(instance),
      cc_factory_(this) {

  url_request_.SetURL(path);
  url_request_.SetMethod("GET");
  url_request_.SetRecordDownloadProgress(true);

  this->status_ = FILE_STATUS_WAITING;
}

NaClInternalFile::~NaClInternalFile() {
}

void NaClInternalFile::Open() {
  this->status_ = FILE_STATUS_WORKING;

  pp::CompletionCallback cc = cc_factory_.NewCallback(&NaClInternalFile::OnOpen);

  int32_t result = url_loader_.Open(url_request_, cc);
  if (result != PP_OK_COMPLETIONPENDING) {
    this->status_ = FILE_STATUS_ERROR;
    Furai::LOG->LogE("NIF: Error opening file with path: %s", path_.c_str());
    return;
  } else {
    Furai::LOG->LogV("NIF: Open R: %d", result);
  }
}

void NaClInternalFile::Close() {

}

void NaClInternalFile::WaitOperationToComplete() {
  while (status_ == FILE_STATUS_WORKING) {
    Furai::LOG->LogV("NIF: WaitOperationToComplete %d", status_);
  }
}

void NaClInternalFile::Read(const int64_t offset, const int32_t bytes_to_read,
                            char *buffer) {
  this->status_ = FILE_STATUS_WORKING;

  pp::CompletionCallback cc = cc_factory_.NewOptionalCallback(
      &NaClInternalFile::OnRead);

  int32_t result = url_loader_.ReadResponseBody(buffer, 1000000, cc);

  if (result != PP_OK_COMPLETIONPENDING) {
    cc.Run(result);
  }
}

void NaClInternalFile::OnOpen(int32_t result) {
  Furai::LOG->LogV("NIF: OnOpen");
  if (result != PP_OK) {
    this->status_ = FILE_STATUS_ERROR;
    return;
  }
  int64_t bytes_received = 0;
  int64_t total_bytes_to_be_received = 0;
  if (url_loader_.GetDownloadProgress(&bytes_received,
                                      &total_bytes_to_be_received)) {
    if (total_bytes_to_be_received > 0) {
      this->info_.size_ = total_bytes_to_be_received;
    }
  }
  url_request_.SetRecordDownloadProgress(false);

  this->status_ = FILE_STATUS_WAITING;
}

void NaClInternalFile::OnRead(int32_t result) {
  if (result == PP_OK) {
    this->bytes_read_ = result;
    this->status_ = FILE_STATUS_WAITING;
  } else {
    this->bytes_read_ = -1;
    this->status_ = FILE_STATUS_ERROR;
  }
}

}  // namespace furai
