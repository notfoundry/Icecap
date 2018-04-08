/*
* Created by Mark Johnson on 6/18/2017.
*/

#include "jset.h"

using namespace icecap::set;

JSet::JSet(const std::shared_ptr<JNIEnv>& env, jobject set) : JCollection(env, set) {}