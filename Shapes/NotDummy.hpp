class DummyNotMoveableObject : public NotMoveableObject {
    public:
        DummyNotMoveableObject() : NotMoveableObject(Vector2f{0.0, 0.0}) {}
        FloatRect getBound() {return FloatRect();}
        void draw(RenderWindow& window) override {}
};