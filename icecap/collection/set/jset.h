/*
* Created by Mark Johnson on 6/18/2017.
*/

#ifndef ICECAP_JSET_H
#define ICECAP_JSET_H

#include <jni.h>

#include <memory>

#include "jset_fwd.h"
#include "../jcollection.h"

namespace icecap {
    namespace set {
        class JSet : public icecap::collection::JCollection {
        public:
            JSet(const std::shared_ptr<JNIEnv>& env, jobject set);
        };
    }
}

#endif //ICECAP_JSET_H
