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

#ifndef FURAI_NACLINTERNALFILE_H_
#define FURAI_NACLINTERNALFILE_H_

#include "ppapi/cpp/url_loader.h"
#include "ppapi/cpp/url_request_info.h"
#include <ppapi/cpp/instance.h>
#include <ppapi/utility/completion_callback_factory.h>

#include <furai/storage/InternalFile.h>

namespace furai {

class NaClInternalFile : public InternalFile {
 public:
  NaClInternalFile(pp::Instance* instance, const std::string path);
  virtual ~NaClInternalFile();

  void WaitOperationToComplete();

  void Open();
  void Close();

  void Read(const int64_t offset, const int32_t bytes_to_read, char *buffer);

 private:
  pp::URLRequestInfo url_request_;
  pp::URLLoader url_loader_;
  pp::CompletionCallbackFactory<NaClInternalFile> cc_factory_;

  void OnOpen(int32_t result);
  void OnRead(int32_t result);
};

}  // namespace furai
#endif /* FURAI_NACLINTERNALFILE_H_ */
