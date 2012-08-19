#include <jni.h>

#include <android_native_app_glue.h>

#include <furai/core/Application.h>
#include <furai/backends/android/core/AndroidApplication.h>
#include <android/native_activity.h>
#include <HelloTriangle.h>
#include <AndroidHelloTriangle.h>

void android_main(struct android_app *app) {
  using namespace furai;
  WindowListener* hello_triangle = new HelloTriangle();
  AndroidFullWindowListener* full_app_cycle = new AndroidHelloTriangle();
  Application* application = new AndroidApplication(hello_triangle,
                                                    full_app_cycle, app);
  application->start();
}
