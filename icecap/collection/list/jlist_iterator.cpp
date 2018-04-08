/*
* Created by Mark Johnson on 6/17/2017.
*/

#include "jlist.h"

using namespace icecap::list;

JListIterator::JListIterator(JList* list, bool terminal) : list(list), idx(0), has_curr(false), terminal(terminal) {}

JListIterator::iterator JListIterator::operator++(int) {
    JListIterator that = *this;
    moveBy(1);
    return that;
}

JListIterator::iterator& JListIterator::operator++() {
    moveBy(1);
    return *this;
}

jlist_jobject_lens& JListIterator::operator*() const {
    ensureCurrentElementCached();
    return reinterpret_cast<reference>(curr);
}

jlist_jobject_lens* JListIterator::operator->() const {
    ensureCurrentElementCached();
    return &curr;
}

JListIterator::iterator JListIterator::operator+(JListIterator::difference_type v) const {
    JListIterator that = *this;
    that.moveBy(v);
    return that;
}

bool JListIterator::operator==(const JListIterator::iterator& rhs) const {
    if (rhs.terminal) {
        return idx >= rhs.list->size();
    } else if (terminal) {
        return rhs.idx >= list->size();
    } else {
        return idx == rhs.idx;
    }
}

bool JListIterator::operator!=(const JListIterator::iterator& rhs) const {
    return !operator==(rhs);
}

JListIterator::iterator JListIterator::operator--(int) {
    JListIterator that = *this;
    moveBy(-1);
    return that;
}

JListIterator::iterator& JListIterator::operator--() {
    moveBy(-1);
    return *this;
}

JListIterator::iterator JListIterator::operator-(JListIterator::difference_type v) const {
    JListIterator that = *this;
    that.moveBy(-v);
    return that;
}

JListIterator::iterator JListIterator::operator-(const JListIterator::iterator& rhs) const {
    JListIterator that = *this;
    that.moveBy(-rhs.idx);
    return that;
}

bool JListIterator::operator<(const JListIterator::iterator& rhs) const {
    if (rhs.terminal) {
        return idx < list->size();
    } else if (terminal) {
        return rhs.idx < list->size();
    } else {
        return idx < rhs.idx;
    }
}

bool JListIterator::operator<=(const JListIterator::iterator& rhs) const {
    if (rhs.terminal) {
        return idx <= list->size();
    } else if (terminal) {
        return rhs.idx <= list->size();
    } else {
        return idx <= rhs.idx;
    }
}

bool JListIterator::operator>(const JListIterator::iterator& rhs) const {
    if (rhs.terminal) {
        return idx > list->size();
    } else if (terminal) {
        return rhs.idx > list->size();
    } else {
        return idx > rhs.idx;
    }
}

bool JListIterator::operator>=(const JListIterator::iterator& rhs) const {
    if (rhs.terminal) {
        return idx >= list->size();
    } else if (terminal) {
        return rhs.idx >= list->size();
    } else {
        return idx >= rhs.idx;
    }
}

void JListIterator::operator+=(JListIterator::difference_type v) {
    moveBy(v);
}

void JListIterator::operator-=(JListIterator::difference_type v) {
    moveBy(-v);
}

JListIterator::value_type JListIterator::operator[](JListIterator::difference_type v) const {
    return jlist_jobject_lens{list, v};
}

JListIterator::iterator
operator+(JListIterator::difference_type v, const JListIterator::iterator& rhs) {
    return rhs.operator+(v);
}