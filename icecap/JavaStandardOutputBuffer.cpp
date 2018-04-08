#include <sstream>

#include "jni.h"

/*
* Created by Mark Johnson on 6/19/2017.
*/

class JavaStandardOutputBuffer : public std::stringbuf {
public:
    explicit JavaStandardOutputBuffer(JNIEnv* env)
            : env(env), systemJClass((jclass) env->NewGlobalRef(env->FindClass("java/lang/System"))) {}

    ~JavaStandardOutputBuffer() override {
        env->DeleteGlobalRef(systemJClass);
    }

    int sync() override {
        static jfieldID printStreamFieldID = nullptr;
        static jmethodID printMethodID = nullptr;

        if (printStreamFieldID == nullptr) {
            printStreamFieldID = env->GetStaticFieldID(systemJClass, "out", "Ljava/io/PrintStream;");
            printMethodID = env->GetMethodID(env->FindClass("java/io/PrintStream"), "print", "(Ljava/lang/String;)V");
        }
        env->CallVoidMethod(env->GetStaticObjectField(systemJClass, printStreamFieldID), printMethodID, env->NewStringUTF(str().c_str()));
        return 0;
    }

private:
    JNIEnv* env;

    jclass systemJClass;
};