/*
* Created by Mark Johnson on 6/18/2017.
*/

#ifndef ICECAP_JCONTAINER_H
#define ICECAP_JCONTAINER_H

#include "jadapter.h"

namespace icecap {
    class JContainer : public JAdapter {
    public:
        typedef jint size_type;

        JContainer(const std::shared_ptr<JNIEnv>& env, jobject target);

        bool contains(jobject obj) const;

        bool empty() const;

        size_type size() const;

        void clear();
    };
}

#endif //ICECAP_JCONTAINER_H
