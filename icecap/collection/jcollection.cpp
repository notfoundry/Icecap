/*
* Created by Mark Johnson on 6/18/2017.
*/

#include "jcollection.h"

using namespace icecap::collection;

icecap::collection::JCollection::JCollection(std::shared_ptr<JNIEnv> env, jobject collection) : JContainer(env, collection) {}

bool JCollection::add(jobject obj) {
    static jmethodID collectionAddMethodID = nullptr;
    if (collectionAddMethodID == nullptr) {
        collectionAddMethodID = env->GetMethodID(targetCls, "add", "(Ljava/lang/Object;)Z");
    }
    return env->CallBooleanMethod(target, collectionAddMethodID, obj);
}

bool JCollection::remove(jobject obj) {
    static jmethodID collectionRemoveMethodID = nullptr;
    if (collectionRemoveMethodID == nullptr) {
        collectionRemoveMethodID = env->GetMethodID(targetCls, "remove", "(Ljava/lang/Object;)Z");
    }
    return env->CallBooleanMethod(target, collectionRemoveMethodID, obj);
}
