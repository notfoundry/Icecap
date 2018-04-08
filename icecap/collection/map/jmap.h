/*
* Created by Mark Johnson on 6/18/2017.
*/

#ifndef ICECAP_JMAP_H
#define ICECAP_JMAP_H

#include <jni.h>

#include <memory>

#include "jmap_fwd.h"
#include "../../jcontainer.h"

namespace icecap {
    namespace map {
        class JMap : public icecap::JContainer {
        public:
            JMap(const std::shared_ptr<JNIEnv>& env, jobject map);

            jobject get(jobject key) const;
        };
    }
}

#endif //ICECAP_JMAP_H
