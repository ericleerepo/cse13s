#include "set.h"

#include <stdio.h>

Set set_empty(void) {
    return 0x00;
}

Set set_universal(void) {
    return 255;
}
Set set_insert(Set s, int x) {
    Set compare = 1 << x;
    Set insert = s | compare;
    return insert;
}

Set set_remove(Set s, int x) {
    Set compare = ~(1 << x);
    Set removed = s & compare;
    return removed;
}
bool set_member(Set s, int x) {
    Set compare = 1 << x;
    Set check = s & compare;
    if (check > 0) {
        return true;
    } else {
        return false;
    }
}
Set set_union(Set s, Set t) {
    Set combine = s | t;
    return combine;
}
Set set_intersect(Set s, Set t) {
    Set intersect = s & t;
    return intersect;
}
Set set_difference(Set s, Set t) {
    Set inverse = ~t;
    Set difference = s & inverse;
    return difference;
}
Set set_complement(Set s) {
    return ~s;
}
