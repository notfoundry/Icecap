#ifndef ICECAP_LIBRARY_H
#define ICECAP_LIBRARY_H

#include <jni.h>

#include <memory>

#include "jlist_fwd.h"
#include "../jcollection.h"

namespace icecap {
    namespace list {
        class JListIterator;

        class JList : public icecap::collection::JCollection {
        public:
            typedef JListIterator iterator;

            explicit JList(const std::shared_ptr<JNIEnv>& env, jobject list);

            jobject get(size_type pos) const;

            jobject set(size_type idx, jobject obj);

            void add(jobject obj);

            void add(size_type idx, jobject obj);

            size_type indexOf(jobject obj) const;

            jobject remove(size_type idx);

            jobject remove(jobject obj);

            iterator begin();

            iterator end();

        private:
            friend class JListIterator;
        };

        class jlist_jobject_lens {
        public:
            jlist_jobject_lens(JList* list, JList::size_type idx) : list(list), idx(idx) {}

            jlist_jobject_lens() = default;

            operator jobject() const {
                return list->get(idx);
            }

            jlist_jobject_lens& operator=(const jobject& rhs) {
                list->set(idx, rhs);
                return *this;
            }
        private:
            JList::size_type idx;

            JList* list;
        };

        class JListIterator : public std::iterator<std::random_access_iterator_tag, jlist_jobject_lens> {
        public:
            typedef JListIterator iterator;

            typedef JList::size_type difference_type;

            JListIterator() = default;

            explicit JListIterator(JList* list, bool terminal = false);

            iterator operator++(int);

            iterator& operator++();

            reference operator*() const;

            pointer operator->() const;

            iterator operator+(difference_type v) const;

            bool operator==(const iterator& rhs) const;

            bool operator!=(const iterator& rhs) const;

            iterator operator--(int);

            iterator& operator--();

            iterator operator-(difference_type v) const;

            iterator operator-(const iterator& rhs) const;

            friend iterator operator+(difference_type v , const iterator& rhs);

            bool operator<(const iterator& rhs) const;

            bool operator<=(const iterator& rhs) const;

            bool operator>(const iterator& rhs) const;

            bool operator>=(const iterator& rhs) const;

            void operator+=(difference_type v);

            void operator-=(difference_type v);

            value_type operator[](difference_type v) const;

        private:
            inline void ensureCurrentElementCached() const {
                if (!has_curr) {
                    curr = list->get(idx);
                    has_curr = true;
                }
            }

            inline void moveBy(JList::size_type distance) noexcept {
                idx += distance;
                has_curr = false;
            }

            JList* list;

            JList::size_type idx;

            mutable jlist_jobject_lens curr;

            mutable bool has_curr;

            const bool terminal;
        };
    }
}

#endif