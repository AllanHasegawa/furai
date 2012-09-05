#include <jni.h>

#include <native_app_glue/android_native_app_glue.h>
#include <android/native_activity.h>

#include <furai/core/Application.h>
#include <furai/backends/android/core/AndroidApplication.h>
#include <HelloTriangle.h>

void android_main(struct android_app *app) {
  using namespace furai;

  WindowListener* hello_triangle = new HelloTriangle();

  Application* application = new AndroidApplication(hello_triangle, app);

  Furai::LOG->LogI("Initializing HelloTriangle Furai Sample");

  application->Start();

  delete hello_triangle;
  delete application;
}
