/*
* Created by Mark Johnson on 6/18/2017.
*/

#include "jadapter.h"

icecap::JAdapter::JAdapter(std::shared_ptr<JNIEnv> env, jobject target)
        : env(env),
          target(env->NewGlobalRef(target)),
          targetCls(static_cast<jclass>(env->NewGlobalRef(env->GetObjectClass(target)))) {}

icecap::JAdapter::~JAdapter() {
    env->DeleteGlobalRef(target);
    env->DeleteGlobalRef(targetCls);
}
