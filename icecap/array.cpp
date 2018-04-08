/*
* Created by Mark Johnson on 6/25/2017.
*/

#include <jni.h>

#include <type_traits>

namespace icecap {

    namespace {
        class jni_caller {
        protected:
            explicit jni_caller(JNIEnv& env) : env(env) {}

            JNIEnv& env;
        };
    }

    template <typename T, typename = void>
    class array;

    template <typename T, typename = void>
    class array_element_lens;

    template <typename T>
    class array_element_lens<T, std::enable_if_t<std::is_base_of<std::remove_pointer_t<jobject>, std::remove_pointer_t<T>>::value>>
            : jni_caller {
    public:
        array_element_lens(JNIEnv& env, jobjectArray arr, jsize index) : jni_caller(env), arr(arr), index(index) {}

        array_element_lens() = default;

        operator T() const {
            return env.GetObjectArrayElement(arr, index);
        }

        array_element_lens<T>& operator=(const T& rhs) {
            env.SetObjectArrayElement(arr, index, rhs);
            return *this;
        }

    private:
        jobjectArray arr;

        jsize index;
    };

#define MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(type_name, f_spec_name)           \
    template <>                                                                 \
    class array_element_lens<type_name> : jni_caller {                          \
    public:                                                                     \
        array_element_lens(JNIEnv& env, type_name ## Array arr, jsize index)    \
            : jni_caller(env), arr(arr), index(index) {}                        \
                                                                                \
        array_element_lens() = default;                                         \
                                                                                \
        operator type_name() const {                                            \
            type_name* buf;                                                     \
            env.Get ## f_spec_name ## ArrayRegion(arr, index, 1, buf);          \
            return *buf;                                                        \
        }                                                                       \
                                                                                \
        array_element_lens<type_name>& operator=(const type_name& rhs) {        \
            type_name buf[] {rhs};                                              \
            env.Set ## f_spec_name ## ArrayRegion(arr, index, 1, buf);          \
            return *this;                                                       \
        }                                                                       \
                                                                                \
    private:                                                                    \
        type_name ## Array arr;                                                 \
                                                                                \
        jsize index;                                                            \
    };

    MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(jint, Int)

    MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(jlong, Long)

    MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(jbyte, Byte)

    MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(jboolean, Boolean)

    MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(jchar, Char)

    MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(jshort, Short)

    MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(jfloat, Float)

    MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T(jdouble, Double)

#undef MAKE_SPECIALIZED_ARRAY_ELEMENT_LENS_T

    template <typename T>
    class array<T, std::enable_if_t<std::is_base_of<std::remove_pointer_t<jobject>, std::remove_pointer_t<T>>::value>>
            : jni_caller {
    public:
        typedef jsize size_type;

        array(JNIEnv& env, jobjectArray arr) : jni_caller(env), arr(arr) {}

        ~array() {
            env.DeleteLocalRef(arr);
        }

        array_element_lens<T> operator[](size_type index) {
            return array_element_lens<T> {env, arr, index};
        }

        size_type length() const {
            return env.GetArrayLength(arr);
        }

    private:
        jobjectArray arr;
    };


#define MAKE_SPECIALIZED_ARRAY_T(type_name)                                         \
    template <>                                                                     \
    class array<type_name> : jni_caller {                                           \
    public:                                                                         \
        typedef jsize size_type;                                                    \
                                                                                    \
        array(JNIEnv& env, type_name ## Array arr) : jni_caller(env), arr(arr) {}   \
                                                                                    \
        ~array() {                                                                  \
            env.DeleteLocalRef(arr);                                                \
        }                                                                           \
                                                                                    \
        array_element_lens<type_name> operator[](size_type index) {                 \
            return array_element_lens<type_name> {env, arr, index};                 \
        }                                                                           \
                                                                                    \
        size_type length() const {                                                  \
            return env.GetArrayLength(arr);                                         \
        }                                                                           \
                                                                                    \
    private:                                                                        \
        type_name ## Array arr;                                                     \
    };

    MAKE_SPECIALIZED_ARRAY_T(jint)

    MAKE_SPECIALIZED_ARRAY_T(jlong)

    MAKE_SPECIALIZED_ARRAY_T(jbyte)

    MAKE_SPECIALIZED_ARRAY_T(jboolean)

    MAKE_SPECIALIZED_ARRAY_T(jchar)

    MAKE_SPECIALIZED_ARRAY_T(jshort)

    MAKE_SPECIALIZED_ARRAY_T(jfloat)

    MAKE_SPECIALIZED_ARRAY_T(jdouble)

#undef MAKE_SPECIALIZED_ARRAY_T
}