struct radius_tag {};
struct durchmesser_tag {};

struct Kreis {
    double radius;
    Kreis(double radius, radius_tag _) : radius(radius){};
    Kreis(double durchmesser, durchmesser_tag _) : radius(durchmesser / 2){};
};

int main() {
    Kreis k1(3, radius_tag{});
    Kreis k2(6, durchmesser_tag{});
};