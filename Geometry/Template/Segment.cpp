struct Segment {
    Point s, e;
    Segment(): s({0, 0}), e({0, 0}) {}
    Segment(Point s, Point e): s(s), e(e) {}
    DBL length() { return dis(s, e); }
};