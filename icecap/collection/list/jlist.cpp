#include "jlist.h"

using namespace icecap::list;

JList::JList(const std::shared_ptr<JNIEnv>& env, jobject list)
        : JCollection(env, list) {}

jobject JList::get(size_type pos) const {
    static jmethodID listGetMethodID = nullptr;
    if (listGetMethodID == nullptr) {
        listGetMethodID = env->GetMethodID(targetCls, "get", "(I)Ljava/lang/Object;");
    }
    return env->CallObjectMethod(target, listGetMethodID, pos);
}

JList::iterator JList::begin() {
    return icecap::list::JList::iterator(this);
}

JList::iterator JList::end() {
    return icecap::list::JList::iterator(this, true);
}

jobject JList::set(JList::size_type idx, jobject obj) {
    static jmethodID listSetMethodID = nullptr;
    if (listSetMethodID == nullptr) {
        listSetMethodID = env->GetMethodID(targetCls, "set", "(ILjava/lang/Object;)Ljava/lang/Object;");
    }
    return env->CallObjectMethod(target, listSetMethodID, idx, obj);
}

void JList::add(jobject obj) {
    static jmethodID listAddMethodID = nullptr;
    if (listAddMethodID == nullptr) {
        listAddMethodID = env->GetMethodID(targetCls, "add", "(Ljava/lang/Object;)V");
    }
    env->CallVoidMethod(target, listAddMethodID, obj);
}

void JList::add(JList::size_type idx, jobject obj) {
    static jmethodID listAddMethodID = nullptr;
    if (listAddMethodID == nullptr) {
        listAddMethodID = env->GetMethodID(targetCls, "add", "(ILjava/lang/Object;)V");
    }
    env->CallVoidMethod(target, listAddMethodID, idx, obj);
}

JList::size_type JList::indexOf(jobject obj) const {
    static jmethodID listIndexOfMethodID = nullptr;
    if (listIndexOfMethodID == nullptr) {
        listIndexOfMethodID = env->GetMethodID(targetCls, "indexOf", "(Ljava/lang/Object;)I");
    }
    return env->CallIntMethod(target, listIndexOfMethodID, obj);
}

jobject JList::remove(JList::size_type idx) {
    static jmethodID listRemoveMethodID = nullptr;
    if (listRemoveMethodID == nullptr) {
        listRemoveMethodID = env->GetMethodID(targetCls, "remove", "(I)Ljava/lang/Object;");
    }
    return env->CallObjectMethod(target, listRemoveMethodID, idx);
}

jobject JList::remove(jobject obj) {
    static jmethodID listRemoveMethodID = nullptr;
    if (listRemoveMethodID == nullptr) {
        listRemoveMethodID = env->GetMethodID(targetCls, "remove", "(Ljava/lang/Object;)Ljava/lang/Object;");
    }
    return env->CallObjectMethod(target, listRemoveMethodID, obj);
}