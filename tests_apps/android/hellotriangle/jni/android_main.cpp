#include <furai/core/Application.h>
#include <furai/backends/android/core/AndroidApplication.h>
#include <furai/backends/android/core/jniglue/jniglue.h>
#include <android/native_activity.h>
#include <MyCycle.h>

void android_main(struct android_app *app) {
  furai::WindowListener *my_cycle = new MyCycle();
  furai::Application* application = new furai::AndroidApplication(my_cycle,
                                                                  app);
  application->start();
}
