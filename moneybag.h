#include <algorithm>
#include <compare>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

class Moneybag {
public:
    using coin_number_t = uint64_t;

    coin_number_t liwry;
    coin_number_t solidy;
    coin_number_t denary;

    constexpr Moneybag (coin_number_t n_liwry, coin_number_t n_solidy, coin_number_t n_denary):
            liwry(n_liwry) , solidy(n_solidy), denary (n_denary) {};

    constexpr Moneybag (const Moneybag& another):
            liwry(another.liwry), solidy(another.solidy), denary(another.denary) {};

    constexpr void operator= (const Moneybag& another) noexcept{
        if (this != &another){
            liwry = another.liwry;
            solidy = another.solidy;
            denary = another.denary;
        }
    }

    constexpr Moneybag operator+ (const Moneybag& another) const{
        return Moneybag (liwry + another.liwry, solidy + another.solidy, denary + another.denary);
    }

    constexpr Moneybag operator+= (const Moneybag& another) const{
        liwry = liwry + another.liwry;
    }
};


constexpr Moneybag Livre (1,0,0);
constexpr Moneybag Solidus (0, 1, 0);
constexpr Moneybag Denier (0, 0, 1);
