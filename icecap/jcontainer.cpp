/*
* Created by Mark Johnson on 6/18/2017.
*/

#include "jcontainer.h"

icecap::JContainer::JContainer(const std::shared_ptr<JNIEnv>& env, jobject target) : JAdapter(env, target) {}

bool icecap::JContainer::contains(jobject obj) const {
    static jmethodID containsMethodID = nullptr;
    if (containsMethodID == nullptr) {
        containsMethodID = env->GetMethodID(targetCls, "contains", "(Ljava/lang/Object;)Z");
    }
    return env->CallBooleanMethod(target, containsMethodID, obj);
}

bool icecap::JContainer::empty() const {
    static jmethodID isEmptyMethodID = nullptr;
    if (isEmptyMethodID == nullptr) {
        isEmptyMethodID = env->GetMethodID(targetCls, "isEmpty", "()Z");
    }
    return env->CallBooleanMethod(target, isEmptyMethodID);
}

icecap::JContainer::size_type icecap::JContainer::size() const {
    static jmethodID sizeMethodID = nullptr;
    if (sizeMethodID == nullptr) {
        sizeMethodID = env->GetMethodID(targetCls, "size", "()I");
    }
    return static_cast<size_type>(env->CallIntMethod(target, sizeMethodID));
}

void icecap::JContainer::clear() {
    static jmethodID clearMethodID = nullptr;
    if (clearMethodID == nullptr) {
        clearMethodID = env->GetMethodID(targetCls, "clear", "()V");
    }
    env->CallVoidMethod(target, clearMethodID);
}
