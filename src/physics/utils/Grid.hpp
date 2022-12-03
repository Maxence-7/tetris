class Grid {
    public:
        unsigned int W;
        unsigned int H;
        unsigned int P;
        unsigned int X;
        unsigned int Y;
        unsigned int Z;
    public:
    Grid(unsigned int W, unsigned int H, unsigned int X, unsigned int Y);
    Grid(unsigned int W, unsigned int H, unsigned int P, unsigned int X, unsigned int Y, unsigned int Z);
    ~Grid();
};

Grid::Grid(unsigned int W, unsigned int H, unsigned int X, unsigned int Y) : W(W), H(H), X(X), Y(Y) {
}

Grid::Grid(unsigned int W, unsigned int H, unsigned int P, unsigned int X, unsigned int Y, unsigned int Z) : W(W), H(H), P(P), X(X), Y(Y), Z(Z) {
}

Grid::~Grid() {
}
