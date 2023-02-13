#include <algorithm>
#include <compare>
#include <cstdint>
#include <bits/stdc++.h>
#include <exception>
#include <limits.h>
#include <compare>
#include <iostream>
#include <stdexcept>
#include <string>

class Moneybag {
public:
    using coin_number_t = uint64_t;

    coin_number_t liwry;
    coin_number_t solidy;
    coin_number_t denary;

    //obsluga bledow dokonczyc
    constexpr static void in_range_sum (const uint64_t x, const uint64_t y) {
        if (UINT64_MAX - x < y || UINT64_MAX - y < x){
            throw new std::out_of_range ("sum is not in range");
        }
    }

    //dlaczego static (inaczej jest blad w mnozeniu nie wiem dlaczego)
    constexpr static void in_range_difference (const uint64_t x, const uint64_t y) {
        if (x < y){
            throw new std::out_of_range ("difference is not in range");
        }
    }

    constexpr static void in_range_multiple (const int c, const uint64_t x) {
        uint64_t t = UINT64_MAX / c;

        if (c < 0 || x > t){
            throw new std::out_of_range ("multiply is out of range");
        }
    }

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
        in_range_sum(liwry, another.liwry);
        in_range_sum (solidy, another.solidy);
        in_range_sum (denary, another.denary);

        return Moneybag (liwry + another.liwry, solidy + another.solidy, denary + another.denary);
    }

    constexpr Moneybag operator+= (const Moneybag& another) {
        in_range_sum(liwry, another.liwry);
        in_range_sum (solidy, another.solidy);
        in_range_sum (denary, another.denary);

        liwry += another.liwry;
        denary += another.denary;
        solidy += another.solidy;

        return *this;
    }

    constexpr Moneybag operator- (const Moneybag& another) const{
        in_range_difference(liwry, another.liwry);
        in_range_difference(solidy, another.solidy);
        in_range_difference(denary, another.denary);

        return Moneybag (liwry - another.liwry, solidy - another.solidy,
                         denary - another.denary);
    }

    constexpr Moneybag& operator-= (const Moneybag& another){
        in_range_difference(liwry, another.liwry);
        in_range_difference(solidy, another.solidy);
        in_range_difference(denary, another.denary);

        liwry -= another.liwry;
        denary -= another.denary;
        solidy -= another.solidy;

        return *this;
    }

    friend constexpr Moneybag operator* (const int c, const Moneybag& m) {
        in_range_multiple(c, m.livre_number());
        in_range_multiple(c, m.solidus_number());
        in_range_multiple(c, m.denier_number());

        return Moneybag(c * m.liwry,
                        c * m.solidy,
                        c * m.denary);
    }

    constexpr Moneybag operator*= (const int c) {
        in_range_multiple(c, livre_number());
        in_range_multiple(c, solidus_number());
        in_range_multiple(c, denier_number());

        liwry *= c;
        denary *= c;
        solidy *= c;

        return *this;
    }

    constexpr coin_number_t solidus_number() const noexcept{
        return this->solidy;
    }
    constexpr coin_number_t livre_number() const noexcept{
        return this->liwry;
    }
    constexpr coin_number_t denier_number() const noexcept{
        return this->denary;
    }

    constexpr bool operator== (const Moneybag& another) const noexcept{
        if (liwry == another.liwry && solidy == another.solidy && denary == another.denary) return true;

        return false;
    }

    friend std::ostream& operator<< (std::ostream& os, const Moneybag& another) noexcept{
        os << "(" << another.liwry << " livres, " << another.solidy << " soliduses, "
                  << another.denary << " deniers)" << std::endl;

        return os;
    }

    friend std::partial_ordering operator<=>(const Moneybag& m1, const Moneybag& m2) {
        std::strong_ordering cmp_l = m1.livre_number() <=> m2.livre_number();
        std::strong_ordering cmp_s = m1.solidus_number() <=> m2.solidus_number();
        std::strong_ordering cmp_d = m1.denier_number() <=> m2.denier_number();

        if (std::is_eq(cmp_l) && std::is_eq(cmp_s) && std::is_eq(cmp_d)) {
            return std::partial_ordering::equivalent;
        }
        if (std::is_lteq(cmp_l) && std::is_lteq(cmp_s) && std::is_lteq(cmp_d)) {
            return std::partial_ordering::less;
        }
        if (std::is_gteq(cmp_l) && std::is_gteq(cmp_s) && std::is_gteq(cmp_d)) {
            return std::partial_ordering::greater;
        }
        return std::partial_ordering::unordered;
    }

    explicit operator bool ()  {
        if (!solidy || !denary || !liwry) return true;

        return false;
    }


};


constexpr Moneybag Livre (1,0,0);
constexpr Moneybag Solidus (0, 1, 0);
constexpr Moneybag Denier (0, 0, 1);

// 1 liwr = 20 solidów = 240 denarów
class Value {
public:
    uint64_t denary;

    constexpr Value (const uint64_t n_denary) :
        denary(n_denary) {};

    //dlaczego explicit tu?
   explicit constexpr Value (const Moneybag& another) :
        denary(another.denier_number() + 12 * another.solidus_number()  + 240 * another.livre_number()) {};

    constexpr Value operator= (const Value& another){
        if (this != &another){
            denary = another.denary;
        }

        return *this;
    }

    explicit operator std::string () const{
        return std::to_string (denary);
    }

    auto operator<=> (const Value &) const = default;
};
