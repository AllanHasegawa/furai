#include <furai/core/Application.h>
#include <furai/backends/android/core/AndroidApplication.h>
#include <furai/backends/android/core/jniglue/jniglue.h>
#include <android/native_activity.h>
#include <HelloTriangle.h>

void android_main(struct android_app *app) {
  furai::WindowListener *hello_triangle = new HelloTriangle();
  furai::Application* application = new furai::AndroidApplication(hello_triangle,
                                                                  app);
  application->start();
}
