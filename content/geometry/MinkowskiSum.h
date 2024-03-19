/**
 * Author: cp-algorithms
 * Date: 2024-03-19
 * License: CC0
 * Source: cp-algorithms
 * Description: Returns the Minkowski sum of two polygons.
 * Status:
 */

template<class P>
void reorder_polygon(vector<P> & p){
    size_t pos = 0;
    for(size_t i = 1; i < p.size(); i++){
        if(p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x))
            pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

template<class P>
vector<P> minkowski(vector<P> p, vector<P> q){
    // the first vertex must be the lowest
    reorder_polygon(p);
    reorder_polygon(q);
    // we must ensure cyclic indexing
    p.push_back(p[0]);
    p.push_back(p[1]);
    q.push_back(q[0]);
    q.push_back(q[1]);
    // main part
    vector<P> result;
    size_t i = 0, j = 0;
    while(i < p.size() - 2 || j < q.size() - 2){
        result.push_back(p[i] + q[j]);
        auto cross = (p[i + 1] - p[i]).cross(q[j + 1] - q[j]);
        if(cross >= 0 && i < p.size() - 2)
            ++i;
        if(cross <= 0 && j < q.size() - 2)
            ++j;
    }
    return result;
}