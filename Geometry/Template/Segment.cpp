struct Segment {
    Point s, e;
    Vector v;
    Segment(): s(0, 0), e(0, 0), v(0, 0) {}
    Segment(Point s, Point e): s(s), e(e) {
      v = e - s;
    }
    DBL length() { return v.length(); }
};