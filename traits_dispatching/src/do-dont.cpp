#include <iostream>
#include <type_traits>

// struct Kreis {
//     static struct Leerer_kreis {
//     } leerer_kreis;
//     static struct Einheits_kreis {
//     } einheits_kreis;
//     explicit Kreis(Leerer_kreis);
//     explicit Kreis(Einheits_kreis);
// };

// struct Kreis {
//     struct radius_tag{};
//     struct durchmesser_tag {};
//     explicit Kreis(double r, radius_tag);
//     explicit Kreis(double d, durchmesser_tag);
// };


struct Kreis {
    explicit Kreis(Radius r);
    explicit Kreis(Durchmesser d);
};

int main() {
    // Kreis k1(Kreis::Leerer_kreis);
    // Kreis k2(Kreis::Einheits_kreis);
}
