/*
* Created by Mark Johnson on 6/18/2017.
*/

#ifndef ICECAP_JADAPTER_H
#define ICECAP_JADAPTER_H

#include <jni.h>

#include <memory>

namespace icecap {
    class JAdapter {
    public:
        explicit JAdapter(std::shared_ptr<JNIEnv> env, jobject target);

        ~JAdapter();

    protected:
        const std::shared_ptr<JNIEnv> env;

        jobject target;

        jclass targetCls;
    };
}

#endif //ICECAP_JADAPTER_H
