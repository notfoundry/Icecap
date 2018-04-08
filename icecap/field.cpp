/*
* Created by Mark Johnson on 6/22/2017.
*/

#include <jni.h>

#include <type_traits>
#include <utility>

namespace icecap {

    namespace {
        class field_like {
        public:
            explicit field_like(JNIEnv& env, jfieldID fieldID) : env(env), fieldID(fieldID) {}

        protected:
            JNIEnv& env;
            jfieldID fieldID;
        };

        class static_field_like : protected field_like {
        public:
            explicit static_field_like(JNIEnv& env, jfieldID fieldID, jclass cls) : field_like(env, fieldID),
                                                                                    cls(cls) {}

        protected:
            jclass cls;
        };
    }

    template <typename T, typename = void>
    class field;

    template <typename T, typename = void>
    class static_field;

    template <typename T>
    class bound_field {
    public:
        explicit bound_field(const field<T>& field, jobject obj) : field(field), obj(obj) {}

        T get() const {
            return field.get(obj);
        }

        operator T() const {
            return get();
        }

        bound_field<T>& operator=(const T& t) {
            field.set(obj, t);
        }

    private:
        field<T> field;
        jobject obj;
    };

    template <typename T>
    class field<T, std::enable_if_t<std::is_base_of<std::remove_pointer_t<jobject>, std::remove_pointer_t<T>>::value>> : field_like {
    public:
        explicit field(JNIEnv& env, jfieldID fieldID) : field_like(env, fieldID) {}

        T get(jobject obj) const {
            return env.GetObjectField(obj, fieldID);
        }

        void set(jobject obj, const T& t) {
            env.SetObjectField(obj, fieldID, t);
        }

        bound_field<T> bind(jobject obj) const {
            return bound_field<T> {*this, obj};
        }

        bound_field<T> operator[](jobject obj) {
            return bound_field<T> {*this, obj};
        }
    };

#define MAKE_SPECIALIZED_FIELD_T(type_name, f_spec_name)                                \
    template <>                                                                         \
    class field<type_name> : field_like {                                               \
    public:                                                                             \
        explicit field(JNIEnv& env, jfieldID fieldID) : field_like(env, fieldID) {}     \
                                                                                        \
        type_name get(jobject obj) const {                                              \
            return env.Get ## f_spec_name ## Field(obj, fieldID);                       \
        }                                                                               \
                                                                                        \
        void set(jobject obj, const type_name& t) {                                     \
            env.Set ## f_spec_name ## Field(obj, fieldID, t);                           \
        }                                                                               \
                                                                                        \
        bound_field<type_name> bind(jobject obj) const {                                \
            return bound_field<type_name> {*this, obj};                                 \
        }                                                                               \
                                                                                        \
        bound_field<type_name> operator[](jobject obj) {                                \
            return bound_field<type_name> {*this, obj};                                 \
        }                                                                               \
    };

    MAKE_SPECIALIZED_FIELD_T(jint, Int)

    MAKE_SPECIALIZED_FIELD_T(jlong, Long)

    MAKE_SPECIALIZED_FIELD_T(jbyte, Byte)

    MAKE_SPECIALIZED_FIELD_T(jboolean, Boolean)

    MAKE_SPECIALIZED_FIELD_T(jchar, Char)

    MAKE_SPECIALIZED_FIELD_T(jshort, Short)

    MAKE_SPECIALIZED_FIELD_T(jfloat, Float)

    MAKE_SPECIALIZED_FIELD_T(jdouble, Double)

#undef MAKE_SPECIALIZED_FIELD_T

    template <typename T>
    class static_field<T, std::enable_if_t<std::is_base_of<std::remove_pointer_t<jobject>, std::remove_pointer_t<T>>::value>> : static_field_like {
    public:
        explicit static_field(JNIEnv& env, jfieldID fieldID, jclass cls) : static_field_like(env, fieldID, cls) {}

        T get() const {
            return env.GetStaticObjectField(cls, fieldID);
        }

        operator T() const {
            return get();
        }

        static_field<T>& operator=(const T& t) {
            env.SetStaticObjectField(cls, fieldID, t);
        }
    };


#define MAKE_SPECIALIZED_STATIC_FIELD_T(type_name, f_spec_name)                                                     \
    template <>                                                                                                     \
    class static_field<type_name> : static_field_like {                                                             \
    public:                                                                                                         \
        explicit static_field(JNIEnv& env, jfieldID fieldID, jclass cls) : static_field_like(env, fieldID, cls) {}  \
                                                                                                                    \
        type_name get() const {                                                                                     \
            return env.GetStatic ## f_spec_name ## Field(cls, fieldID);                                             \
        }                                                                                                           \
                                                                                                                    \
        operator type_name() const {                                                                                \
            return get();                                                                                           \
        }                                                                                                           \
                                                                                                                    \
        static_field<type_name>& operator=(const type_name& t) {                                                    \
            env.SetStatic ## f_spec_name ## Field(cls, fieldID, t);                                                 \
        }                                                                                                           \
    };

    MAKE_SPECIALIZED_STATIC_FIELD_T(jint, Int)

    MAKE_SPECIALIZED_STATIC_FIELD_T(jlong, Long)

    MAKE_SPECIALIZED_STATIC_FIELD_T(jbyte, Byte)

    MAKE_SPECIALIZED_STATIC_FIELD_T(jboolean, Boolean)

    MAKE_SPECIALIZED_STATIC_FIELD_T(jchar, Char)

    MAKE_SPECIALIZED_STATIC_FIELD_T(jshort, Short)

    MAKE_SPECIALIZED_STATIC_FIELD_T(jfloat, Float)

    MAKE_SPECIALIZED_STATIC_FIELD_T(jdouble, Double)

#undef MAKE_SPECIALIZED_STATIC_FIELD_T

    template <typename T>
    bound_field<T> bind_field(JNIEnv& env, jfieldID fieldID, jobject obj) {
        return bound_field<T>{{env, fieldID}, obj};
    }
}