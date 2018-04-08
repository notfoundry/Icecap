/*
* Created by Mark Johnson on 6/18/2017.
*/

#include "jmap.h"

icecap::map::JMap::JMap(const std::shared_ptr<JNIEnv>& env, jobject map) : JContainer(env, map) {}

jobject icecap::map::JMap::get(jobject key) const {
    static jmethodID mapContainsMethodID = nullptr;
    if (mapContainsMethodID == nullptr) {
        mapContainsMethodID = env->GetMethodID(targetCls, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    }
    return env->CallObjectMethod(target, mapContainsMethodID, key);
}
