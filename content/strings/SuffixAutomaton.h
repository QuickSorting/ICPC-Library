/**
 * Author: 
 * Date: 2024-04-08
 * License: CC0
 * Source: ronnie
 * Description: 
 * Status: 
 */
#pragma once

struct suffix_automaton {
    struct state {
        int len, link;
        map<char, int> next;
        state() {len = link = 0; next.clear(); }
    };
    vector < state > st ;
    int sz, last;
    void sa_init() {
        st.resize ( 1 ) ;
        st[0].len = 0;
        st[0].link = -1;
        sz++;
        last = 0;
    }
    void sa_extend(char c) {
        int cur = sz++;
        st.push_back(state());
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                st.push_back(state());
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    suffix_automaton() {
        st.clear();
        sz = last = 0;
    }
    suffix_automaton(string &s) {
        st.clear();
        sz = last = 0;
        sa_init();
        for(auto c: s) {
            sa_extend(c);
        }
    }
};