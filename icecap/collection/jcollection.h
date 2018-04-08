/*
* Created by Mark Johnson on 6/18/2017.
*/

#ifndef ICECAP_JCOLLECTION_H
#define ICECAP_JCOLLECTION_H

#include <jni.h>

#include <memory>

#include "jcollection_fwd.h"
#include "../jcontainer.h"

namespace icecap {
    namespace collection {

        class JCollection : public icecap::JContainer {
        public:
            typedef jint size_type;

            explicit JCollection(std::shared_ptr<JNIEnv> env, jobject collection);

            bool add(jobject obj);

            bool remove(jobject obj);
        };
    }
}

#endif //ICECAP_JCOLLECTION_H
